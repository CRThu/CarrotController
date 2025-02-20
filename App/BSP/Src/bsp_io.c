#include "bsp_io.h"
#include "bsp_inc.h"


static const io_switch_t bsp_switch_config[] = 
{
    
}

static const dut_interface_t dac11001_profile =
{
    .id = 0,
    .name = "DAC11001",

    .preset_id = 0,
    .preset_name = "2 HARDWARE SPI COMM",

    .pin_configs = {
        {.btb_pin = 11, .pin_name = "#LDAC1",    .port = GPIOA, .pin = GPIO_PIN_1,  .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = 12, .pin_name = "#LDAC2",    .port = GPIOC, .pin = GPIO_PIN_2,  .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = 17, .pin_name = "#SYNC1",    .port = GPIOA, .pin = GPIO_PIN_4,  .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = 19, .pin_name = "#SYNC2",    .port = GPIOA, .pin = GPIO_PIN_15, .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = 23, .pin_name = "SPIA_SCK",  .port = GPIOB, .pin = GPIO_PIN_3,  .func = BSP_IO_FUNC_SPI_SCK,  .state = IO_STATE_RESERVED },
        {.btb_pin = 25, .pin_name = "SPIA_MOSI", .port = GPIOB, .pin = GPIO_PIN_5,  .func = BSP_IO_FUNC_SPI_MOSI, .state = IO_STATE_RESERVED },
        {.btb_pin = 27, .pin_name = "SPIA_MISO", .port = GPIOB, .pin = GPIO_PIN_4,  .func = BSP_IO_FUNC_SPI_MISO, .state = IO_STATE_RESERVED },
        {.btb_pin = 24, .pin_name = "SPIB_SCK",  .port = GPIOC, .pin = GPIO_PIN_10, .func = BSP_IO_FUNC_SPI_SCK,  .state = IO_STATE_RESERVED },
        {.btb_pin = 26, .pin_name = "SPIB_MOSI", .port = GPIOC, .pin = GPIO_PIN_12, .func = BSP_IO_FUNC_SPI_MOSI, .state = IO_STATE_RESERVED },
        {.btb_pin = 28, .pin_name = "SPIB_MISO", .port = GPIOC, .pin = GPIO_PIN_11, .func = BSP_IO_FUNC_SPI_MISO, .state = IO_STATE_RESERVED },
        {.btb_pin = 51, .pin_name = "#CLR1",     .port = GPIOE, .pin = GPIO_PIN_14, .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = 52, .pin_name = "#CLR2",     .port = GPIOE, .pin = GPIO_PIN_15, .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
    },

    .switch_value = 0,

    .perh = {0
    }
};

gpio_config_status_t gpio_check(btb_io_t* gpio)
{
    // todo
    //gpio_capability_matrix
    return GPIO_CONFIG_STATUS_NO_ERR;
}

gpio_config_status_t gpio_config(btb_io_t* gpio, gpio_port_t* port, gpio_pin_t* pin, bsp_io_func func)
{
    gpio->port = port;
    gpio->pin = pin;
    gpio->func = func;
    return gpio_check(gpio);
}

gpio_config_status_t gpio_init(gpio_t* gpio)
{

}