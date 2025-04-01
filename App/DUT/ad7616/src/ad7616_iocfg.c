/****************************
 AD7616 IO CONFIG
 CRTHu
 2025.03.27
 ****************************/

#include "ad7616_iocfg.h"

__FORCEINLINE void ad7616_set_mode(ad7616_t* adc, ad7616_mode mode)
{
    adc->mode = mode;
}

__FORCEINLINE void ad7616_set_io(ad7616_t* adc, dut_interface_t* intf)
{
    adc->clk1_pwm = &BTB_CLK1_PWM;   // TODO: IMPL OF BTB_CLK1_PWM
    adc->clk2_etr = &BTB_CLK2_ETR;   // TODO: IMPL OF BTB_CLK2_ETR

    /*
        if (adc->mode == AD7616_SER_SW)
        {
            adc->spi_a = &BTB_SPIA;
            adc->spi_b = &BTB_SPIB;
            COPY_FROM_IO(&(adc->convst), dut_get_io(intf, "CONVST"));
            COPY_FROM_IO(&(adc->busy), dut_get_io(intf, "BUSY"));
            COPY_FROM_IO(&(adc->sersel), dut_get_io(intf, "SER/nPAR"));
            COPY_FROM_IO(&(adc->refsel), dut_get_io(intf, "REFSEL"));
            COPY_FROM_IO(&(adc->resetn), dut_get_io(intf, "nRESET"));
            COPY_FROM_IO(&(adc->ser1wn), dut_get_io(intf, "DB4"));

            // TODO
        }
    */
    if (adc->mode == AD7616_PAR_SW)
    {
        /* USED IO */
        COPY_FROM_IO(&(adc->convst), dut_get_io(intf, "CONVST"));
        BSP_IO_TYPE(&(adc->convst), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->convst), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(adc->convst), IO_STATE_LOW);

        COPY_FROM_IO(&(adc->busy), dut_get_io(intf, "BUSY"));
        BSP_IO_TYPE(&(adc->busy), IO_TYPE_IN);
        BSP_IO_SPEED(&(adc->busy), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(adc->busy), IO_STATE_LOW);

        COPY_FROM_IO(&(adc->sersel), dut_get_io(intf, "SER/nPAR"));
        BSP_IO_TYPE(&(adc->sersel), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->sersel), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(adc->sersel), IO_STATE_LOW);

        COPY_FROM_IO(&(adc->refsel), dut_get_io(intf, "REFSEL"));
        BSP_IO_TYPE(&(adc->refsel), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->refsel), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(adc->refsel), IO_STATE_LOW);

        COPY_FROM_IO(&(adc->resetn), dut_get_io(intf, "nRESET"));
        BSP_IO_TYPE(&(adc->resetn), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->resetn), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(adc->resetn), IO_STATE_HIGH);

        COPY_FROM_IO(&(adc->csn), dut_get_io(intf, "nCS"));
        BSP_IO_TYPE(&(adc->csn), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->csn), IO_SPEED_FAST);
        BSP_IO_WRITE(&(adc->csn), IO_STATE_HIGH);

        COPY_FROM_IO(&(adc->rdn), dut_get_io(intf, "nRD"));
        BSP_IO_TYPE(&(adc->rdn), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->rdn), IO_SPEED_FAST);
        BSP_IO_WRITE(&(adc->rdn), IO_STATE_HIGH);

        COPY_FROM_IO(&(adc->wrn), dut_get_io(intf, "nWR"));
        BSP_IO_TYPE(&(adc->wrn), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->wrn), IO_SPEED_FAST);
        BSP_IO_WRITE(&(adc->wrn), IO_STATE_HIGH);

        /* UNUSED IO */
        COPY_FROM_IO(&(adc->chsel0), dut_get_io(intf, "CHSEL0"));
        BSP_IO_TYPE(&(adc->chsel0), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->chsel0), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(adc->chsel0), IO_STATE_LOW);

        COPY_FROM_IO(&(adc->chsel1), dut_get_io(intf, "CHSEL1"));
        BSP_IO_TYPE(&(adc->chsel1), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->chsel1), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(adc->chsel1), IO_STATE_LOW);

        COPY_FROM_IO(&(adc->chsel2), dut_get_io(intf, "CHSEL2"));
        BSP_IO_TYPE(&(adc->chsel2), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->chsel2), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(adc->chsel2), IO_STATE_LOW);

        COPY_FROM_IO(&(adc->seqen), dut_get_io(intf, "SEQEN"));
        BSP_IO_TYPE(&(adc->seqen), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->seqen), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(adc->seqen), IO_STATE_LOW);

        COPY_FROM_IO(&(adc->rngsel0), dut_get_io(intf, "RNGSEL0"));
        BSP_IO_TYPE(&(adc->rngsel0), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->rngsel0), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(adc->rngsel0), IO_STATE_LOW);

        COPY_FROM_IO(&(adc->rngsel1), dut_get_io(intf, "RNGSEL1"));
        BSP_IO_TYPE(&(adc->rngsel1), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->rngsel1), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(adc->rngsel1), IO_STATE_LOW);

        /* PERH */
        adc->spi_a = NULL;
        adc->spi_b = NULL;
        adc->par_db = BTB_DB_PORT;

        BSP_DB_TYPE(adc->par_db, IO_TYPE_IN);
        BSP_DB_SPEED(adc->par_db, IO_SPEED_FAST);
        BSP_DB_WRITE(adc->par_db, IO_STATE_LOW);
    }

    /*
        if (adc->mode == AD7616_SER_HW)
        {
            adc->spi_a = &BTB_SPIA;
            adc->spi_b = &BTB_SPIB;
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

            // TODO
        }

        if (adc->mode == AD7616_PAR_HW)
        {
            adc->par_db = BTB_DB_PORT;
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

            // TODO
        }

        */
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
    uint16_t wr_cmd = AD7616_PAR_RD << 15 | addr << 9 | 0 << 0;
    uint16_t rd_data = 0;

    if (adc->mode == AD7616_PAR_SW
        || adc->mode == AD7616_PAR_HW)
    {
        /* PAR */

        /* WRITE COMMAND */
        BSP_DB_TYPE(adc->par_db, IO_TYPE_OUT);
        BSP_IO_WRITE(&(adc->csn), IO_STATE_LOW);
        AD7616_DELAY(AD7616_PAR_T_WRN_SETUP);
        BSP_IO_WRITE(&(adc->wrn), IO_STATE_LOW);
        BSP_DB_WRITE(adc->par_db, wr_cmd);
        AD7616_DELAY(T_MAX(AD7616_PAR_T_DIN_SETUP, AD7616_PAR_T_WRN_LOW));
        BSP_IO_WRITE(&(adc->wrn), IO_STATE_HIGH);
        AD7616_DELAY(AD7616_PAR_T_WRN_HOLD);
        BSP_IO_WRITE(&(adc->csn), IO_STATE_HIGH);

        /* READ COMMAND */
        BSP_DB_TYPE(adc->par_db, IO_TYPE_IN);
        BSP_IO_WRITE(&(adc->csn), IO_STATE_LOW);
        AD7616_DELAY(AD7616_PAR_T_RDN_SETUP);
        BSP_IO_WRITE(&(adc->rdn), IO_STATE_LOW);
        AD7616_DELAY(AD7616_PAR_T_DOUT_SETUP);
        rd_data = BSP_DB_READ(adc->par_db);
        AD7616_DELAY(T_SUB(AD7616_PAR_T_RDN_LOW, AD7616_PAR_T_DOUT_SETUP));
        BSP_IO_WRITE(&(adc->rdn), IO_STATE_HIGH);
        AD7616_DELAY(AD7616_PAR_T_RDN_HOLD);
        BSP_IO_WRITE(&(adc->csn), IO_STATE_HIGH);
        AD7616_DELAY(AD7616_PAR_T_DOUT_3STATE);
    }
    else
    {
        /* SER */
        // TODO IMPL
    }

    return rd_data;
}

__FORCEINLINE void ad7616_reg_write(ad7616_t* adc, uint32_t addr, uint32_t data)
{
    uint16_t wr_cmd = (((AD7616_PAR_WR << 15) | (addr & 0x3F) << 9) | ((data & 0x1FF) << 0));

    if (adc->mode == AD7616_PAR_SW
        || adc->mode == AD7616_PAR_HW)
    {
        /* PAR */

        /* WRITE COMMAND */
        BSP_DB_TYPE(adc->par_db, IO_TYPE_OUT);
        BSP_IO_WRITE(&(adc->csn), IO_STATE_LOW);
        AD7616_DELAY(AD7616_PAR_T_WRN_SETUP);
        BSP_IO_WRITE(&(adc->wrn), IO_STATE_LOW);
        BSP_DB_WRITE(adc->par_db, wr_cmd);
        AD7616_DELAY(T_MAX(AD7616_PAR_T_DIN_SETUP, AD7616_PAR_T_WRN_LOW));
        BSP_IO_WRITE(&(adc->wrn), IO_STATE_HIGH);
        AD7616_DELAY(AD7616_PAR_T_WRN_HOLD);
        BSP_IO_WRITE(&(adc->csn), IO_STATE_HIGH);
    }
    else
    {
        /* SER */
        // TODO IMPL
    }

}

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


int8_t ad7616_comm_test(ad7616_t* adc)
{
    uint16_t txdata, rxdata;

    for (uint8_t reg = 0x04; reg <= 0x07; reg++)
    {
        txdata = 0x00;
        rxdata = 0xCC;

        ad7616_reg_write(adc, reg, txdata);
        rxdata = ad7616_reg_read(adc, reg);
        if (rxdata != txdata)    return -1;
        delay_us(10);

        txdata = 0x55;
        rxdata = 0xCC;

        ad7616_reg_write(adc, reg, txdata);
        rxdata = ad7616_reg_read(adc, reg);
        if (rxdata != txdata)    return -1;
        delay_us(10);

        txdata = 0xAA;
        rxdata = 0xCC;

        ad7616_reg_write(adc, reg, txdata);
        rxdata = ad7616_reg_read(adc, reg);
        if (rxdata != txdata)    return -1;
        delay_us(10);

        txdata = 0xFF;
        rxdata = 0xCC;

        ad7616_reg_write(adc, reg, txdata);
        rxdata = ad7616_reg_read(adc, reg);
        if (rxdata != txdata)    return -1;
        delay_us(10);
    }

    return 0;
}