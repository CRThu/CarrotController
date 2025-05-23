#include "bsp_inc.h"


io_t* ft_io = (io_t[]){
    {.pin_name = "FT_D[0]",  .port = GPIO_PORT(F), .pin = GPIO_PIN(0),  .type = IO_TYPE_IN, .state = IO_STATE_LOW },
    {.pin_name = "FT_D[1]",  .port = GPIO_PORT(F), .pin = GPIO_PIN(1),  .type = IO_TYPE_IN, .state = IO_STATE_LOW },
    {.pin_name = "FT_D[2]",  .port = GPIO_PORT(F), .pin = GPIO_PIN(2),  .type = IO_TYPE_IN, .state = IO_STATE_LOW },
    {.pin_name = "FT_D[3]",  .port = GPIO_PORT(F), .pin = GPIO_PIN(3),  .type = IO_TYPE_IN, .state = IO_STATE_LOW },
    {.pin_name = "FT_D[4]",  .port = GPIO_PORT(F), .pin = GPIO_PIN(4),  .type = IO_TYPE_IN, .state = IO_STATE_LOW },
    {.pin_name = "FT_D[5]",  .port = GPIO_PORT(F), .pin = GPIO_PIN(5),  .type = IO_TYPE_IN, .state = IO_STATE_LOW },
    {.pin_name = "FT_D[6]",  .port = GPIO_PORT(F), .pin = GPIO_PIN(6),  .type = IO_TYPE_IN, .state = IO_STATE_LOW },
    {.pin_name = "FT_D[7]",  .port = GPIO_PORT(F), .pin = GPIO_PIN(7),  .type = IO_TYPE_IN, .state = IO_STATE_LOW },
    {.pin_name = "FT_RXFN",  .port = GPIO_PORT(F), .pin = GPIO_PIN(11), .type = IO_TYPE_IN, .state = IO_STATE_LOW },
    {.pin_name = "FT_TXEN",  .port = GPIO_PORT(F), .pin = GPIO_PIN(12), .type = IO_TYPE_IN, .state = IO_STATE_LOW },
    {.pin_name = "FT_RDN",   .port = GPIO_PORT(F), .pin = GPIO_PIN(13), .type = IO_TYPE_OUT, .speed =IO_SPEED_FAST, .state = IO_STATE_HIGH },
    {.pin_name = "FT_WRN",   .port = GPIO_PORT(F), .pin = GPIO_PIN(14), .type = IO_TYPE_OUT, .speed =IO_SPEED_FAST, .state = IO_STATE_HIGH },
    {.pin_name = "FT_WIWUA", .port = GPIO_PORT(F), .pin = GPIO_PIN(15), .type = IO_TYPE_OUT, .speed =IO_SPEED_FAST, .state = IO_STATE_HIGH },
    {.btb_pin = IO_ARR_END_ID}
};

void bsp_ft_init()
{
    uint16_t i = 0;
    while (ft_io[i].btb_pin != IO_ARR_END_ID)
    {
        bsp_io_preset(&(ft_io[i]));
        i++;
    }

}