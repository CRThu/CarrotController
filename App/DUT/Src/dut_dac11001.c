#include "dut_inc.h"

dut_interface_t dac11001_profile =
{
    .id = 0,
    .name = "DAC11001",

    .preset_id = 0,
    .preset_name = "2 HARDWARE SPI COMM",

    .pin_configs = (io_t[]) {
        {.btb_pin = 11, .pin_name = "#LDAC1",    .port = GPIO_PORT(A), .pin = GPIO_PIN(1),  .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = 12, .pin_name = "#LDAC2",    .port = GPIO_PORT(C), .pin = GPIO_PIN(2),  .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = 17, .pin_name = "#SYNC1",    .port = GPIO_PORT(A), .pin = GPIO_PIN(4),  .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = 19, .pin_name = "#SYNC2",    .port = GPIO_PORT(A), .pin = GPIO_PIN(15), .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = 23, .pin_name = "SPIA_SCK",  .port = GPIO_PORT(B), .pin = GPIO_PIN(3),  .func = BSP_IO_FUNC_SPI_SCK,  .state = IO_STATE_RESERVED },
        {.btb_pin = 25, .pin_name = "SPIA_MOSI", .port = GPIO_PORT(B), .pin = GPIO_PIN(5),  .func = BSP_IO_FUNC_SPI_MOSI, .state = IO_STATE_RESERVED },
        {.btb_pin = 27, .pin_name = "SPIA_MISO", .port = GPIO_PORT(B), .pin = GPIO_PIN(4),  .func = BSP_IO_FUNC_SPI_MISO, .state = IO_STATE_RESERVED },
        {.btb_pin = 24, .pin_name = "SPIB_SCK",  .port = GPIO_PORT(C), .pin = GPIO_PIN(10), .func = BSP_IO_FUNC_SPI_SCK,  .state = IO_STATE_RESERVED },
        {.btb_pin = 26, .pin_name = "SPIB_MOSI", .port = GPIO_PORT(C), .pin = GPIO_PIN(12), .func = BSP_IO_FUNC_SPI_MOSI, .state = IO_STATE_RESERVED },
        {.btb_pin = 28, .pin_name = "SPIB_MISO", .port = GPIO_PORT(C), .pin = GPIO_PIN(11), .func = BSP_IO_FUNC_SPI_MISO, .state = IO_STATE_RESERVED },
        {.btb_pin = 51, .pin_name = "#CLR1",     .port = GPIO_PORT(E), .pin = GPIO_PIN(14), .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = 52, .pin_name = "#CLR2",     .port = GPIO_PORT(E), .pin = GPIO_PIN(15), .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = IO_ARR_END_ID}
    },

    .switch_value = SWITCH_EN(1)
                  | SWITCH_EN(4)
                  | SWITCH_EN(6) ,

    .perh = {
        &spi_instances[0],
        &spi_instances[1],
        NULL
    }
};
