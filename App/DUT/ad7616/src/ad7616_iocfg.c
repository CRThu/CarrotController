/****************************
 AD7616 IO CONFIG
 CRTHu
 2025.04.01
 ****************************/

#include "ad7616_iocfg.h"

__FORCEINLINE void ad7616_set_io_convst(ad7616_t* adc, ad7616_convst_mode mode)
{
    if (mode == AD7616_CONVST_IO)
    {
        bsp_pwm_io_init(0, 0);

        /* SER/PAR SW/HW Shared IO */
        BSP_IO_TYPE(&(adc->convst), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->convst), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(adc->convst), IO_STATE_LOW);
    }
    else /* AD7616_CONVST_PWM */
    {
        bsp_pwm_io_init(0, 1);
    }
}

__FORCEINLINE void ad7616_set_io(ad7616_t* adc, dut_interface_t* intf)
{
    ad7616_io_t initial_io;

    /* PERH */
    adc->pwm1 = bsp_get_tim_instance(0);
    adc->etr2 = BTB_CLK2_ETR;   // TODO: IMPL OF BTB_CLK2_ETR

    /* PERH IOCFG */
    // default: use CONVST PWM MODE
    //bsp_pwm_io_init(0, 1);

    // default: use CONVST PWM MODE
    /* SER/PAR SW/HW Shared IO */
    COPY_FROM_IO(&(adc->convst), dut_get_io(intf->pin_configs, "CONVST"));
    //BSP_IO_TYPE(&(adc->convst), IO_TYPE_OUT);
    //BSP_IO_SPEED(&(adc->convst), IO_SPEED_NORMAL);
    //BSP_IO_WRITE(&(adc->convst), IO_STATE_LOW);

    ad7616_set_io_convst(adc, AD7616_CONVST_PWM);

    COPY_FROM_IO(&(adc->busy), dut_get_io(intf->pin_configs, "BUSY"));
    BSP_IO_TYPE(&(adc->busy), IO_TYPE_IN);
    BSP_IO_SPEED(&(adc->busy), IO_SPEED_NORMAL);
    BSP_IO_WRITE(&(adc->busy), IO_STATE_LOW);

    COPY_FROM_IO(&(adc->refsel), dut_get_io(intf->pin_configs, "REFSEL"));
    BSP_IO_TYPE(&(adc->refsel), IO_TYPE_OUT);
    BSP_IO_SPEED(&(adc->refsel), IO_SPEED_NORMAL);
    BSP_IO_WRITE(&(adc->refsel), IO_STATE_LOW);

    COPY_FROM_IO(&(adc->resetn), dut_get_io(intf->pin_configs, "nRESET"));
    BSP_IO_TYPE(&(adc->resetn), IO_TYPE_OUT);
    BSP_IO_SPEED(&(adc->resetn), IO_SPEED_NORMAL);
    BSP_IO_WRITE(&(adc->resetn), IO_STATE_HIGH);

    if (adc->mode == AD7616_SER_SW)
    {
        /*
            COPY_FROM_IO(&(adc->csn), dut_get_io(intf->pin_configs, "nCSA"));
            BSP_IO_TYPE(&(adc->csn), IO_TYPE_OUT);
            BSP_IO_SPEED(&(adc->csn), IO_SPEED_FAST);
            BSP_IO_WRITE(&(adc->csn), IO_STATE_HIGH);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SCKA"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_HIGH);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SDIA"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_HIGH);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SDOA"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "nCSB"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SCKB"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SDIB"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SDOB"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);
        */

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "CHSEL0"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "CHSEL1"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "CHSEL2"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SEQEN"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "RNGSEL0"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "RNGSEL1"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SERSEL"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_HIGH);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "nRD"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "nWR"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB0"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB1"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB2"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB3"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(adc->ser1wn), dut_get_io(intf->pin_configs, "DB4"));
        BSP_IO_TYPE(&(adc->ser1wn), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->ser1wn), IO_SPEED_FAST);
        BSP_IO_WRITE(&(adc->ser1wn), (adc->serial_wire == 1) ? IO_STATE_LOW : IO_STATE_HIGH);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB5"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB6"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB7"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB8"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB9"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB10"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB11"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB12"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB13"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB14"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB15"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);


        /* PERH */
        adc->spi_a = bsp_get_spi_instance(0);
        adc->spi_b = bsp_get_spi_instance(1);
        adc->par_db = NULL;

        /* PERH IOCFG */
        bsp_spi_io_config(0, BSP_SPI_IO_MODE_CRT);
        bsp_spi_perh_config(0, BSP_SPI_MODE_MASTER, BSP_SPI_DATA_SIZE_16B, BSP_SPI_CLK_PSC_8, BSP_SPI_CPHA_0, BSP_SPI_CPOL_1);
        bsp_spi_io_config(1, BSP_SPI_IO_MODE_CR_CSIN_SCKIN);
        bsp_spi_perh_config(1, BSP_SPI_MODE_SLAVE, BSP_SPI_DATA_SIZE_16B, BSP_SPI_CLK_PSC_8, BSP_SPI_CPHA_0, BSP_SPI_CPOL_1);
    }

    if (adc->mode == AD7616_PAR_SW)
    {
        COPY_FROM_IO(&(adc->csn), dut_get_io(intf->pin_configs, "nCSA"));
        BSP_IO_TYPE(&(adc->csn), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->csn), IO_SPEED_FAST);
        BSP_IO_WRITE(&(adc->csn), IO_STATE_HIGH);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SCKA"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SDIA"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SDOA"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "nCSB"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SCKB"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SDIB"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SDOB"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "CHSEL0"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "CHSEL1"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "CHSEL2"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SEQEN"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "RNGSEL0"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "RNGSEL1"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "SERSEL"));
        BSP_IO_TYPE(&(initial_io), IO_TYPE_OUT);
        BSP_IO_SPEED(&(initial_io), IO_SPEED_NORMAL);
        BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

        COPY_FROM_IO(&(adc->rdn), dut_get_io(intf->pin_configs, "nRD"));
        BSP_IO_TYPE(&(adc->rdn), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->rdn), IO_SPEED_FAST);
        BSP_IO_WRITE(&(adc->rdn), IO_STATE_HIGH);

        COPY_FROM_IO(&(adc->wrn), dut_get_io(intf->pin_configs, "nWR"));
        BSP_IO_TYPE(&(adc->wrn), IO_TYPE_OUT);
        BSP_IO_SPEED(&(adc->wrn), IO_SPEED_FAST);
        BSP_IO_WRITE(&(adc->wrn), IO_STATE_HIGH);

        /*
            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB0"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB1"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB2"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB3"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB4"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_HIGH);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB5"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB6"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB7"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB8"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB9"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB10"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB11"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB12"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB13"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB14"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);

            COPY_FROM_IO(&(initial_io), dut_get_io(intf->pin_configs, "DB15"));
            BSP_IO_TYPE(&(initial_io), IO_TYPE_IN);
            BSP_IO_SPEED(&(initial_io), IO_SPEED_FAST);
            BSP_IO_WRITE(&(initial_io), IO_STATE_LOW);
        */

        /* PERH */
        adc->spi_a = NULL;
        adc->spi_b = NULL;
        adc->par_db = BTB_DB_PORT;

        /* PERH IOCFG */
        BSP_DB_TYPE(adc->par_db, IO_TYPE_IN);
        BSP_DB_SPEED(adc->par_db, IO_SPEED_FAST);
        BSP_DB_WRITE(adc->par_db, IO_STATE_LOW);
    }

    /*
        if (adc->mode == AD7616_SER_HW)
        {
        }

        if (adc->mode == AD7616_PAR_HW)
        {
    */
}

__FORCEINLINE void ad7616_full_reset(ad7616_t* adc)
{
    BSP_IO_WRITE(&(adc->resetn), IO_STATE_LOW);
    delay_ns(1200);     // full reset = 1200ns
    BSP_IO_WRITE(&(adc->resetn), IO_STATE_HIGH);
    delay_ms(15);       // full reset = 15ms
}

__FORCEINLINE uint16_t ad7616_reg_read(ad7616_t* adc, uint32_t addr)
{
    uint16_t regcmd[2];
    regcmd[0] = AD7616_PAR_RD << 15 | addr << 9 | 0 << 0;
    regcmd[1] = 0;

    if (adc->mode == AD7616_PAR_SW
        || adc->mode == AD7616_PAR_HW)
    {
        /* PAR */

        /* WRITE COMMAND */
        BSP_DB_TYPE(adc->par_db, IO_TYPE_OUT);
        BSP_IO_WRITE(&(adc->csn), IO_STATE_LOW);
        AD7616_DELAY(AD7616_PAR_T_WRN_SETUP);
        BSP_IO_WRITE(&(adc->wrn), IO_STATE_LOW);
        BSP_DB_WRITE(adc->par_db, regcmd[0]);
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
        regcmd[1] = BSP_DB_READ(adc->par_db);
        AD7616_DELAY(T_SUB(AD7616_PAR_T_RDN_LOW, AD7616_PAR_T_DOUT_SETUP));
        BSP_IO_WRITE(&(adc->rdn), IO_STATE_HIGH);
        AD7616_DELAY(AD7616_PAR_T_RDN_HOLD);
        BSP_IO_WRITE(&(adc->csn), IO_STATE_HIGH);
        AD7616_DELAY(AD7616_PAR_T_DOUT_3STATE);
    }
    else
    {
        /* SER */
        while (hspi1.State != HAL_SPI_STATE_READY);
        bsp_spi_write(adc->spi_a, (uint8_t*)&regcmd[0], 1);
        while (hspi1.State != HAL_SPI_STATE_READY);
        bsp_spi_read(adc->spi_a, (uint8_t*)&regcmd[1], 1);
        //bsp_spi_readwrite(adc->spi_a, (uint8_t*)regcmd, (uint8_t*)regcmd, 2);
    }

    return regcmd[1];
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
        // uint8_t wr_cmd_arr[2];
        // wr_cmd_arr[0] = wr_cmd >> 8;
        // wr_cmd_arr[1] = wr_cmd;


        //HAL_SPI_Transmit(&hspi1,wr_cmd_arr,sizeof(wr_cmd_arr),100);
        while (hspi1.State != HAL_SPI_STATE_READY);
        //BSP_IO_WRITE(&(adc->convst), 1);
        //HAL_SPI_Transmit(adc->spi_a,wr_cmd_arr,sizeof(wr_cmd_arr),100);
        //bsp_spi_write(adc->spi_a, wr_cmd_arr, sizeof(wr_cmd_arr));

        // DATASIZE=8
        //bsp_spi_write(adc->spi_a, wr_cmd_arr, sizeof(wr_cmd_arr));
        // DATASIZE=16
        bsp_spi_write(adc->spi_a, (uint8_t*)&wr_cmd, 1);
        //BSP_IO_WRITE(&(adc->convst), 0);
    }

}

__FORCEINLINE uint16_t ad7616_reg_bits_read(ad7616_t* adc, uint32_t addr, uint8_t start, uint8_t end)
{
    return BITS_GET(ad7616_reg_read(adc, addr), start, end);
}

__FORCEINLINE void ad7616_reg_bits_write(ad7616_t* adc, uint32_t addr, uint8_t start, uint8_t end, uint32_t data)
{
    ad7616_reg_write(adc, addr, BITS_SET(ad7616_reg_read(adc, addr), start, end, data));
}

__FORCEINLINE uint16_t ad7616_data_read(ad7616_t* adc)
{
    uint16_t rd_data = 0;

    if (adc->mode == AD7616_PAR_SW
        || adc->mode == AD7616_PAR_HW)
    {
        /* PAR */

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
    }
    else
    {
        /* SER: READ ONLY CHA */
        while (hspi1.State != HAL_SPI_STATE_READY);
        bsp_spi_read(adc->spi_a, (uint8_t*)&rd_data, 1);
    }

    return rd_data;
}

__FORCEINLINE void ad7616_data_read_two(ad7616_t* adc, uint16_t* pa, uint16_t* pb)
{
    if (adc->mode == AD7616_PAR_SW
        || adc->mode == AD7616_PAR_HW)
    {
        /* PAR */

        /* READ COMMAND */
        BSP_DB_TYPE(adc->par_db, IO_TYPE_IN);
        BSP_IO_WRITE(&(adc->csn), IO_STATE_LOW);
        AD7616_DELAY(AD7616_PAR_T_RDN_SETUP);
        BSP_IO_WRITE(&(adc->rdn), IO_STATE_LOW);
        AD7616_DELAY(AD7616_PAR_T_DOUT_SETUP);
        *pa = BSP_DB_READ(adc->par_db);
        AD7616_DELAY(T_SUB(AD7616_PAR_T_RDN_LOW, AD7616_PAR_T_DOUT_SETUP));
        BSP_IO_WRITE(&(adc->rdn), IO_STATE_HIGH);
        AD7616_DELAY(AD7616_PAR_T_RDN_HOLD);
        BSP_IO_WRITE(&(adc->csn), IO_STATE_HIGH);

        AD7616_DELAY(AD7616_PAR_T_CSN_HIGH);

        BSP_IO_WRITE(&(adc->csn), IO_STATE_LOW);
        AD7616_DELAY(AD7616_PAR_T_RDN_SETUP);
        BSP_IO_WRITE(&(adc->rdn), IO_STATE_LOW);
        AD7616_DELAY(AD7616_PAR_T_DOUT_SETUP);
        *pb = BSP_DB_READ(adc->par_db);
        AD7616_DELAY(T_SUB(AD7616_PAR_T_RDN_LOW, AD7616_PAR_T_DOUT_SETUP));
        BSP_IO_WRITE(&(adc->rdn), IO_STATE_HIGH);
        AD7616_DELAY(AD7616_PAR_T_RDN_HOLD);
        BSP_IO_WRITE(&(adc->csn), IO_STATE_HIGH);
    }
    else
    {
        /* SER: READ ONLY CHA */
        if (adc->serial_wire == 1)
        {
            uint16_t data[2] = { 0 };

            while ((adc->spi_a)->State != HAL_SPI_STATE_READY);
            bsp_spi_read(adc->spi_a, (uint8_t*)data, 2);

            *pa = data[0];
            *pb = data[1];
        }
        else
        {
            // TODO
            while ((adc->spi_a)->State != HAL_SPI_STATE_READY);
            while ((adc->spi_b)->State != HAL_SPI_STATE_READY);
            HAL_SPI_Receive_IT(adc->spi_b, (uint8_t*)pb, 1);
            bsp_spi_read(adc->spi_a, (uint8_t*)pa, 1);
        }
    }
}

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