#include "bsp_inc.h"


io_switch_t switch_config[] =
{
    {.id = 1,  .sw_sel = {.pin_name = "MUX_SEL01", .port = GPIO_PORT(B), .pin = GPIO_PIN(15), .func = BSP_IO_SWITCH_SEL}},
    {.id = 2,  .sw_sel = {.pin_name = "MUX_SEL02", .port = GPIO_PORT(A), .pin = GPIO_PIN(8),  .func = BSP_IO_SWITCH_SEL}},
    {.id = 3,  .sw_sel = {.pin_name = "MUX_SEL03", .port = GPIO_PORT(C), .pin = GPIO_PIN(9),  .func = BSP_IO_SWITCH_SEL}},
    {.id = 4,  .sw_sel = {.pin_name = "MUX_SEL04", .port = GPIO_PORT(C), .pin = GPIO_PIN(8),  .func = BSP_IO_SWITCH_SEL}},
    {.id = 5,  .sw_sel = {.pin_name = "MUX_SEL05", .port = GPIO_PORT(B), .pin = GPIO_PIN(13), .func = BSP_IO_SWITCH_SEL}},
    {.id = 6,  .sw_sel = {.pin_name = "MUX_SEL06", .port = GPIO_PORT(B), .pin = GPIO_PIN(14), .func = BSP_IO_SWITCH_SEL}},
    {.id = 7,  .sw_sel = {.pin_name = "MUX_SEL07", .port = GPIO_PORT(C), .pin = GPIO_PIN(5),  .func = BSP_IO_SWITCH_SEL}},
    {.id = 8,  .sw_sel = {.pin_name = "MUX_SEL08", .port = GPIO_PORT(A), .pin = GPIO_PIN(5),  .func = BSP_IO_SWITCH_SEL}},
    {.id = 9,  .sw_sel = {.pin_name = "MUX_SEL09", .port = GPIO_PORT(C), .pin = GPIO_PIN(13), .func = BSP_IO_SWITCH_SEL}},
    {.id = 10, .sw_sel = {.pin_name = "MUX_SEL10", .port = GPIO_PORT(E), .pin = GPIO_PIN(0),  .func = BSP_IO_SWITCH_SEL}},
    {.id = 11, .sw_sel = {.pin_name = "MUX_SEL11", .port = GPIO_PORT(C), .pin = GPIO_PIN(15), .func = BSP_IO_SWITCH_SEL}},
    {.id = 12, .sw_sel = {.pin_name = "MUX_SEL12", .port = GPIO_PORT(C), .pin = GPIO_PIN(14), .func = BSP_IO_SWITCH_SEL}},
    {.id = IO_SWITCH_ARR_END_ID}
};


gpio_config_status_t switch_init(io_switch_t* switch_configs)
{
    uint16_t i = 0;
    while (switch_configs[i].id != IO_SWITCH_ARR_END_ID)
    {
        gpio_init(&(switch_configs[i].sw_sel));
        i++;
    }
    return GPIO_CONFIG_STATUS_NO_ERR;
}

gpio_config_status_t switch_set(io_switch_t* switch_configs, uint16_t value)
{
    uint16_t i = 0;
    while (switch_configs[i].id != IO_SWITCH_ARR_END_ID)
    {
        GPIO_WRITE(&(switch_configs[i].sw_sel), (value >> i) & 0x01);
        i++;
    }
    return GPIO_CONFIG_STATUS_NO_ERR;
}

uint32_t switch_get(io_switch_t* switch_configs)
{
    uint32_t val = 0;
    uint16_t i = 0;
    while (switch_configs[i].id != IO_SWITCH_ARR_END_ID)
    {
        val = (val << 1) | (GPIO_READ(&(switch_configs[i].sw_sel)) & 0x01);
        i++;
    }
    return val;
}
