#include "bsp_inc.h"

__weak SPI_HandleTypeDef hspi1;
__weak SPI_HandleTypeDef hspi3;

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

spi_t* bsp_spi[] =
{
    &hspi1,
    &hspi3
};

__FORCEINLINE spi_t* bsp_get_spi_instance(uint8_t index)
{
    return bsp_spi[index];
}

__FORCEINLINE int8_t bsp_get_spi_index(spi_t* spi)
{
    for (int i = 0;i < sizeof(bsp_spi) / sizeof(spi_t*); i++)
    {
        if (spi == bsp_spi[i])
            return i;
    }
    return -1;
}

void bsp_spi_io_config(spi_t* spi, bsp_spi_io_mode spi_io_mode)
{
    int8_t index = bsp_get_spi_index(spi);

    /* IO INITIAL */
    io_t* io;

    /* SCKx io initial */
    io = dut_get_io_id(spi_io_cfg, index, "SCK");
    if (spi_io_mode == BSP_SPI_IO_MODE_OFF)
    {
        bsp_io_setup_unused(io);
    }
    else
    {
        bsp_io_setup_af(io, io->af, IO_SPEED_FAST);
    }

    /* NSSx io initial */
    io = dut_get_io_id(spi_io_cfg, index, "NSS");
    if ((spi_io_mode == BSP_SPI_IO_MODE_OFF) || (~spi_io_mode & BSP_SPI_MODE_CS_EN))
    {
        bsp_io_setup_unused(io);
    }
    else
    {
        bsp_io_setup_af(io, io->af, IO_SPEED_FAST);
    }

    /* SDOx io initial */
    io = dut_get_io_id(spi_io_cfg, index, "SDO");
    if ((spi_io_mode == BSP_SPI_IO_MODE_OFF) || (~spi_io_mode & BSP_SPI_MODE_RX_EN))
    {
        bsp_io_setup_unused(io);
    }
    else
    {
        bsp_io_setup_af(io, io->af, IO_SPEED_FAST);
    }

    /* SDIx io initial */
    io = dut_get_io_id(spi_io_cfg, index, "SDI");
    if ((spi_io_mode == BSP_SPI_IO_MODE_OFF) || (~spi_io_mode & BSP_SPI_MODE_TX_EN))
    {
        bsp_io_setup_unused(io);
    }
    else
    {
        bsp_io_setup_af(io, io->af, IO_SPEED_FAST);
    }

    /* PERH initial */
    if (spi_io_mode != BSP_SPI_IO_MODE_OFF)
    {
        (spi->Init).Direction = SPI_DIRECTION_2LINES;

        // (spi_io_mode & BSP_SPI_MODE_TX_EN)
        //     ? ((spi_io_mode & BSP_SPI_MODE_RX_EN)
        //         ? SPI_DIRECTION_2LINES
        //         : SPI_DIRECTION_2LINES_TXONLY)
        //     : SPI_DIRECTION_1LINE;

        (spi->Init).NSS = (spi_io_mode & BSP_SPI_MODE_CS_EN)
            ? ((spi_io_mode & BSP_SPI_MODE_CS_IN)
                ? SPI_NSS_HARD_INPUT
                : SPI_NSS_HARD_OUTPUT)
            : SPI_NSS_SOFT;
    }
}

void bsp_spi_io_config_all(bsp_spi_io_mode spi_io_mode)
{
    for (int i = 0; i < sizeof(bsp_spi) / sizeof(spi_t*); i++)
    {
        bsp_spi_io_config(bsp_spi[i], spi_io_mode);
    }
}

void bsp_spi_perh_config(spi_t* spi, bsp_spi_mode master, bsp_spi_data_size datasize, bsp_spi_clk_psc psc, bsp_spi_cpha cpha, bsp_spi_cpol cpol)
{
    int8_t index = bsp_get_spi_index(spi);

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

    /* PERH initial */
    //spi->Instance = SPI1;
    //spi->Init.Mode = SPI_MODE_MASTER;
    spi->Init.Mode = master;
    //sspi->Init.Direction = SPI_DIRECTION_2LINES;
    //sspi->Init.DataSize = SPI_DATASIZE_16BIT;
    spi->Init.DataSize = datasize;
    //spi->Init.CLKPolarity = SPI_POLARITY_LOW;
    spi->Init.CLKPolarity = cpol;
    //spi->Init.CLKPhase = SPI_PHASE_1EDGE;
    spi->Init.CLKPhase = cpha;
    //spi->Init.NSS = SPI_NSS_HARD_OUTPUT;
    //spi->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
    spi->Init.BaudRatePrescaler = (master == BSP_SPI_MODE_MASTER) ? psc : SPI_BAUDRATEPRESCALER_BYPASS;
    spi->Init.FirstBit = SPI_FIRSTBIT_MSB;
    spi->Init.TIMode = SPI_TIMODE_DISABLE;
    spi->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    spi->Init.CRCPolynomial = 0x7;
    spi->Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
    spi->Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
    spi->Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
    spi->Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
    spi->Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
    spi->Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
    spi->Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_ENABLE;
    spi->Init.IOSwap = (master == BSP_SPI_MODE_MASTER) ? SPI_IO_SWAP_DISABLE : SPI_IO_SWAP_ENABLE;
    spi->Init.ReadyMasterManagement = SPI_RDY_MASTER_MANAGEMENT_INTERNALLY;
    spi->Init.ReadyPolarity = SPI_RDY_POLARITY_HIGH;
    if (HAL_SPI_Init(spi) != HAL_OK)
    {
        Error_Handler();
    }
}


// /**
//   * @brief This function handles SPI1 global interrupt.
//   */
// void SPI1_IRQHandler(void)
// {
//   /* USER CODE BEGIN SPI1_IRQn 0 */

//   /* USER CODE END SPI1_IRQn 0 */
//   HAL_SPI_IRQHandler(&hspi1);
//   /* USER CODE BEGIN SPI1_IRQn 1 */

//   /* USER CODE END SPI1_IRQn 1 */
// }
