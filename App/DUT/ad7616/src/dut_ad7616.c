#include "dut_ad7616.h"

dut_interface_t ad7616_profiles[] =
{
    {
        .id = 0x7616,
        .name = "AD7616",

        .preset_id = 0,
        .preset_name = "Parallel software mode",

        .pin_configs = (io_t[]) {
            { .btb_pin = 11, .pin_name = "CONVST"     , .port = GPIO_PORT(A), .pin = GPIO_PIN( 1),  .func = BSP_IO_FUNC_OUT  , .state = IO_STATE_LOW      },
            { .btb_pin = 13, .pin_name = "BUSY"       , .port = GPIO_PORT(A), .pin = GPIO_PIN( 0),  .func = BSP_IO_FUNC_IN   , .state = IO_STATE_RESERVED },
         // { .btb_pin = 17, .pin_name = "nCS"        , .port = GPIO_PORT(A), .pin = GPIO_PIN( 4),  .func = BSP_IO_FUNC_NONE , .state = IO_STATE_RESERVED },
         // { .btb_pin = 23, .pin_name = "SCLK/nRD"   , .port = GPIO_PORT(B), .pin = GPIO_PIN( 3),  .func = BSP_IO_FUNC_NONE , .state = IO_STATE_RESERVED },
         // { .btb_pin = 25, .pin_name = "DB10/SDI"   , .port = GPIO_PORT(B), .pin = GPIO_PIN( 5),  .func = BSP_IO_FUNC_NONE , .state = IO_STATE_RESERVED },
         // { .btb_pin = 27, .pin_name = "DB12/SDOA"  , .port = GPIO_PORT(B), .pin = GPIO_PIN( 4),  .func = BSP_IO_FUNC_NONE , .state = IO_STATE_RESERVED },
         // { .btb_pin = 19, .pin_name = "nCS"        , .port = GPIO_PORT(A), .pin = GPIO_PIN(15),  .func = BSP_IO_FUNC_NONE , .state = IO_STATE_RESERVED },
         // { .btb_pin = 24, .pin_name = "SCLK/nRD"   , .port = GPIO_PORT(C), .pin = GPIO_PIN(10),  .func = BSP_IO_FUNC_NONE , .state = IO_STATE_RESERVED },
         // { .btb_pin = 26, .pin_name = "DB10/SDI"   , .port = GPIO_PORT(C), .pin = GPIO_PIN(12),  .func = BSP_IO_FUNC_NONE , .state = IO_STATE_RESERVED },
         // { .btb_pin = 28, .pin_name = "DB11/SDOB"  , .port = GPIO_PORT(C), .pin = GPIO_PIN(11),  .func = BSP_IO_FUNC_NONE , .state = IO_STATE_RESERVED },
         // { .btb_pin = 12, .pin_name = "CHSEL0"     , .port = GPIO_PORT(C), .pin = GPIO_PIN( 2),  .func = BSP_IO_FUNC_NONE , .state = IO_STATE_RESERVED },
         // { .btb_pin = 14, .pin_name = "CHSEL1"     , .port = GPIO_PORT(C), .pin = GPIO_PIN( 3),  .func = BSP_IO_FUNC_NONE , .state = IO_STATE_RESERVED },
         // { .btb_pin = 18, .pin_name = "CHSEL2"     , .port = GPIO_PORT(A), .pin = GPIO_PIN( 2),  .func = BSP_IO_FUNC_NONE , .state = IO_STATE_RESERVED },
         // { .btb_pin = 20, .pin_name = "SEQEN"      , .port = GPIO_PORT(A), .pin = GPIO_PIN( 3),  .func = BSP_IO_FUNC_NONE , .state = IO_STATE_RESERVED },
         // { .btb_pin = 55, .pin_name = "HW_RNGSEL1" , .port = GPIO_PORT(A), .pin = GPIO_PIN( 9),  .func = BSP_IO_FUNC_NONE , .state = IO_STATE_RESERVED },
         // { .btb_pin = 57, .pin_name = "HW_RNGSEL0" , .port = GPIO_PORT(A), .pin = GPIO_PIN(10),  .func = BSP_IO_FUNC_NONE , .state = IO_STATE_RESERVED },
            { .btb_pin = 31, .pin_name = "SER/nPAR"   , .port = GPIO_PORT(C), .pin = GPIO_PIN( 7),  .func = BSP_IO_FUNC_OUT  , .state = IO_STATE_LOW      },
            { .btb_pin = 49, .pin_name = "REFSEL"     , .port = GPIO_PORT(E), .pin = GPIO_PIN(12),  .func = BSP_IO_FUNC_OUT  , .state = IO_STATE_LOW      },
            { .btb_pin = 51, .pin_name = "nRESET"     , .port = GPIO_PORT(E), .pin = GPIO_PIN(14),  .func = BSP_IO_FUNC_OUT  , .state = IO_STATE_HIGH     },
            { .btb_pin = 32, .pin_name = "nCS"        , .port = GPIO_PORT(C), .pin = GPIO_PIN( 6),  .func = BSP_IO_FUNC_OUT  , .state = IO_STATE_HIGH     },
            { .btb_pin = 50, .pin_name = "SCLK/nRD"   , .port = GPIO_PORT(E), .pin = GPIO_PIN(13),  .func = BSP_IO_FUNC_OUT  , .state = IO_STATE_HIGH     },
            { .btb_pin = 52, .pin_name = "nWR/BURST"  , .port = GPIO_PORT(E), .pin = GPIO_PIN(15),  .func = BSP_IO_FUNC_OUT  , .state = IO_STATE_HIGH     },
            { .btb_pin = 34, .pin_name = "DB0"        , .port = GPIO_PORT(D), .pin = GPIO_PIN( 0),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            { .btb_pin = 36, .pin_name = "DB1"        , .port = GPIO_PORT(D), .pin = GPIO_PIN( 1),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            { .btb_pin = 38, .pin_name = "DB2"        , .port = GPIO_PORT(D), .pin = GPIO_PIN( 2),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            { .btb_pin = 40, .pin_name = "DB3"        , .port = GPIO_PORT(D), .pin = GPIO_PIN( 3),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            { .btb_pin = 42, .pin_name = "DB4/nSER1W" , .port = GPIO_PORT(D), .pin = GPIO_PIN( 4),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            { .btb_pin = 44, .pin_name = "DB5/CRCEN"  , .port = GPIO_PORT(D), .pin = GPIO_PIN( 5),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            { .btb_pin = 46, .pin_name = "DB6"        , .port = GPIO_PORT(D), .pin = GPIO_PIN( 6),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            { .btb_pin = 48, .pin_name = "DB7"        , .port = GPIO_PORT(D), .pin = GPIO_PIN( 7),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            { .btb_pin = 33, .pin_name = "DB8"        , .port = GPIO_PORT(D), .pin = GPIO_PIN( 8),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            { .btb_pin = 35, .pin_name = "DB9"        , .port = GPIO_PORT(D), .pin = GPIO_PIN( 9),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            { .btb_pin = 37, .pin_name = "DB10/SDI"   , .port = GPIO_PORT(D), .pin = GPIO_PIN(10),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            { .btb_pin = 39, .pin_name = "DB11/SDOB"  , .port = GPIO_PORT(D), .pin = GPIO_PIN(11),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            { .btb_pin = 41, .pin_name = "DB12/SDOA"  , .port = GPIO_PORT(D), .pin = GPIO_PIN(12),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            { .btb_pin = 43, .pin_name = "DB13/OS0"   , .port = GPIO_PORT(D), .pin = GPIO_PIN(13),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            { .btb_pin = 45, .pin_name = "DB14/OS1"   , .port = GPIO_PORT(D), .pin = GPIO_PIN(14),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            { .btb_pin = 47, .pin_name = "DB15/OS2"   , .port = GPIO_PORT(D), .pin = GPIO_PIN(15),  .func = BSP_IO_FUNC_INOUT, .state = IO_STATE_RESERVED },
            {.btb_pin = IO_ARR_END_ID}
        },

        .switch_value = BSPMUX_DEFAULT,

        .perh = {
            NULL
    }
    }
};

void dut_ad7616_init()
{
    dut_init(&ad7616_profiles[0]);
}
