#include "bsp_inc.h"

io_t spi_io_cfg[] =
{
    {.btb_pin = 17, .pin_name = "NSS[0]", .port = GPIO_PORT(A), .pin = GPIO_PIN(4)  },
    {.btb_pin = 23, .pin_name = "SCK[0]", .port = GPIO_PORT(B), .pin = GPIO_PIN(3)  },
    {.btb_pin = 25, .pin_name = "SDI[0]", .port = GPIO_PORT(B), .pin = GPIO_PIN(5)  },
    {.btb_pin = 27, .pin_name = "SDO[0]", .port = GPIO_PORT(B), .pin = GPIO_PIN(4)  },
    {.btb_pin = 19, .pin_name = "NSS[1]", .port = GPIO_PORT(A), .pin = GPIO_PIN(15) },
    {.btb_pin = 24, .pin_name = "SCK[1]", .port = GPIO_PORT(C), .pin = GPIO_PIN(10) },
    {.btb_pin = 26, .pin_name = "SDI[1]", .port = GPIO_PORT(C), .pin = GPIO_PIN(12) },
    {.btb_pin = 28, .pin_name = "SDO[1]", .port = GPIO_PORT(C), .pin = GPIO_PIN(11) },

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
    io_t* io;

    /* SCKx io initial when SPI_OFF */
    if (spi_mode == BSP_SPI_MODE_OFF)
    {
        io = dut_get_io_id(spi_io_cfg, index, "SCK");
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }

    /* NSSx io initial when SPI_OFF || !CS_EN */
    if ((spi_mode == BSP_SPI_MODE_OFF) || (~spi_mode & BSP_SPI_MODE_CS_EN))
    {
        io = dut_get_io_id(spi_io_cfg, index, "NSSA");
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }

    /* SDOx io initial when SPI_OFF || !RX_EN */
    if ((spi_mode == BSP_SPI_MODE_OFF) || (~spi_mode & BSP_SPI_MODE_RX_EN))
    {
        io = dut_get_io_id(spi_io_cfg, index, "SDOA");
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }

    /* SDIx io initial when SPI_OFF || !TX_EN */
    if ((spi_mode == BSP_SPI_MODE_OFF) || (~spi_mode & BSP_SPI_MODE_TX_EN))
    {
        io = dut_get_io_id(spi_io_cfg, index, "SDIA");
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }
}

void bsp_spi_init_all(bsp_spi_mode spi_mode)
{
    for (int i = 0; i < sizeof(spi_instances) / sizeof(spi_t); i++)
    {
        bsp_spi_init(i, spi_mode);
    }
}