/****************************
 AD7616 IO CONFIG
 CRTHu
 2025.03.27
 ****************************/

#include "ad7616_iocfg.h"

// __AD7616_IOCFG_INLINE void ad7616_dbl_init(uint8_t io_dir)
// {
// }

// __AD7616_IOCFG_INLINE void ad7616_dbh_init(uint8_t io_dir)
// {
// }

__FORCEINLINE void ad7616_reset(ad7616_t* adc)
{
    IO_WRITE(GPIOA, GPIO_PIN_1,1);
    IO_WRITE(GPIOA, GPIO_PIN_1,0);
    IO_WRITE(GPIOA, GPIO_PIN_1,1);
    io_t* io_rstn = dut_get_io(adc->dut_interface, "nRESET");
    IO_WRITE(GPIOA, GPIO_PIN_1,0);
    BSP_IO_WRITE(io_rstn, IO_STATE_LOW);
    IO_WRITE(GPIOA, GPIO_PIN_1,1);
    //HAL_Delay(10);
    BSP_IO_WRITE(io_rstn, IO_STATE_HIGH);
    IO_WRITE(GPIOA, GPIO_PIN_1,0);
    //HAL_Delay(10);
}

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