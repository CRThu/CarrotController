#include "bsp_inc.h"

io_t spi_io_cfg[] =
{
    {.btb_pin = 17, .pin_name = "NSSA", .port = GPIO_PORT(A), .pin = GPIO_PIN(4)  },
    {.btb_pin = 23, .pin_name = "SCKA", .port = GPIO_PORT(B), .pin = GPIO_PIN(3)  },
    {.btb_pin = 25, .pin_name = "SDIA", .port = GPIO_PORT(B), .pin = GPIO_PIN(5)  },
    {.btb_pin = 27, .pin_name = "SDOA", .port = GPIO_PORT(B), .pin = GPIO_PIN(4)  },
    {.btb_pin = 19, .pin_name = "NSSB", .port = GPIO_PORT(A), .pin = GPIO_PIN(15) },
    {.btb_pin = 24, .pin_name = "SCKB", .port = GPIO_PORT(C), .pin = GPIO_PIN(10) },
    {.btb_pin = 26, .pin_name = "SDIB", .port = GPIO_PORT(C), .pin = GPIO_PIN(12) },
    {.btb_pin = 28, .pin_name = "SDOB", .port = GPIO_PORT(C), .pin = GPIO_PIN(11) },

    {.btb_pin = IO_ARR_END_ID }
};

void bsp_spi_init(bsp_spi_mode spi_a_mode, bsp_spi_mode spi_b_mode)
{
    io_t* io;
    
    /* SCKx io initial when SPI_OFF */
    if (spi_a_mode == BSP_SPI_MODE_OFF)
    {
        io = dut_get_io(spi_io_cfg, "SCKA");
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);

        io = dut_get_io(spi_io_cfg, "SCKB");
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }

    /* NSSx io initial when SPI_OFF || !CS_EN */
    if ((spi_a_mode == BSP_SPI_MODE_OFF) || (~spi_a_mode & BSP_SPI_MODE_CS_EN))
    {
        io = dut_get_io(spi_io_cfg, "NSSA");
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }
    if ((spi_b_mode == BSP_SPI_MODE_OFF) || (~spi_b_mode & BSP_SPI_MODE_CS_EN))
    {
        io = dut_get_io(spi_io_cfg, "NSSB");
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }
    
    /* SDOx io initial when SPI_OFF || !RX_EN */
    if ((spi_a_mode == BSP_SPI_MODE_OFF) || (~spi_a_mode & BSP_SPI_MODE_RX_EN))
    {
        io = dut_get_io(spi_io_cfg, "SDOA");
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }
    if ((spi_b_mode == BSP_SPI_MODE_OFF) || (~spi_b_mode & BSP_SPI_MODE_RX_EN))
    {
        io = dut_get_io(spi_io_cfg, "SDOB");
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }
    
    /* SDIx io initial when SPI_OFF || !TX_EN */
    if ((spi_a_mode == BSP_SPI_MODE_OFF) || (~spi_a_mode & BSP_SPI_MODE_TX_EN))
    {
        io = dut_get_io(spi_io_cfg, "SDIA");
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }
    if ((spi_b_mode == BSP_SPI_MODE_OFF) || (~spi_b_mode & BSP_SPI_MODE_TX_EN))
    {
        io = dut_get_io(spi_io_cfg, "SDIB");
        BSP_IO_TYPE(io, IO_TYPE_IN);
        BSP_IO_SPEED(io, IO_SPEED_NORMAL);
        BSP_IO_WRITE(io, IO_STATE_LOW);
    }
}