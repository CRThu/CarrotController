#include "bsp_inc.h"


io_switch_t switch_config[] =
{
    {.id = 1,  .sw_sel = {.pin_name = "MUX_SEL01", .port = GPIO_PORT(B), .pin = GPIO_PIN(15), .type = IO_TYPE_OUT}},
    {.id = 2,  .sw_sel = {.pin_name = "MUX_SEL02", .port = GPIO_PORT(A), .pin = GPIO_PIN(8),  .type = IO_TYPE_OUT}},
    {.id = 3,  .sw_sel = {.pin_name = "MUX_SEL03", .port = GPIO_PORT(C), .pin = GPIO_PIN(9),  .type = IO_TYPE_OUT}},
    {.id = 4,  .sw_sel = {.pin_name = "MUX_SEL04", .port = GPIO_PORT(C), .pin = GPIO_PIN(8),  .type = IO_TYPE_OUT}},
    {.id = 5,  .sw_sel = {.pin_name = "MUX_SEL05", .port = GPIO_PORT(B), .pin = GPIO_PIN(13), .type = IO_TYPE_OUT}},
    {.id = 6,  .sw_sel = {.pin_name = "MUX_SEL06", .port = GPIO_PORT(B), .pin = GPIO_PIN(14), .type = IO_TYPE_OUT}},
    {.id = 7,  .sw_sel = {.pin_name = "MUX_SEL07", .port = GPIO_PORT(C), .pin = GPIO_PIN(5),  .type = IO_TYPE_OUT}},
    {.id = 8,  .sw_sel = {.pin_name = "MUX_SEL08", .port = GPIO_PORT(A), .pin = GPIO_PIN(5),  .type = IO_TYPE_OUT}},
    {.id = 9,  .sw_sel = {.pin_name = "MUX_SEL09", .port = GPIO_PORT(C), .pin = GPIO_PIN(13), .type = IO_TYPE_OUT}},
    {.id = 10, .sw_sel = {.pin_name = "MUX_SEL10", .port = GPIO_PORT(E), .pin = GPIO_PIN(0),  .type = IO_TYPE_OUT}},
    {.id = 11, .sw_sel = {.pin_name = "MUX_SEL11", .port = GPIO_PORT(C), .pin = GPIO_PIN(15), .type = IO_TYPE_OUT}},
    {.id = 12, .sw_sel = {.pin_name = "MUX_SEL12", .port = GPIO_PORT(C), .pin = GPIO_PIN(14), .type = IO_TYPE_OUT}},
    {.id = IO_SWITCH_ARR_END_ID}
};

void bsp_switch_init(uint16_t swval)
{
    switch_init(switch_config);
    switch_set(switch_config, swval);
}

int8_t switch_init(io_switch_t* switch_configs)
{
    uint16_t i = 0;
    while (switch_configs[i].id != IO_SWITCH_ARR_END_ID)
    {
        bsp_io_preset(&(switch_configs[i].sw_sel));
        i++;
    }
    return 0;
}

int8_t switch_set(io_switch_t* switch_configs, uint16_t value)
{
    uint16_t i = 0;
    while (switch_configs[i].id != IO_SWITCH_ARR_END_ID)
    {
        BSP_IO_WRITE(&(switch_configs[i].sw_sel), (value >> i) & 0x01);
        i++;
    }
    return 0;
}

uint32_t switch_get(io_switch_t* switch_configs)
{
    uint32_t val = 0;
    uint16_t i = 0;
    while (switch_configs[i].id != IO_SWITCH_ARR_END_ID)
    {
        val = (val << 1) | (BSP_IO_READ(&(switch_configs[i].sw_sel)) & 0x01);
        i++;
    }
    return val;
}
