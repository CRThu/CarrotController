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

// pin name: name
io_t* dut_get_io(dut_interface_t* dut, const char* name)
{
    uint16_t i = 0;
    while ((dut->pin_configs[i]).btb_pin != IO_ARR_END_ID)
    {
        if (strcmp(dut->pin_configs[i].pin_name, name) == 0)
            return &(dut->pin_configs[i]);
        i++;
    }
    return NULL;
}


// pin name: name[id]
io_t* dut_get_io_id(dut_interface_t* dut, uint8_t id, const char* name)
{
    char name_id[IO_PIN_NAME_MAX_LEN + 8];

    if (snprintf(name_id, sizeof(name_id), "%s[%d]", name, id) >= sizeof(name_id))
        return NULL; // OVERFLOW
    uint16_t i = 0;
    while ((dut->pin_configs[i]).btb_pin != IO_ARR_END_ID)
    {
        if (strcmp(dut->pin_configs[i].pin_name, name_id) == 0)
            return &(dut->pin_configs[i]);
        i++;
    }
    return NULL;
}