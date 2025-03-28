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

#define COPY_FROM_IO(dst, src) do { \
    (dst)->port = (src)->port;      \
    (dst)->pin = (src)->pin;        \
} while(0)

typedef struct ad7616_io_t
{
    ad7616_gpio_port_t* port;
    ad7616_gpio_pin_t pin;
} ad7616_io_t;

typedef struct ad7616_t
{
    ad7616_io_t resetn;
    ad7616_io_t csn;
    ad7616_io_t rdn;
    ad7616_io_t wrn;
    ad7616_io_t db[16];
} ad7616_t;

void ad7616_init(ad7616_t* adc, dut_interface_t* intf);
void ad7616_reset(ad7616_t* adc);

#endif // _AD7616_IOCFG_H_
