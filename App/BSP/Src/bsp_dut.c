#include "bsp_dut.h"


gpio_config_status_t dut_init(dut_interface_t* dut)
{
    uint16_t i = 0;
    while ((dut->pin_configs[i]).btb_pin != IO_ARR_END_ID)
    {
        
        gpio_init(&(dut->pin_configs[i]));
        i++;
    }
    
    switch_init(switch_config);
    switch_set(switch_config, dut->switch_value);



    return GPIO_CONFIG_STATUS_NO_ERR;
}

