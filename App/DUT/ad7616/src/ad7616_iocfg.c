/****************************
 AD7616 IO CONFIG
 CRTHu
 2025.03.27
 ****************************/

#include "ad7616_iocfg.h"

__FORCEINLINE void ad7616_set_mode(ad7616_t* adc, ad7616_mode* mode)
{
    adc->mode = mode;
}

__FORCEINLINE void ad7616_set_io(ad7616_t* adc, dut_interface_t* intf)
{
    if (adc->mode == AD7616_SER_SW)
    {
        COPY_FROM_IO(&(adc->convst), dut_get_io(intf, "CONVST"));
        COPY_FROM_IO(&(adc->busy), dut_get_io(intf, "BUSY"));
        COPY_FROM_IO(&(adc->sersel), dut_get_io(intf, "SER/nPAR"));
        COPY_FROM_IO(&(adc->refsel), dut_get_io(intf, "REFSEL"));
        COPY_FROM_IO(&(adc->resetn), dut_get_io(intf, "nRESET"));
        COPY_FROM_IO(&(adc->ser1wn), dut_get_io(intf, "DB4"));
    }

    if (adc->mode == AD7616_PAR_SW)
    {
        COPY_FROM_IO(&(adc->convst), dut_get_io(intf, "CONVST"));
        COPY_FROM_IO(&(adc->busy), dut_get_io(intf, "BUSY"));
        COPY_FROM_IO(&(adc->sersel), dut_get_io(intf, "SER/nPAR"));
        COPY_FROM_IO(&(adc->refsel), dut_get_io(intf, "REFSEL"));
        COPY_FROM_IO(&(adc->resetn), dut_get_io(intf, "nRESET"));
        COPY_FROM_IO(&(adc->csn), dut_get_io(intf, "nCS"));
        COPY_FROM_IO(&(adc->rdn), dut_get_io(intf, "nRD"));
        COPY_FROM_IO(&(adc->wrn), dut_get_io(intf, "nWR"));
    }

    if (adc->mode == AD7616_SER_HW)
    {
        COPY_FROM_IO(&(adc->convst), dut_get_io(intf, "CONVST"));
        COPY_FROM_IO(&(adc->busy), dut_get_io(intf, "BUSY"));
        COPY_FROM_IO(&(adc->sersel), dut_get_io(intf, "SER/nPAR"));
        COPY_FROM_IO(&(adc->refsel), dut_get_io(intf, "REFSEL"));
        COPY_FROM_IO(&(adc->resetn), dut_get_io(intf, "nRESET"));
        COPY_FROM_IO(&(adc->chsel0), dut_get_io(intf, "CHSEL0"));
        COPY_FROM_IO(&(adc->chsel1), dut_get_io(intf, "CHSEL1"));
        COPY_FROM_IO(&(adc->chsel2), dut_get_io(intf, "CHSEL2"));
        COPY_FROM_IO(&(adc->seqen), dut_get_io(intf, "SEQEN"));
        COPY_FROM_IO(&(adc->rngsel0), dut_get_io(intf, "RNGSEL0"));
        COPY_FROM_IO(&(adc->rngsel1), dut_get_io(intf, "RNGSEL1"));
        COPY_FROM_IO(&(adc->ser1wn), dut_get_io(intf, "DB4"));
        COPY_FROM_IO(&(adc->burst), dut_get_io(intf, "nWR"));
        COPY_FROM_IO(&(adc->crcen), dut_get_io(intf, "DB5"));
        COPY_FROM_IO(&(adc->os0), dut_get_io(intf, "OS0"));
        COPY_FROM_IO(&(adc->os1), dut_get_io(intf, "OS1"));
        COPY_FROM_IO(&(adc->os2), dut_get_io(intf, "OS2"));
    }

    if (adc->mode == AD7616_PAR_HW)
    {
        COPY_FROM_IO(&(adc->convst), dut_get_io(intf, "CONVST"));
        COPY_FROM_IO(&(adc->busy), dut_get_io(intf, "BUSY"));
        COPY_FROM_IO(&(adc->sersel), dut_get_io(intf, "SER/nPAR"));
        COPY_FROM_IO(&(adc->refsel), dut_get_io(intf, "REFSEL"));
        COPY_FROM_IO(&(adc->resetn), dut_get_io(intf, "nRESET"));
        COPY_FROM_IO(&(adc->csn), dut_get_io(intf, "nCS"));
        COPY_FROM_IO(&(adc->rdn), dut_get_io(intf, "nRD"));
        COPY_FROM_IO(&(adc->chsel0), dut_get_io(intf, "CHSEL0"));
        COPY_FROM_IO(&(adc->chsel1), dut_get_io(intf, "CHSEL1"));
        COPY_FROM_IO(&(adc->chsel2), dut_get_io(intf, "CHSEL2"));
        COPY_FROM_IO(&(adc->seqen), dut_get_io(intf, "SEQEN"));
        COPY_FROM_IO(&(adc->rngsel0), dut_get_io(intf, "RNGSEL0"));
        COPY_FROM_IO(&(adc->rngsel1), dut_get_io(intf, "RNGSEL1"));
        COPY_FROM_IO(&(adc->burst), dut_get_io(intf, "nWR"));
    }
}

__FORCEINLINE void ad7616_set_perh(ad7616_t* adc)
{
    adc->clk1_pwm = &BTB_CLK1_PWM;   // TODO: IMPL OF BTB_CLK1_PWM
    adc->clk2_etr = &BTB_CLK2_ETR;   // TODO: IMPL OF BTB_CLK2_ETR

    if (adc->mode == AD7616_SER_SW
        || adc->mode == AD7616_SER_HW)
    {
        adc->spi_a = &BTB_SPIA;
        adc->spi_b = &BTB_SPIB;
    }

    if (adc->mode == AD7616_PAR_SW
        || adc->mode == AD7616_PAR_HW)
    {
        adc->par_db = BTB_DB_PORT;
    }
}

__FORCEINLINE void ad7616_full_reset(ad7616_t* adc)
{
    BSP_IO_WRITE(&(adc->resetn), IO_STATE_LOW);
    delay_ns(1200);     // full reset = 1200ns
    BSP_IO_WRITE(&(adc->resetn), IO_STATE_HIGH);
    delay_ms(15);       // full reset = 15ms
}

__FORCEINLINE uint32_t ad7616_reg_read(ad7616_t* adc, uint32_t addr)
{
    if (adc->mode == AD7616_PAR_SW
        || adc->mode == AD7616_PAR_HW)
    {
        /* PAR */
    }
    else
    {
        /* SER */
    }
}

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