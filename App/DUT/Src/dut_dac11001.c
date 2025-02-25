#include "dut_inc.h"

#define SHARED_LDAC
#define PWM_LDAC

dut_interface_t dac11001_profile =
{
    .id = 0,
    .name = "DAC11001",

    .preset_id = 0,

    #ifdef SHARED_LDAC
    .preset_name = "TWO SPI, SHARED LDAC",
    #else
    .preset_name = "TWO SPI",
    #endif

    .pin_configs = (io_t[]) {
    #ifndef PWM_LDAC
    #ifdef SHARED_LDAC
        {.btb_pin = 11, .pin_name = "#LDAC",       .port = GPIO_PORT(A), .pin = GPIO_PIN(1),  .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
    #else
        {.btb_pin = 11, .pin_name = "#LDAC[0]",    .port = GPIO_PORT(A), .pin = GPIO_PIN(1),  .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = 12, .pin_name = "#LDAC[1]",    .port = GPIO_PORT(C), .pin = GPIO_PIN(2),  .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
    #endif
    #endif
        //{.btb_pin = 17, .pin_name = "#SYNC[0]",    .port = GPIO_PORT(A), .pin = GPIO_PIN(4),  .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        //{.btb_pin = 19, .pin_name = "#SYNC[1]",    .port = GPIO_PORT(A), .pin = GPIO_PIN(15), .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = 23, .pin_name = "SPI_SCK[0]",  .port = GPIO_PORT(B), .pin = GPIO_PIN(3),  .func = BSP_IO_FUNC_SPI_SCK,  .state = IO_STATE_RESERVED },
        {.btb_pin = 25, .pin_name = "SPI_MOSI[0]", .port = GPIO_PORT(B), .pin = GPIO_PIN(5),  .func = BSP_IO_FUNC_SPI_MOSI, .state = IO_STATE_RESERVED },
        {.btb_pin = 27, .pin_name = "SPI_MISO[0]", .port = GPIO_PORT(B), .pin = GPIO_PIN(4),  .func = BSP_IO_FUNC_SPI_MISO, .state = IO_STATE_RESERVED },
        {.btb_pin = 24, .pin_name = "SPI_SCK[1]",  .port = GPIO_PORT(C), .pin = GPIO_PIN(10), .func = BSP_IO_FUNC_SPI_SCK,  .state = IO_STATE_RESERVED },
        {.btb_pin = 26, .pin_name = "SPI_MOSI[1]", .port = GPIO_PORT(C), .pin = GPIO_PIN(12), .func = BSP_IO_FUNC_SPI_MOSI, .state = IO_STATE_RESERVED },
        {.btb_pin = 28, .pin_name = "SPI_MISO[1]", .port = GPIO_PORT(C), .pin = GPIO_PIN(11), .func = BSP_IO_FUNC_SPI_MISO, .state = IO_STATE_RESERVED },
        {.btb_pin = 51, .pin_name = "#CLR[0]",     .port = GPIO_PORT(E), .pin = GPIO_PIN(14), .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = 52, .pin_name = "#CLR[1]",     .port = GPIO_PORT(E), .pin = GPIO_PIN(15), .func = BSP_IO_FUNC_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = IO_ARR_END_ID}
    },

    .switch_value = SWITCH_EN(1)
                  | SWITCH_EN(4)
                  | SWITCH_EN(6) ,

    .perh = {
        &spi_instances[0],  // config from cubemx
        &spi_instances[1],  // config from cubemx
        NULL
    }
};

uint8_t rxbuf[4];
uint8_t txbuf[4];


void dut_dac11001_init()
{
    dut_init(&dac11001_profile);
    
    #ifdef PWM_LDAC
    // todo
    #endif
}

void dut_dac11001_set_spi(uint8_t id, spi_t* hspi)
{
    if (id < DUT_MAX_PERH_NUM)
        dac11001_profile.perh[id] = hspi;
}

void dut_dac11001_reg_write(uint8_t id, uint8_t addr, uint32_t data)
{
    data = data << 4;

    txbuf[0] = (0x00 << 7) | (addr & 0x7F);
    txbuf[1] = (data >> 16) & 0xFF;
    txbuf[2] = (data >> 8) & 0xFF;
    txbuf[3] = (data >> 0) & 0xFF;

    //io_t* io_nsync = dut_get_io_id(&dac11001_profile, id, "#SYNC");

    //gpio_write(io_nsync, IO_STATE_LOW);
    //for (int i = 0; i < 5; i++);
    spi_write((spi_t*)dac11001_profile.perh[id], txbuf, 4);
    //for (int i = 0; i < 5; i++);
    //gpio_write(io_nsync, IO_STATE_HIGH);
}

void dut_dac11001_set_code(uint8_t id, uint32_t code)
{
    #ifndef PWM_LDAC
    #ifdef SHARED_LDAC
    io_t* io_ldac = dut_get_io(&dac11001_profile, "#LDAC");
    #else
    io_t* io_ldac = dut_get_io_id(&dac11001_profile, id, "#LDAC");
    #endif
    #endif

    dut_dac11001_reg_write(id, 0x01, code);
    #ifndef PWM_LDAC
    gpio_write(io_ldac, IO_STATE_LOW);
    for (int i = 0; i < 5; i++);
    gpio_write(io_ldac, IO_STATE_HIGH);
    #endif
}