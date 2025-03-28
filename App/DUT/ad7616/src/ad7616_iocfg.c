/****************************
 AD7616 IO CONFIG
 CRTHu
 2025.03.27
 ****************************/

#include "ad7616_iocfg.h"

void ad7616_init(ad7616_t* adc, dut_interface_t* intf)
{
    COPY_FROM_IO(&(adc->resetn), dut_get_io(intf, "nRESET"));
    COPY_FROM_IO(&(adc->csn), dut_get_io(intf, "nCS"));
    COPY_FROM_IO(&(adc->rdn), dut_get_io(intf, "nRD"));
    COPY_FROM_IO(&(adc->wrn), dut_get_io(intf, "nWR"));
    COPY_FROM_IO(&(adc->db[0]), dut_get_io(intf, "DB0"));
    COPY_FROM_IO(&(adc->db[1]), dut_get_io(intf, "DB1"));
    COPY_FROM_IO(&(adc->db[2]), dut_get_io(intf, "DB2"));
    COPY_FROM_IO(&(adc->db[3]), dut_get_io(intf, "DB3"));
    COPY_FROM_IO(&(adc->db[4]), dut_get_io(intf, "DB4"));
    COPY_FROM_IO(&(adc->db[5]), dut_get_io(intf, "DB5"));
    COPY_FROM_IO(&(adc->db[6]), dut_get_io(intf, "DB6"));
    COPY_FROM_IO(&(adc->db[7]), dut_get_io(intf, "DB7"));
    COPY_FROM_IO(&(adc->db[8]), dut_get_io(intf, "DB8"));
    COPY_FROM_IO(&(adc->db[9]), dut_get_io(intf, "DB9"));
    COPY_FROM_IO(&(adc->db[10]), dut_get_io(intf, "DB10"));
    COPY_FROM_IO(&(adc->db[11]), dut_get_io(intf, "DB11"));
    COPY_FROM_IO(&(adc->db[12]), dut_get_io(intf, "DB12"));
    COPY_FROM_IO(&(adc->db[13]), dut_get_io(intf, "DB13"));
    COPY_FROM_IO(&(adc->db[14]), dut_get_io(intf, "DB14"));
    COPY_FROM_IO(&(adc->db[15]), dut_get_io(intf, "DB15"));
}

__FORCEINLINE void ad7616_reset(ad7616_t* adc)
{
    IO_WRITE(GPIOA, GPIO_PIN_1, 1);
    IO_WRITE(GPIOA, GPIO_PIN_1, 0);
    IO_WRITE(GPIOA, GPIO_PIN_1, 1);
    IO_WRITE(GPIOA, GPIO_PIN_1, 0);
    BSP_IO_WRITE(&(adc->resetn), IO_STATE_LOW);
    IO_WRITE(GPIOA, GPIO_PIN_1, 1);
    //HAL_Delay(10);
    BSP_IO_WRITE(&(adc->resetn), IO_STATE_HIGH);
    IO_WRITE(GPIOA, GPIO_PIN_1, 0);
    //HAL_Delay(10);
}


// __AD7616_IOCFG_INLINE void ad7616_dbl_init(uint8_t io_dir)
// {
// }

// __AD7616_IOCFG_INLINE void ad7616_dbh_init(uint8_t io_dir)
// {
// }

// __AD7616_IOCFG_INLINE uint32_t ad7616_reg_read(uint32_t addr)
// {
// }

// __AD7616_IOCFG_INLINE void ad7616_reg_write(uint32_t addr, uint32_t data)
// {
// }

// __AD7616_IOCFG_INLINE uint32_t ad7616_reg_bits_read(uint32_t addr, uint8_t start, uint8_t end)
// {
// }

// __AD7616_IOCFG_INLINE void ad7616_reg_bits_write(uint32_t addr, uint8_t start, uint8_t end, uint32_t data)
// {
// }

// __AD7616_IOCFG_INLINE void ad7616_enter_adc_mode()
// {
// }

// __AD7616_IOCFG_INLINE void ad7616_enter_register_mode()
// {
// }