#include "bsp_io.h"
#include "bsp_inc.h"


static io_switch_t switch_config[] =
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
};

static dut_interface_t dac11001_profile =
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
    },

    .switch_value = SWITCH_EN(1)
                  | SWITCH_EN(4)
                  | SWITCH_EN(6) ,

    .perh = { 0
    }
};

gpio_config_status_t gpio_init(io_t* gpio)
{
    if (!gpio)
    {
        return -1;
    }

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    /* GPIO Ports Clock Enable */
    if (gpio->port == GPIO_PORT(A))  GPIO_CLOCK(A);
    if (gpio->port == GPIO_PORT(B))  GPIO_CLOCK(B);
    if (gpio->port == GPIO_PORT(C))  GPIO_CLOCK(C);
    if (gpio->port == GPIO_PORT(D))  GPIO_CLOCK(D);
    if (gpio->port == GPIO_PORT(E))  GPIO_CLOCK(E);
    if (gpio->port == GPIO_PORT(F))  GPIO_CLOCK(F);
    if (gpio->port == GPIO_PORT(G))  GPIO_CLOCK(G);
    if (gpio->port == GPIO_PORT(H))  GPIO_CLOCK(H);
    if (gpio->port == GPIO_PORT(I))  GPIO_CLOCK(I);


    switch (gpio->func)
    {
    case BSP_IO_FUNC_NONE:
        return -2;
        break;
    case BSP_IO_FUNC_OUT:
    case BSP_IO_SWITCH_SEL:
        /*Configure GPIO pin Output Level */
        HAL_GPIO_WritePin(gpio->port, gpio->pin, gpio->state);

        /*Configure GPIO pin */
        GPIO_InitStruct.Pin = gpio->pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(gpio->port, &GPIO_InitStruct);

        return GPIO_CONFIG_STATUS_NO_ERR;
        break;
    case BSP_IO_FUNC_IN:
        /*Configure GPIO pin */
        GPIO_InitStruct.Pin = gpio->pin;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(gpio->port, &GPIO_InitStruct);
        return GPIO_CONFIG_STATUS_NO_ERR;
        break;
    default:
        return -3;
        break;
    }
}

gpio_config_status_t io_write(io_t* io, uint16_t value)
{
    GPIO_WRITE(io->port, io->pin, value);
}

gpio_config_status_t switch_init(io_switch_t** switch_configs, uint16_t size)
{
    for (uint16_t i = 0; i < size; i++)
        gpio_init(&(switch_configs[i]->sw_sel));
}

gpio_config_status_t switch_set(io_switch_t** switch_configs, uint16_t size, uint16_t value)
{
    for (uint16_t i = 0; i < size; i++)
        gpio_write(&(switch_configs[i]->sw_sel), (value >> i) & 0x01);
}

gpio_config_status_t dut_init(dut_interface_t* dut)
{
    for (uint16_t i = 0; i < 40; i++)
    {
        if ((dut->pin_configs[i])->btb_pin == 0)
            break;
        gpio_init(&(dut->pin_configs[i]));
    }
    switch_init(switch_config, 12);
    switch_set(switch_config, 12, dut->switch_value);
}

