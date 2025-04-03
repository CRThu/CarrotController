#include "bsp_inc.h"

io_t spi_ios[] =
{
    {.btb_pin = 17, .pin_name = "NSSA", .port = GPIO_PORT(A), .pin = GPIO_PIN(4),  .func = BSP_IO_FUNC_PERH, .state = IO_STATE_RESERVED },
    {.btb_pin = 23, .pin_name = "SCKA", .port = GPIO_PORT(B), .pin = GPIO_PIN(3),  .func = BSP_IO_FUNC_PERH, .state = IO_STATE_RESERVED },
    {.btb_pin = 25, .pin_name = "SDIA", .port = GPIO_PORT(B), .pin = GPIO_PIN(5),  .func = BSP_IO_FUNC_PERH, .state = IO_STATE_RESERVED },
    {.btb_pin = 27, .pin_name = "SDOA", .port = GPIO_PORT(B), .pin = GPIO_PIN(4),  .func = BSP_IO_FUNC_PERH, .state = IO_STATE_RESERVED },
    {.btb_pin = 19, .pin_name = "NSSB", .port = GPIO_PORT(A), .pin = GPIO_PIN(15), .func = BSP_IO_FUNC_PERH, .state = IO_STATE_RESERVED },
    {.btb_pin = 24, .pin_name = "SCKB", .port = GPIO_PORT(C), .pin = GPIO_PIN(10), .func = BSP_IO_FUNC_PERH, .state = IO_STATE_RESERVED },
    {.btb_pin = 26, .pin_name = "SDIB", .port = GPIO_PORT(C), .pin = GPIO_PIN(12), .func = BSP_IO_FUNC_PERH, .state = IO_STATE_RESERVED },
    {.btb_pin = 28, .pin_name = "SDOB", .port = GPIO_PORT(C), .pin = GPIO_PIN(11), .func = BSP_IO_FUNC_PERH, .state = IO_STATE_RESERVED },

    {.btb_pin = IO_ARR_END_ID }
};

void bsp_spi_init()
{
    io_t* io;
    io = dut_get_io(spi_ios, "NSSA");
    BSP_IO_TYPE(io, IO_TYPE_IN);
    BSP_IO_SPEED(io, IO_SPEED_NORMAL);
    BSP_IO_WRITE(io, IO_STATE_LOW);

    io = dut_get_io(spi_ios, "SCKA");
    BSP_IO_TYPE(io, IO_TYPE_IN);
    BSP_IO_SPEED(io, IO_SPEED_NORMAL);
    BSP_IO_WRITE(io, IO_STATE_LOW);

    io = dut_get_io(spi_ios, "SDIA");
    BSP_IO_TYPE(io, IO_TYPE_IN);
    BSP_IO_SPEED(io, IO_SPEED_NORMAL);
    BSP_IO_WRITE(io, IO_STATE_LOW);

    io = dut_get_io(spi_ios, "SDOA");
    BSP_IO_TYPE(io, IO_TYPE_IN);
    BSP_IO_SPEED(io, IO_SPEED_NORMAL);
    BSP_IO_WRITE(io, IO_STATE_LOW);

    io = dut_get_io(spi_ios, "NSSB");
    BSP_IO_TYPE(io, IO_TYPE_IN);
    BSP_IO_SPEED(io, IO_SPEED_NORMAL);
    BSP_IO_WRITE(io, IO_STATE_LOW);

    io = dut_get_io(spi_ios, "CLKB");
    BSP_IO_TYPE(io, IO_TYPE_IN);
    BSP_IO_SPEED(io, IO_SPEED_NORMAL);
    BSP_IO_WRITE(io, IO_STATE_LOW);

    io = dut_get_io(spi_ios, "SDIB");
    BSP_IO_TYPE(io, IO_TYPE_IN);
    BSP_IO_SPEED(io, IO_SPEED_NORMAL);
    BSP_IO_WRITE(io, IO_STATE_LOW);

    io = dut_get_io(spi_ios, "SDOB");
    BSP_IO_TYPE(io, IO_TYPE_IN);
    BSP_IO_SPEED(io, IO_SPEED_NORMAL);
    BSP_IO_WRITE(io, IO_STATE_LOW);
}