#include <stdio.h>
#include <stdint.h>
#include <platform.h>
#include <rv_dma.h>

#define FLASH_SRCADDR 0x20000000
#define SRCADDR 0x81e000
#define DSTADDR 0x81f000
#define BUFSZ   0x100

#define DMA_CHANNEL_NUM 0

DRIVER_DMAC *DMAC0 = &driver_dma0;

static volatile int dma_complete_flag = 0;

void cb_event (uint32_t event)
{
    switch(event) {
    case DMA_EVENT_COMPLETE:
        dma_complete_flag = 1;
        break;
    case DMA_EVENT_PROGRAM_ERR:
    case DMA_EVENT_TRANSFER_ERR:
    default:
        dma_complete_flag = -1;
    }
}

void prepare_buffer(char *name, char *buff, uint32_t size, char c)
{
    int i;

    printf("Prepare %s buffer\n", name);
    for (i = 0; i < size; i++) {
        *(buff+i) = c;
    }
}

int check_buffers(char *src, char *dst, uint32_t size)
{
    int i;

    printf("Checking buffers...\n");
    for (i = 0; i < size; i++) {
        if (*(src+i) != *(dst+i))
            return 1;
    }
    return 0;
}

int dma_test(void)
{
    char *src, *dst;
    uint32_t control, stat;

    printf("Start to test DMA!\n");

    printf("1. SRAM to SRAM\n");
    // Prepare buffers for DMA
    src = (char *)SRCADDR;
    prepare_buffer("source", src, BUFSZ, 'a');

    dst = (char *)DSTADDR;
    prepare_buffer("destination", dst, BUFSZ, '0');

    // Copy source to destination through DMA
    // DMA controller initialization
    printf("Initialize DMAC\n");
    DMAC0->initialize();

    // Enable the channel
    DMAC0->enable(DMA_CHANNEL_NUM);

    // Check if the channel is busy
    while (DMAC0->get_status(DMA_CHANNEL_NUM) & STAT_BUSY_Msk) {}; 

    // Reset the channel (Optional)

    // Configure src, dst and sz
    // Configure direct transfer mode
    // Configure address mode and width
    // Configure interrupt mode (enable)
    control = (0U << DMAC_MCx_TR_EN_Pos) |
              (0U << DMAC_MCx_SAR_MODE_Pos) |
              (0U << DMAC_MCx_DAR_MODE_Pos) |
              (0U << DMAC_MCx_SIZE_Pos) |
              DMAC_MCx_CC_EN_Msk | DMAC_MCx_PE_EN_Msk | DMAC_MCx_TE_EN_Msk;
    stat = DMAC0->configure(DMA_CHANNEL_NUM, (uint32_t)src, (uint32_t)dst,
                            BUFSZ, control, cb_event);
    if (stat == -1) {
        printf("DMA configure error!\n");
        goto err;
    }

    // Start to transfer
    printf("Start to transfer...\n");
    DMAC0->start_transfer(DMA_CHANNEL_NUM);

    // Check if the transaction has completed:
    //   the interrupt handler will set the flag
    while (dma_complete_flag == 0) {};

    printf("%ld bytes (should be %d) have been transfered by DMA.\n",
           DMAC0->get_count(DMA_CHANNEL_NUM), BUFSZ);

    // Disable the Channel
    DMAC0->disable(DMA_CHANNEL_NUM);

    // Shutdown DMA controller
    DMAC0->uninitialize();

    // Check the result
    if (!check_buffers(src, dst, BUFSZ)) {
        printf("Destination buffer has been verified\n");
    } else
        goto err;

    ///////////////////////////////////////////////
    ///////////////////////////////////////////////
    printf("2. Flash to SRAM\n");
    dma_complete_flag = 0;
    src = (char *)FLASH_SRCADDR; // Flash address
    // Prepare buffers for DMA
    dst = (char *)DSTADDR;
    prepare_buffer("destination", dst, BUFSZ, '0');

    // Copy source to destination through DMA
    // DMA controller initialization
    printf("Initialize DMAC\n");
    DMAC0->initialize();

    // Enable the channel
    DMAC0->enable(DMA_CHANNEL_NUM);

    // Check if the channel is busy
    while (DMAC0->get_status(DMA_CHANNEL_NUM) & STAT_BUSY_Msk) {};

    // Reset the channel (Optional)

    // Configure src, dst and sz
    // Configure direct transfer mode
    // Configure address mode and width
    // Configure interrupt mode (enable)
    control = (0U << DMAC_MCx_TR_EN_Pos) |
              (0U << DMAC_MCx_SAR_MODE_Pos) |
              (0U << DMAC_MCx_DAR_MODE_Pos) |
              (0U << DMAC_MCx_SIZE_Pos) |
              DMAC_MCx_CC_EN_Msk | DMAC_MCx_PE_EN_Msk | DMAC_MCx_TE_EN_Msk;
    stat = DMAC0->configure(DMA_CHANNEL_NUM, (uint32_t)src, (uint32_t)dst,
                            BUFSZ, control, cb_event);
    if (stat == -1) {
        printf("DMA configure error!\n");
        goto err;
    }

    // Start to transfer
    printf("Start to transfer...\n");
    DMAC0->start_transfer(DMA_CHANNEL_NUM);

    // Check if the transaction has completed:
    //   the interrupt handler will set the flag
    while (dma_complete_flag == 0) {};

    printf("%ld bytes (should be %d) have been transfered by DMA.\n",
           DMAC0->get_count(DMA_CHANNEL_NUM), BUFSZ);

    // Disable the Channel
    DMAC0->disable(DMA_CHANNEL_NUM);

    // Shutdown DMA controller
    DMAC0->uninitialize();

    // Check the result
    if (!check_buffers(src, dst, BUFSZ)) {
        printf("Destination buffer has been verified\n");
    } else
        goto err;

    printf("DMA work corretly.\n");
    return 0;

err:
    printf("DMA work incorrectly.\n");
    return -1;
}
