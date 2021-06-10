#include <string.h>
#include <platform.h>
#include <rv_trng.h>

static int HalWaitInterrupt(rv32_trng_t *trng)
{
    uint32_t isr = 0;
    uint32_t crngterr = 0;
    uint32_t abort = 0;

    // Polling ISR value
    do {
        isr = trng->ISR;
        if (isr & 0x1 << DX_RNG_ISR_EHR_VALID_BIT_SHIFT)
            return 0;

        if (isr & 0x1 << DX_RNG_ISR_CRNGT_ERR_BIT_SHIFT) {
            trng->ICR = 0x1 << DX_RNG_ISR_CRNGT_ERR_BIT_SHIFT;
            crngterr++;
            if (crngterr >= TRNG_MAX_CRNGT_ERRORS)
                abort = 1;
        }
    } while (!abort);

    return -1;
}

static void TurnOffTrng(rv32_trng_t *trng)
{
    // Disable the RND source
    trng->RND_SOURCE_ENABLE = LLF_RND_HW_RND_SRC_DISABLE_VAL;

    // clear RNG interrupts
    trng->ICR = 0xffffffff;

    return;
}

static int GetRoscSampleCnt(uint32_t rosc, CCRndParams_t *pTrngParams)
{
    switch (rosc) {
    case 0x1:
        pTrngParams->SubSamplingRatio = pTrngParams->SubSamplingRatio1;
        break;
    case 0x2:
        pTrngParams->SubSamplingRatio = pTrngParams->SubSamplingRatio2;
        break;
    case 0x4:
        pTrngParams->SubSamplingRatio = pTrngParams->SubSamplingRatio3;
        break;
    case 0x8:
        pTrngParams->SubSamplingRatio = pTrngParams->SubSamplingRatio4;
        break;
    default:
        return -1;
    }

    return 0;
}

static uint32_t RoscMaskToNum(uint32_t mask)
{
    return (mask == LLF_RND_HW_TRNG_ROSC3_BIT) ? LLF_RND_HW_TRNG_ROSC3_NUM :
           (mask == LLF_RND_HW_TRNG_ROSC2_BIT) ? LLF_RND_HW_TRNG_ROSC2_NUM :
           (mask == LLF_RND_HW_TRNG_ROSC1_BIT) ? LLF_RND_HW_TRNG_ROSC1_NUM :
           LLF_RND_HW_TRNG_ROSC0_NUM;
}

static int GetFastestRosc(CCRndParams_t *trngParams_ptr, uint32_t *rosc_ptr)
{
    do {
        if (*rosc_ptr & trngParams_ptr->RoscsAllowed) 
            return 0;
        else
            *rosc_ptr <<= 1;
    } while (*rosc_ptr <= 0x08);

    return -1;
}

static int startTrngHW(CCRndState_t  *rndState_ptr,
                       CCRndParams_t *trngParams_ptr,
                       int           isRestart,
                       uint32_t      *roscsToStart_ptr,
                       rv32_trng_t *trng)
{
    int error = 0;
    uint32_t tmpSamplCnt = 0;
    uint32_t roscNum = 0;

    if ((rndState_ptr == 0) || (trngParams_ptr == 0) || (roscsToStart_ptr == 0))
        return -1;

    // 1. If full restart, get semaphore and set initial ROSCs
    if (isRestart) {
        *roscsToStart_ptr = 1UL;
        rndState_ptr->TrngProcesState = 0;
    }

    if (*roscsToStart_ptr == 0)
        return -1;

    // TRNG90B mode, Get fastest allowed ROSC
    error = GetFastestRosc(trngParams_ptr, roscsToStart_ptr);
    if (error)
        return error;

    error = GetRoscSampleCnt(*roscsToStart_ptr, trngParams_ptr);
    if (error)
        return error;

    roscNum = RoscMaskToNum(*roscsToStart_ptr);

    // 2. Restart the TRNG and set parameters
    do {
        trng->SAMPLE_CNT1 = trngParams_ptr->SubSamplingRatio;
        tmpSamplCnt = trng->SAMPLE_CNT1;
    } while (tmpSamplCnt != trngParams_ptr->SubSamplingRatio);

    trng->RND_SOURCE_ENABLE = LLF_RND_HW_RND_SRC_DISABLE_VAL;
    trng->CONFIG = roscNum;
    trng->DEBUG_CONTROL = LLF_RND_HW_DEBUG_CONTROL_VALUE_ON_TRNG90B_MODE;
    trng->IMR = LLF_RNG_INT_MASK_ON_TRNG90B_MODE;
    trng->ICR = 0xFFFFFFFF;
    trng->RND_SOURCE_ENABLE = LLF_RND_HW_RND_SRC_ENABLE_VAL;

    rndState_ptr->TrngProcesState  = (rndState_ptr->TrngProcesState & 0x00ffffff) | (*roscsToStart_ptr << 24);
    rndState_ptr->TrngProcesState |= (*roscsToStart_ptr << 8);

    return error;
}

static int32_t readEhrData(uint32_t     *sample,
                           uint32_t     len,
                           CCRndState_t *rndState_ptr,
                           CCRndParams_t *trngParams_ptr,
                           uint32_t     *roscsToStart_ptr,
                           rv32_trng_t *trng)
{
    uint32_t i, words, bytes;
    int err = 0;

    if (len > (TRNG_EHR_SIZE * sizeof(uint32_t)))
        return -1;

    err = startTrngHW(rndState_ptr, trngParams_ptr, 0, roscsToStart_ptr, trng);
    if (err)
        return err;

    // Read 1 EHR of random bits
    if (HalWaitInterrupt(trng)) {
        TurnOffTrng(trng);
        return -1;
    }

    words = len / sizeof(uint32_t);
    bytes = len & (sizeof(uint32_t) - 1);

    // Read EHR into tmp buffer
    for (i = 0; i < words; i++)
        sample[i] = trng->EHR_DATA[i];

    if (bytes) {
        uint32_t val = trng->EHR_DATA[i];
        uint8_t *tmp = (uint8_t *)sample + words * sizeof(uint32_t);

        for (i = 0; i < bytes; i++)
            tmp[i] = (val >> (i*8)) & 0xff;
    }

    return 0;
}

static int readMultipleEHR(uint32_t         inSize,
                           uint8_t         *ramAddr,
                           CCRndState_t    *rndState_ptr,
                           CCRndParams_t   *trngParams_ptr,
                           uint32_t        *roscsToStart_ptr,
                           rv32_trng_t   *trng)
{
    int err = 0;
    uint32_t read_size;

    while (inSize) {
        TurnOffTrng(trng);
        read_size = (inSize < (TRNG_EHR_SIZE * sizeof(uint32_t))) ?
                        inSize : (TRNG_EHR_SIZE * sizeof(uint32_t));
        err = readEhrData((uint32_t *)ramAddr, read_size, rndState_ptr,
                          trngParams_ptr, roscsToStart_ptr, trng);
        if (err != 0)
            return err;

        inSize -= read_size;
        ramAddr += read_size;
    }

    return 0;
}

static uint32_t getBitsFromUint32Array(uint32_t arrayBitsOffset,
                                       uint32_t numOfBits,
                                       uint32_t *arr)
{
    uint32_t res = 0;
    uint32_t byteOffset = arrayBitsOffset / 32;
    uint32_t bitOffset = arrayBitsOffset % 32;

    if (numOfBits > 32)
        return 0;

    // (UINT32_SIZE_IN_BITS - bitOffset) bits were taken from the first DWORD.
    res = arr[byteOffset] >> bitOffset;

    if (32 - bitOffset > numOfBits) {
        // We copied more bits than required. Zero the extra bits.
        res &= (0xffffffff >> (32 - numOfBits));
    } else if (32 - bitOffset < numOfBits) {
        // We copied less bits than required. Copy the next bits from the next DWORD.
        numOfBits -= 32 - bitOffset;
        res |= (arr[byteOffset + 1] & (0xffffffff >> (32 - numOfBits))) << (32 - bitOffset);
    }

    return res;
}

static int RepetitionConterTest(uint32_t *pData,
                                uint32_t sizeInBytes,
                                uint32_t C)
{
    uint32_t bitOffset = 0;
    uint32_t newSample = 0;
    uint32_t A = 0; // the most recently seen sample value
    uint32_t B = 0; // the number of consecutive times that the value A has been seen
    uint32_t bitsPerSample = 1; // always use single bit per sample for repetition counter test

    if (pData == 0 || sizeInBytes == 0 || LLF_RND_TRNG90B_MAX_BYTES < sizeInBytes)
        return -1;

    // the repection count test is performed as follows
    for (bitOffset = 0; bitOffset <= (sizeInBytes * 8) - bitsPerSample; bitOffset += bitsPerSample) {
        newSample = getBitsFromUint32Array(bitOffset, bitsPerSample, (uint32_t *)pData);

        if (bitOffset == 0) {
            // 1. Let A be the current sample value.
            A = newSample;
            // 2. Initialize the counter B to 1.
            B = 1;
        } else if (A == newSample) {
            // 3. If the next sample value is A, increment B by one
            ++B;
            if (B == C)
                return -1;
        } else {
            // Let A be the next sample value.
            A = newSample;
            // Initialize the counter B to 1.
            B = 1;
        }
    }

    return 0;
}

static int AdaptiveProportionTest(uint32_t *pData,
                                  uint32_t sizeInBytes,
                                  uint32_t C,
                                  uint32_t W)
{
    uint32_t bitOffset = 0;
    uint32_t currentSample = 0;
    uint32_t A = 0; // the sample value currently being counted
    uint32_t B = 0; // the current number of times that A has been seen in the S samples examined so far
    uint32_t i = 0; // the counter for the number of samples examined in the current window
    uint32_t bitsPerSample = 1; // binary source

    if (pData == 0 || sizeInBytes == 0 || LLF_RND_TRNG90B_MAX_BYTES < sizeInBytes ||
        W == 0 || C == 0)
        return -1;

    // The test is performed as follows:
    for (bitOffset = 0; bitOffset <= (sizeInBytes * 8) - bitsPerSample; bitOffset += bitsPerSample) {
        currentSample = getBitsFromUint32Array(bitOffset, bitsPerSample, (uint32_t *)pData);

        if ((bitOffset == 0) || (i == W)) {
            // 1. Let A be the current sample value.
            // 2. Initialize the counter B to 1
            A = currentSample;
            B = 1;
            i = 0;
        } else {
            // 3. For i = 1 to W - 1
            if (A == currentSample)
                ++B;
        }

        // 4. If B > C, return error.
        if (i == W - 1) {
            if (B > C)
                return -1;
        }

        ++i;
        // 5. Goto step 1
    }

    return 0;
}

static int runContinuousTesting(uint32_t *pData,
                                uint32_t sizeInBytes)
{
    int error = 0;
    uint32_t repC = CC_CONFIG_TRNG90B_REPETITION_COUNTER_CUTOFF;
    uint32_t adpW = CC_CONFIG_TRNG90B_ADAPTIVE_PROPORTION_WINDOW_SIZE;
    uint32_t adpC = CC_CONFIG_TRNG90B_ADAPTIVE_PROPORTION_CUTOFF;

    error = RepetitionConterTest(pData, sizeInBytes, repC);
    if (error != 0)
        return error;

    error = AdaptiveProportionTest(pData, sizeInBytes, adpC, adpW);
    if (error != 0)
        return error;

    return 0;
}

static int CheckHwParams(CCRndParams_t *trngParams_ptr,
                         rv32_trng_t *trng)
{
    // Check debug control - masked TRNG tests according to mode
    if (trng->DEBUG_CONTROL != LLF_RND_HW_DEBUG_CONTROL_VALUE_ON_TRNG90B_MODE)
        return -1;

    // Check samplesCount
    if (trng->SAMPLE_CNT1 != trngParams_ptr->SubSamplingRatio)
        return -1;

    return 0;
}

static int getTrngSource(
             CCRndState_t    *rndState_ptr,      /*in/out*/
             CCRndParams_t   *trngParams_ptr,    /*in/out*/
             int              isContinued,       /*in*/
             uint32_t       **sourceOut_ptr_ptr, /*out*/
             uint32_t        *sourceOutSize_ptr, /*in/out*/
             uint32_t        *rndWorkBuff_ptr,   /*in*/
             int              isStartup,         /*in*/
             rv32_trng_t *trng)
{
    // The return error identifier
    int error=0, descrError=0;
    int32_t i;
    uint32_t roscToStart;
    uint32_t *ramAddr;
    const uint32_t trng90bRequireBytes = (isStartup == 0 ? CC_CONFIG_TRNG90B_AMOUNT_OF_BYTES : CC_CONFIG_TRNG90B_AMOUNT_OF_BYTES_STARTUP);

    // Set source RAM address with offset 8 bytes from sourceOut address in
    // order to remain empty bytes for CC operations
    *sourceOut_ptr_ptr = rndWorkBuff_ptr;
    ramAddr = *sourceOut_ptr_ptr;

    *sourceOutSize_ptr = 0;

    if (isContinued == 0) {
        // Full restart TRNG
        error = startTrngHW(rndState_ptr, trngParams_ptr,
                            1 /* isRestart */, &roscToStart, trng);
        if (error)
            goto End;
    } else {
        // Check TRNG parameters
        error = CheckHwParams(trngParams_ptr, trng);
        if (error != 0)
            goto End;

        // Previously started ROSCs
        roscToStart = (rndState_ptr->TrngProcesState & 0xff000000) >> 24;
    }

    for (i = 0; i < LLF_RND_NUM_OF_ROSCS; i++) {
        *sourceOutSize_ptr = trng90bRequireBytes;

        descrError = readMultipleEHR(*sourceOutSize_ptr,
                                     (uint8_t *)ramAddr,
                                     rndState_ptr,
                                     trngParams_ptr,
                                     &roscToStart,
                                     trng);
        if (descrError == 0) {
            error = runContinuousTesting(ramAddr, *sourceOutSize_ptr);
            if (error == 0)
                break;
            *sourceOutSize_ptr = 0;
        } else {
            error = descrError;
        }

        // Update total processed ROSCs
        rndState_ptr->TrngProcesState |= ((rndState_ptr->TrngProcesState >> 8)
                                            & 0x00ff0000);
        // Clean started & not processed
        rndState_ptr->TrngProcesState &= 0x00ffffff;

        if (roscToStart == 0x8) {
            error = -1;
            break;
        } else {
            roscToStart <<= 1;
            error = startTrngHW(rndState_ptr, trngParams_ptr,
                                0 /*isRestart*/, &roscToStart,
                                trng);
            if (error != 0)
                goto End;
        }
    }

End:
    TurnOffTrng(trng);

    return error;
}

static int SetUserRngParameters(CCRndParams_t *pTrngParams)
{
    // Set TRNG parameters
    pTrngParams->SubSamplingRatio1 = CC_CONFIG_SAMPLE_CNT_ROSC_1;
    pTrngParams->SubSamplingRatio2 = CC_CONFIG_SAMPLE_CNT_ROSC_2;
    pTrngParams->SubSamplingRatio3 = CC_CONFIG_SAMPLE_CNT_ROSC_3;
    pTrngParams->SubSamplingRatio4 = CC_CONFIG_SAMPLE_CNT_ROSC_4;

    // Allowed ROSCs length b'0-3. If bit value 1 - appropriate ROSC is allowed.
    pTrngParams->RoscsAllowed = 0xf;
    pTrngParams->SubSamplingRatio = 0;

    return 0;
}

static int TrngGetSource(uint8_t *outAddr, uint32_t reqBytes, rv32_trng_t *trng)
{
    int error = 0;
    uint32_t rndWorkBuff[CC_RND_WORK_BUFFER_SIZE_WORDS];
    CCRndParams_t rndParams;
    CCRndState_t rndState = {0};
    uint32_t *rndSrc_ptr;
    uint32_t sourceOutSizeBytes = 0;

    if ((outAddr == NULL) || (reqBytes == 0) || (trng == NULL))
        return -1;

    // zero the rnd buff
    memset((uint8_t *)rndWorkBuff, 0, CC_RND_WORK_BUFFER_SIZE_BYTES);
    memset((uint8_t *)&rndParams, 0, sizeof(CCRndParams_t));

    // Get parameters and set them in the RND structures
    error = SetUserRngParameters(&rndParams);
    if (error != 0)
        return error;

    while (reqBytes > 0) {
        // Get TRNG Source
        error = getTrngSource(
                    &rndState, &rndParams, 0,
                    &rndSrc_ptr, &sourceOutSizeBytes,
                    rndWorkBuff, 0 /*isStartup*/,
                    trng);
        if (error) {
            // memset 0 to outAddr for security concern
            memset(outAddr, 0, reqBytes);
            return error;
        }

        if (reqBytes < sourceOutSizeBytes) {
            memcpy(outAddr, (uint8_t *)rndSrc_ptr, reqBytes);
            reqBytes = 0;
        } else {
            memcpy(outAddr, (uint8_t *)rndSrc_ptr, sourceOutSizeBytes);
            reqBytes -= sourceOutSizeBytes;
            outAddr += sourceOutSizeBytes;
        }
    }

    return error;
}

static int TrngGetSourceFast(uint8_t *outAddr, uint32_t reqBytes, rv32_trng_t *trng)
{
    int error = 0;
    CCRndParams_t rndParams;
    CCRndState_t rndState = {0};
    uint32_t roscToStart, i;

    if ((outAddr == NULL) || (reqBytes == 0) || (trng == NULL))
        return -1;

    // Zero the rnd buff
    memset((uint8_t *)&rndParams, 0, sizeof(CCRndParams_t));

    // Get parameters and set them in the RND structures
    error = SetUserRngParameters(&rndParams);
    if (error != 0)
        return error;

    error = startTrngHW(&rndState, &rndParams, 1 /*isRestart*/, &roscToStart, trng);

    for (i = 0; i < LLF_RND_NUM_OF_ROSCS; i++) {
        error = readMultipleEHR(reqBytes, outAddr, &rndState,
                                &rndParams, &roscToStart, trng);
        if (error == 0)
            return 0;

        // Update total processed ROSCs
        rndState.TrngProcesState |= ((rndState.TrngProcesState >> 8) & 0x00ff0000);
        // Clean started & not processed
        rndState.TrngProcesState &= 0x00ffffff;

        // Call StartTrng, with next ROSC
        roscToStart <<= 1;
    }

    // memset 0 to outAddr for security concern
    memset(outAddr, 0, reqBytes);

    return error;
}

void TrngInitialize(void)
{
}

int Trng0GetSource(uint8_t *outAddr, uint32_t reqBytes)
{
    int ret;

    //TODO
    //MISC_Enable_TRNG0();

    ret = TrngGetSource(outAddr, reqBytes, RV32_TRNG0);

    //TODO
    //MISC_Disable_TRNG0();

    return ret;
}

int Trng0GetSourceFast(uint8_t *outAddr, uint32_t reqBytes)
{
    int ret;

    //TODO
    //MISC_Enable_TRNG0();

    ret = TrngGetSourceFast(outAddr, reqBytes, RV32_TRNG0);

    //TODO
    //MISC_Disable_TRNG0

    return ret;
}
