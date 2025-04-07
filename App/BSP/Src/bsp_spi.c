#include "bsp_inc.h"

io_t spi_io_cfg[] =
{
    {.btb_pin = 17, .pin_name = "NSS[0]", .port = GPIO_PORT(A), .pin = GPIO_PIN(4) , .af = GPIO_AF5_SPI1 },
    {.btb_pin = 23, .pin_name = "SCK[0]", .port = GPIO_PORT(B), .pin = GPIO_PIN(3) , .af = GPIO_AF5_SPI1 },
    {.btb_pin = 25, .pin_name = "SDI[0]", .port = GPIO_PORT(B), .pin = GPIO_PIN(5) , .af = GPIO_AF5_SPI1 },
    {.btb_pin = 27, .pin_name = "SDO[0]", .port = GPIO_PORT(B), .pin = GPIO_PIN(4) , .af = GPIO_AF5_SPI1 },
    {.btb_pin = 19, .pin_name = "NSS[1]", .port = GPIO_PORT(A), .pin = GPIO_PIN(15), .af = GPIO_AF6_SPI3 },
    {.btb_pin = 24, .pin_name = "SCK[1]", .port = GPIO_PORT(C), .pin = GPIO_PIN(10), .af = GPIO_AF6_SPI3 },
    {.btb_pin = 26, .pin_name = "SDI[1]", .port = GPIO_PORT(C), .pin = GPIO_PIN(12), .af = GPIO_AF6_SPI3 },
    {.btb_pin = 28, .pin_name = "SDO[1]", .port = GPIO_PORT(C), .pin = GPIO_PIN(11), .af = GPIO_AF6_SPI3 },

    {.btb_pin = IO_ARR_END_ID }
};

spi_t spi_instances[] =
{
    {.Instance = SPI1},
    {.Instance = SPI3}
};

__FORCEINLINE spi_t* bsp_get_spi_instance(uint8_t index)
{
    return &spi_instances[index];
}

void bsp_spi_init(uint8_t index, bsp_spi_mode spi_mode)
{
    /* CLOCK CONFIG */
    switch (index)
    {
    case 0:
        __HAL_RCC_SPI1_CONFIG(RCC_SPI1CLKSOURCE_PLL2P);
        __HAL_RCC_SPI1_CLK_ENABLE();
        break;
    case 1:
        __HAL_RCC_SPI3_CONFIG(RCC_SPI3CLKSOURCE_PLL2P);
        __HAL_RCC_SPI3_CLK_ENABLE();
    default:
        break;
    }

    /* IO INITIAL */
    io_t* io;

    /* SCKx io initial */
    io = dut_get_io_id(spi_io_cfg, index, "SCK");
    if (spi_mode == BSP_SPI_MODE_OFF)
    {
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }
    else
    {
        BSP_IO_SET_AF(io);
        BSP_IO_TYPE(io, IO_TYPE_PERH);
        BSP_IO_SPEED(io, IO_SPEED_FAST);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }

    /* NSSx io initial */
    io = dut_get_io_id(spi_io_cfg, index, "NSS");
    if ((spi_mode == BSP_SPI_MODE_OFF) || (~spi_mode & BSP_SPI_MODE_CS_EN))
    {
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }
    else
    {
        BSP_IO_SET_AF(io);
        BSP_IO_TYPE(io, IO_TYPE_PERH);
        BSP_IO_SPEED(io, IO_SPEED_FAST);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }

    /* SDOx io initial */
    io = dut_get_io_id(spi_io_cfg, index, "SDO");
    if ((spi_mode == BSP_SPI_MODE_OFF) || (~spi_mode & BSP_SPI_MODE_RX_EN))
    {
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }
    else
    {
        BSP_IO_SET_AF(io);
        BSP_IO_TYPE(io, IO_TYPE_PERH);
        BSP_IO_SPEED(io, IO_SPEED_FAST);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }

    /* SDIx io initial */
    io = dut_get_io_id(spi_io_cfg, index, "SDI");
    if ((spi_mode == BSP_SPI_MODE_OFF) || (~spi_mode & BSP_SPI_MODE_TX_EN))
    {
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }
    else
    {
        BSP_IO_SET_AF(io);
        BSP_IO_TYPE(io, IO_TYPE_PERH);
        BSP_IO_SPEED(io, IO_SPEED_FAST);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }

    /* PERH initial */
    spi_instances[index].Instance = SPI1;
    spi_instances[index].Init.Mode = SPI_MODE_MASTER;
    spi_instances[index].Init.Direction = SPI_DIRECTION_2LINES;
    spi_instances[index].Init.DataSize = SPI_DATASIZE_8BIT;
    spi_instances[index].Init.CLKPolarity = SPI_POLARITY_LOW;
    spi_instances[index].Init.CLKPhase = SPI_PHASE_1EDGE;
    spi_instances[index].Init.NSS = SPI_NSS_HARD_OUTPUT;
    spi_instances[index].Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    spi_instances[index].Init.FirstBit = SPI_FIRSTBIT_MSB;
    spi_instances[index].Init.TIMode = SPI_TIMODE_DISABLE;
    spi_instances[index].Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    spi_instances[index].Init.CRCPolynomial = 0x7;
    spi_instances[index].Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
    spi_instances[index].Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
    spi_instances[index].Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
    spi_instances[index].Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_04CYCLE;
    spi_instances[index].Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
    spi_instances[index].Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
    spi_instances[index].Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;
    spi_instances[index].Init.IOSwap = SPI_IO_SWAP_DISABLE;
    spi_instances[index].Init.ReadyMasterManagement = SPI_RDY_MASTER_MANAGEMENT_INTERNALLY;
    spi_instances[index].Init.ReadyPolarity = SPI_RDY_POLARITY_HIGH;
    if (HAL_SPI_Init(&spi_instances[index]) != HAL_OK)
    {
        Error_Handler();
    }
}

void bsp_spi_init_all(bsp_spi_mode spi_mode)
{
    for (int i = 0; i < sizeof(spi_instances) / sizeof(spi_t); i++)
    {
        bsp_spi_init(i, spi_mode);
    }
}