/****************************
 AD7616 DEF
 CRTHu
 2025.03.27
 ****************************/

#ifndef _AD7616_DEF_H_
#define _AD7616_DEF_H_

#include <stdint.h>
#include "bsp_inc.h"

#define AD7616_CONV_BUFFER_LEN          65536

#define AD7616_PAR_WR                   1
#define AD7616_PAR_RD                   0

typedef enum ad7616_mode {
    AD7616_SER_SW,
    AD7616_PAR_SW,
    AD7616_SER_HW,
    AD7616_PAR_HW
} ad7616_mode;

typedef enum ad7616_convst_mode {
    AD7616_CONVST_IO,
    AD7616_CONVST_PWM,
} ad7616_convst_mode;


typedef gpio_port_t ad7616_gpio_port_t;
typedef gpio_pin_t ad7616_gpio_pin_t;

#define COPY_FROM_IO(dst, src) do {     \
    if(dst != NULL && src != NULL)      \
    {                                   \
        (dst)->port = (src)->port;      \
        (dst)->pin = (src)->pin;        \
    }                                   \
} while(0)

typedef struct ad7616_io_t
{
    volatile ad7616_gpio_port_t* port;
    volatile ad7616_gpio_pin_t pin;
} ad7616_io_t;

typedef struct ad7616_t
{
    /* config */
    ad7616_mode mode;
    uint8_t serial_wire;

    uint32_t convst_freq;
    uint8_t adc_ch_a;
    uint8_t adc_ch_b;
    uint8_t adc_ch_a_en;
    uint8_t adc_ch_b_en;

    /* io */
    /* IO AVAILABLE AT MODE            */
    /* S:SERIAL, P:PARALLEL    S P S P */
    /* S:Software, H:Hardware  S S H H */
    ad7616_io_t convst;     /* + + + + */
    ad7616_io_t busy;       /* + + + + */
    ad7616_io_t csn;        /*         */
    ad7616_io_t rdn;        /*         */
    ad7616_io_t wrn;        /*         */

    ad7616_io_t chsel0;     /*         */
    ad7616_io_t chsel1;     /*         */
    ad7616_io_t chsel2;     /*         */
    ad7616_io_t seqen;      /*         */
    ad7616_io_t rngsel1;    /*         */
    ad7616_io_t rngsel0;    /*         */
    ad7616_io_t sersel;     /*         */
    ad7616_io_t refsel;     /* + + + + */
    ad7616_io_t resetn;     /* + + + + */

    ad7616_io_t burst;      /*         */
    ad7616_io_t ser1wn;     /*         */
    ad7616_io_t crcen;      /*         */
    ad7616_io_t os0;        /*         */
    ad7616_io_t os1;        /*         */
    ad7616_io_t os2;        /*         */

    /* perh */
    void* clk1_pwm;         /*         */
    void* clk2_etr;         /*         */
    spi_t* spi_a;           /*         */
    spi_t* spi_b;           /*         */
    gpio_port_t* par_db;    /*         */
} ad7616_t;

/* T (ns) */
#define T_MIN(t1, t2)                   (((t1) < (t2)) ? t1 : t2 )
#define T_MAX(t1, t2)                   (((t1) > (t2)) ? t1 : t2 )
#define T_ADD(t1, t2)                   ((t1) + (t2))
#define T_SUB(t1, t2)                   (((int)(t1) - (int)(t2)) >= 0 ? ((int)(t1) - (int)(t2)) : 0 )

#define AD7616_DELAY(t)                 delay_ns(T_ADD(T_MAX(t, AD7616_DEBUG_DELAY), AD7616_RESERVED_DELAY))

#define AD7616_DEBUG_DELAY              0
#define AD7616_RESERVED_DELAY           0

#define AD7616_T_CONV_HIGH              50

#define AD7616_PAR_T_RDN_SETUP          10
#define AD7616_PAR_T_RDN_HOLD           10
#define AD7616_PAR_T_RDN_HIGH           10
#define AD7616_PAR_T_RDN_LOW            30
#define AD7616_PAR_T_DOUT_SETUP         30
#define AD7616_PAR_T_DOUT_3STATE        11
#define AD7616_PAR_T_WRN_SETUP          10
#define AD7616_PAR_T_WRN_HOLD           10
#define AD7616_PAR_T_WRN_HIGH           20
#define AD7616_PAR_T_WRN_LOW            30
#define AD7616_PAR_T_DIN_SETUP          30

#define AD7616_PAR_T_CSN_HIGH           10

#endif // _AD7616_DEF_H_
