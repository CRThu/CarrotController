#include "dut_dac11001.h"

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
        {.btb_pin = 11, .pin_name = "#LDAC",       .port = GPIO_PORT(A), .pin = GPIO_PIN(1),  .type = IO_TYPE_OUT,      .state = IO_STATE_HIGH     },
    #else
        {.btb_pin = 11, .pin_name = "#LDAC[0]",    .port = GPIO_PORT(A), .pin = GPIO_PIN(1),  .type = IO_TYPE_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = 12, .pin_name = "#LDAC[1]",    .port = GPIO_PORT(C), .pin = GPIO_PIN(2),  .type = IO_TYPE_OUT,      .state = IO_STATE_HIGH     },
    #endif
    #endif
        //{.btb_pin = 17, .pin_name = "#SYNC[0]",    .port = GPIO_PORT(A), .pin = GPIO_PIN(4),  .type = IO_TYPE_OUT,      .state = IO_STATE_HIGH     },
        //{.btb_pin = 19, .pin_name = "#SYNC[1]",    .port = GPIO_PORT(A), .pin = GPIO_PIN(15), .type = IO_TYPE_OUT,      .state = IO_STATE_HIGH     },
        {.btb_pin = 23, .pin_name = "SPI_SCK[0]",  .port = GPIO_PORT(B), .pin = GPIO_PIN(3),  .type = IO_TYPE_PERH, .state = IO_STATE_LOW },
        {.btb_pin = 25, .pin_name = "SPI_MOSI[0]", .port = GPIO_PORT(B), .pin = GPIO_PIN(5),  .type = IO_TYPE_PERH, .state = IO_STATE_LOW },
        {.btb_pin = 27, .pin_name = "SPI_MISO[0]", .port = GPIO_PORT(B), .pin = GPIO_PIN(4),  .type = IO_TYPE_PERH, .state = IO_STATE_LOW },
        {.btb_pin = 24, .pin_name = "SPI_SCK[1]",  .port = GPIO_PORT(C), .pin = GPIO_PIN(10), .type = IO_TYPE_PERH, .state = IO_STATE_LOW },
        {.btb_pin = 26, .pin_name = "SPI_MOSI[1]", .port = GPIO_PORT(C), .pin = GPIO_PIN(12), .type = IO_TYPE_PERH, .state = IO_STATE_LOW },
        {.btb_pin = 28, .pin_name = "SPI_MISO[1]", .port = GPIO_PORT(C), .pin = GPIO_PIN(11), .type = IO_TYPE_PERH, .state = IO_STATE_LOW },
        {.btb_pin = 51, .pin_name = "#CLR[0]",     .port = GPIO_PORT(E), .pin = GPIO_PIN(14), .type = IO_TYPE_OUT,  .state = IO_STATE_HIGH     },
        {.btb_pin = 52, .pin_name = "#CLR[1]",     .port = GPIO_PORT(E), .pin = GPIO_PIN(15), .type = IO_TYPE_OUT,  .state = IO_STATE_HIGH     },
        {.btb_pin = IO_ARR_END_ID}
    },

    .switch_value = BSPMUX_BTB_CLK1_TO_MCU_IO
                  | BSPMUX_BTB_SPIA_SCK_TO_MCU_SPIA_SCK
                  | BSPMUX_BTB_SPIB_SCK_TO_MCU_SPIB_SCK ,

    .perh = {
        NULL, //&hspi1,
        NULL,//&hspi3,
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
    bsp_spi_write(dac11001_profile.perh[id], txbuf, 4);
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


/*

    dut_dac11001_init();

    HAL_TIM_RegisterCallback(&htim5, HAL_TIM_PERIOD_ELAPSED_CB_ID, set_flag);
    HAL_TIM_Base_Start_IT(&htim5);
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);

    // cordic test
    HAL_CORDIC_Configure(&hcordic, &(CORDIC_ConfigTypeDef) {
        .Function = CORDIC_FUNCTION_COSINE,
            .InSize = CORDIC_INSIZE_32BITS,
            .OutSize = CORDIC_OUTSIZE_32BITS,
            .NbWrite = CORDIC_NBWRITE_2,
            .NbRead = CORDIC_NBREAD_2,
            .Precision = CORDIC_PRECISION_8CYCLES,
    });

    int32_t inbuf[16];
    int32_t outbuf[16];
    double arg1, arg2, res1, res2;
    double f = 921;
    double fs = 100000;
    int32_t code;
    //uint8_t buf[256];

    //arg1 = 0.1;
    //arg2 = 1.0;

    //inbuf[0] = (double)arg1 * (double)2147483648.0;
    //inbuf[1] = (double)arg2 * (double)2147483648.0;

    //HAL_CORDIC_CalculateZO(&hcordic, inbuf, outbuf, 1, 0xFFFF);

    //res1 = (double)outbuf[0] / (double)2147483648.0;
    //res2 = (double)outbuf[1] / (double)2147483648.0;

    //// 1.00000000*cos(0.10000000/pi)=0.95105672, sin=0.30901575
    //sprintf(buf, "%.8lf*cos(%.8lf/pi)=%.8lf, sin=%.8lf\r\n", arg2, arg1, res1, res2);

    //uart_comm_write(comm_pc, buf, strlen(buf));

    // dac11001
    inbuf[0] = 0;
    inbuf[1] = 0.9 * (double)2147483648.0;

*/



/*
// timer driven ldac
if (flag)
{
    cnt += 1;

   if (cnt > (double)fs / (double)2.0 / (double)f)
       cnt -= (double)fs / (double)f;

   inbuf[0] = (double)2.0 / (double)fs * (double)cnt * (double)f * (double)2147483648.0;

   HAL_CORDIC_CalculateZO(&hcordic, inbuf, outbuf, 1, 0xFFFF);

             //outbuf[0] = arm_cos_q31(inbuf[0]);
             //outbuf[0] *=0.9;

   code = (double)outbuf[0] / (double)2147483648.0 * (double)524288.0 - (double)524288.0;


    //code = 0.9*cos(2.0*3.14159265*cnt/(double)fs*(double)f) *(double)524288.0 - (double)524288.0 ;

                //code = 0.9*arm_cos_f32(2.0*3.14159265*cnt/(double)fs*(double)f)*(double)524288.0 - (double)524288.0;

            //arm_cos_q31

    dut_dac11001_set_code(0, code);
    //code = (double)outbuf[1] / (double)2147483648.0 * (double)524288.0-(double)524288.0;
    dut_dac11001_set_code(1, code);

    flag = 0;
}
*/