#ifndef __trng_h__
#define __trng_h__
#include <device.h>

typedef struct rv32_trng {
    volatile uint32_t RESERVED[64];
    volatile uint32_t IMR;
    volatile uint32_t ISR;
    volatile uint32_t ICR;
    volatile uint32_t CONFIG;
    volatile uint32_t VALID;
    volatile uint32_t EHR_DATA[6];
    volatile uint32_t RND_SOURCE_ENABLE;
    volatile uint32_t SAMPLE_CNT1;
    volatile uint32_t AUTOCORR_STATISTIC;
    volatile uint32_t DEBUG_CONTROL;
    volatile uint32_t RESERVED1;
    volatile uint32_t SW_RESET;
    volatile uint32_t RESERVED2[29];
    volatile uint32_t BUSY;
    volatile uint32_t RST_BITS_COUNTER;
    volatile uint32_t RESERVED3[8];
    volatile uint32_t RST_BIST_COUNTER[3];
} rv32_trng_t;

#define RV32_TRNG_VALID_EHR_VALID_Pos     (0UL)
#define RV32_TRNG_VALID_EHR_VALID_Msk     (0x1UL)

#define TRNG_MAX_CRNGT_ERRORS               (12)

#define LLF_RND_HW_DEBUG_CONTROL_VALUE_ON_TRNG90B_MODE  0x0000000A
#define LLF_RND_HW_DMA_EHR_SAMPLES_NUM_ON_TRNG90B_MODE  22UL

#define TRNG_EHR_SIZE                       6
#define LLF_RND_NUM_OF_ROSCS                4

/* sample count for each ring oscillator */
/* for unallowed rosc, sample count = 0 */
#define CC_CONFIG_SAMPLE_CNT_ROSC_1         200
#define CC_CONFIG_SAMPLE_CNT_ROSC_2         200
#define CC_CONFIG_SAMPLE_CNT_ROSC_3         300
#define CC_CONFIG_SAMPLE_CNT_ROSC_4         100

#define LLF_RND_HW_TRNG_EHR_WIDTH_IN_WORDS  6
#define LLF_RND_HW_TRNG_EHR_WIDTH_IN_BYTES  (LLF_RND_HW_TRNG_EHR_WIDTH_IN_WORDS * sizeof(uint32_t))
#define LLF_RND_TRNG90B_MAX_BYTES           (LLF_RND_HW_DMA_EHR_SAMPLES_NUM_ON_TRNG90B_MODE * LLF_RND_HW_TRNG_EHR_WIDTH_IN_BYTES)
#define CC_CONFIG_TRNG90B_ADAPTIVE_PROPORTION_WINDOW_SIZE      1024

/* ring oscillator offsets and numbers */
#define LLF_RND_HW_TRNG_ROSC0_BIT           0x1
#define LLF_RND_HW_TRNG_ROSC1_BIT           0x2
#define LLF_RND_HW_TRNG_ROSC2_BIT           0x4
#define LLF_RND_HW_TRNG_ROSC3_BIT           0x8
#define LLF_RND_HW_TRNG_ROSC0_NUM           0x0
#define LLF_RND_HW_TRNG_ROSC1_NUM           0x1
#define LLF_RND_HW_TRNG_ROSC2_NUM           0x2
#define LLF_RND_HW_TRNG_ROSC3_NUM           0x3

// -------------------------------------------------------
// TRNG register definitions
// -------------------------------------------------------
#define DX_RNG_IMR_EHR_VALID_INT_MASK_BIT_SHIFT      0x0UL
#define DX_RNG_IMR_EHR_VALID_INT_MASK_BIT_SIZE 	     0x1UL
#define DX_RNG_IMR_AUTOCORR_ERR_INT_MASK_BIT_SHIFT   0x1UL
#define DX_RNG_IMR_AUTOCORR_ERR_INT_MASK_BIT_SIZE    0x1UL
#define DX_RNG_IMR_CRNGT_ERR_INT_MASK_BIT_SHIFT      0x2UL
#define DX_RNG_IMR_CRNGT_ERR_INT_MASK_BIT_SIZE 	     0x1UL
#define DX_RNG_IMR_VN_ERR_INT_MASK_BIT_SHIFT         0x3UL
#define DX_RNG_IMR_VN_ERR_INT_MASK_BIT_SIZE          0x1UL

#define DX_RNG_ISR_EHR_VALID_BIT_SHIFT 	             0x0UL
#define DX_RNG_ISR_EHR_VALID_BIT_SIZE 	             0x1UL
#define DX_RNG_ISR_AUTOCORR_ERR_BIT_SHIFT            0x1UL
#define DX_RNG_ISR_AUTOCORR_ERR_BIT_SIZE             0x1UL
#define DX_RNG_ISR_CRNGT_ERR_BIT_SHIFT 	             0x2UL
#define DX_RNG_ISR_CRNGT_ERR_BIT_SIZE 	             0x1UL
#define DX_RNG_ISR_VN_ERR_BIT_SHIFT                  0x3UL
#define DX_RNG_ISR_VN_ERR_BIT_SIZE                   0x1UL

#define DX_RNG_ICR_EHR_VALID_BIT_SHIFT 	             0x0UL
#define DX_RNG_ICR_EHR_VALID_BIT_SIZE 	             0x1UL
#define DX_RNG_ICR_AUTOCORR_ERR_BIT_SHIFT            0x1UL
#define DX_RNG_ICR_AUTOCORR_ERR_BIT_SIZE             0x1UL
#define DX_RNG_ICR_CRNGT_ERR_BIT_SHIFT 	             0x2UL
#define DX_RNG_ICR_CRNGT_ERR_BIT_SIZE 	             0x1UL
#define DX_RNG_ICR_VN_ERR_BIT_SHIFT                  0x3UL
#define DX_RNG_ICR_VN_ERR_BIT_SIZE                   0x1UL

#define LLF_RND_HW_RND_SRC_ENABLE_VAL                1UL
#define LLF_RND_HW_RND_SRC_DISABLE_VAL               0UL
#define LLF_RND_HW_TRNG_WITH_DMA_CONFIG_VAL          0x4
#define LLF_RNG_INT_MASK_ON_TRNG90B_MODE             0xFFFFFFC5
#define LLF_RNG_INT_MASK_ON_FETRNG_MODE              0xFFFFFFEC


/* amount of bytes for the required entropy bits =
 *   ROUND_UP(
 *      ROUND_UP(((required entropy bits)/(entropy per bit)), 1024),
 *      (EHR width in bytes)) / 8
 *
 * (multiple of the window size 1024 bits and multiple of the EHR width 192
 * bits) */
#define CC_CONFIG_TRNG90B_AMOUNT_OF_BYTES            144  /* ROUND_UP(ROUND_UP((384/0.5), 1024), 192) / 8 = 144 */

/*** NIST SP 800-90B (2nd Draft) 4.4.1 ***/
/* C = ROUND_UP(1+(-log(W)/H)), W = 2^(-40), H=(entropy per bit) */
#define CC_CONFIG_TRNG90B_REPETITION_COUNTER_CUTOFF  81  /* ROUND_UP(1+(40/0.5)) = 81 */

/*** NIST SP 800-90B (2nd Draft) 4.4.2 ***/
/* C =CRITBINOM(W, power(2,(-H)),1-a), W = 1024, a = 2^(-40), H=(entropy per bit) */
#define CC_CONFIG_TRNG90B_ADAPTIVE_PROPORTION_CUTOFF 823      /* =CRITBINOM(1024, power(2,(-0.5)),1-2^(-40)) */

/*** For Startup Tests ***/
/* amount of bytes for the startup test = 528 (at least 4096 bits (NIST SP 800-90B (2nd Draft) 4.3.12) = 22 EHRs = 4224 bits) */
#define CC_CONFIG_TRNG90B_AMOUNT_OF_BYTES_STARTUP    528
/* Definitions of temp buffer for DMA */

/* the maximum possible usage of stack memory in words */
#define CC_RND_WORK_BUFFER_SIZE_WORDS                (CC_CONFIG_TRNG90B_AMOUNT_OF_BYTES_STARTUP / 4)
/* the maximum possible usage of stack memory in words */
#define CC_RND_WORK_BUFFER_SIZE_BYTES                (CC_RND_WORK_BUFFER_SIZE_WORDS * sizeof(uint32_t))

/* The CRYS Random Generator Parameters  structure CCRndParams_t -
   structure containing the user given Parameters */
typedef struct CCRndParams_t {
  /* allowed ring oscillator lengths: bits 0,1,2,3  */
  uint32_t  RoscsAllowed;

  /* sampling interval: count of ring oscillator cycles between consecutive bits sampling */
  uint32_t  SubSamplingRatio;
  uint32_t  SubSamplingRatio1;
  uint32_t  SubSamplingRatio2;
  uint32_t  SubSamplingRatio3;
  uint32_t  SubSamplingRatio4;

} CCRndParams_t;

/*! RND state structure. Includes internal data that needs to be saved between boots by the user.*/
typedef struct {
  /* State flag (see definition of StateFlag above), containing bit-fields, defining:
     - b'0: instantiation steps:   0 - not done, 1 - done;
     - 2b'9,8: working or testing mode: 0 - working, 1 - KAT DRBG test, 2 - KAT TRNG test;
     - b'16: flag defining is Previous random valid or not: 0 - not valid, 1 - valid */
  /*! State flag used internally in the code.*/
  uint32_t StateFlag;

  /* Trng processing flag - indicates which ROSC lengths are:
     -  allowed (bits 0-3);
     -  total started (bits 8-11);
     -  processed (bits 16-19);
     -  started, but not processed (bits24-27)       */
  /*! TRNG process state used internally in the code */
  uint32_t TrngProcesState;

} CCRndState_t;

void TrngInitialize(void);

int TrngXorGetSource(uint8_t *outAddr, uint32_t reqBytes);
int Trng0GetSource(uint8_t *outAddr, uint32_t reqBytes);
int Trng1GetSource(uint8_t *outAddr, uint32_t reqBytes);
int Trng2GetSource(uint8_t *outAddr, uint32_t reqBytes);
int Trng3GetSource(uint8_t *outAddr, uint32_t reqBytes);

int TrngXorGetSourceFast(uint8_t *outAddr, uint32_t reqBytes);
int Trng0GetSourceFast(uint8_t *outAddr, uint32_t reqBytes);
int Trng1GetSourceFast(uint8_t *outAddr, uint32_t reqBytes);
int Trng2GetSourceFast(uint8_t *outAddr, uint32_t reqBytes);
int Trng3GetSourceFast(uint8_t *outAddr, uint32_t reqBytes);

#endif
