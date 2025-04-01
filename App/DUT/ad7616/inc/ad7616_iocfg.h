/****************************
 AD7616 IO CONFIG
 CRTHu
 2025.03.27
 ****************************/

#ifndef _AD7616_IOCFG_H_
#define _AD7616_IOCFG_H_

#include <stdint.h>
#include "dut_ad7616.h"
#include "ad7616_def.h"
#include "bsp_inc.h"


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

    /* io */
    ad7616_io_t convst;
    ad7616_io_t busy;
    ad7616_io_t resetn;
    ad7616_io_t csn;
    ad7616_io_t rdn;
    ad7616_io_t wrn;

    ad7616_io_t chsel0;
    ad7616_io_t chsel1;
    ad7616_io_t chsel2;
    ad7616_io_t seqen;
    ad7616_io_t rngsel1;
    ad7616_io_t rngsel0;
    ad7616_io_t sersel;
    ad7616_io_t refsel;

    ad7616_io_t burst;
    ad7616_io_t ser1wn;
    ad7616_io_t crcen;
    ad7616_io_t os0;
    ad7616_io_t os1;
    ad7616_io_t os2;

    /* perh */
    void* clk1_pwm;
    void* clk2_etr;
    void* spi_a;
    void* spi_b;
    gpio_port_t* par_db;
} ad7616_t;

void ad7616_set_mode(ad7616_t* adc, ad7616_mode mode);
void ad7616_set_io(ad7616_t* adc, dut_interface_t* intf);
void ad7616_full_reset(ad7616_t* adc);
uint32_t ad7616_reg_read(ad7616_t* adc, uint32_t addr);

#endif // _AD7616_IOCFG_H_
