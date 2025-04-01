/****************************
 AD7616 IO CONFIG
 CRTHu
 2025.04.01
 ****************************/

#ifndef _AD7616_IOCFG_H_
#define _AD7616_IOCFG_H_

#include <stdint.h>
#include "dut_ad7616.h"
#include "ad7616_def.h"
#include "bsp_inc.h"

void ad7616_set_mode(ad7616_t* adc, ad7616_mode mode);
void ad7616_set_io(ad7616_t* adc, dut_interface_t* intf);

void ad7616_full_reset(ad7616_t* adc);

uint16_t ad7616_reg_read(ad7616_t* adc, uint32_t addr);
void ad7616_reg_write(ad7616_t* adc, uint32_t addr, uint32_t data);

uint16_t ad7616_reg_bits_read(ad7616_t* adc, uint32_t addr, uint8_t start, uint8_t end);
void ad7616_reg_bits_write(ad7616_t* adc, uint32_t addr, uint8_t start, uint8_t end, uint32_t data);

uint16_t ad7616_data_read(ad7616_t* adc);

int8_t ad7616_comm_test(ad7616_t* adc);

#endif // _AD7616_IOCFG_H_
