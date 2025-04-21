#include "bsp_dut.h"


int8_t dut_init(dut_interface_t* dut)
{
    uint16_t i = 0;
    while ((dut->pin_configs[i]).btb_pin != IO_ARR_END_ID)
    {

        bsp_io_preset(&(dut->pin_configs[i]));
        i++;
    }

    switch_init(switch_config);
    switch_set(switch_config, dut->switch_value);



    return 0;
}

// pin name: name
__FORCEINLINE io_t* dut_get_io(io_t* io_cfg, const char* name)
{
    uint16_t i = 0;
    while ((io_cfg[i]).btb_pin != IO_ARR_END_ID)
    {
        if (strcmp(io_cfg[i].pin_name, name) == 0)
            return &(io_cfg[i]);
        i++;
    }
    return NULL;
}


// pin name: name[id]
io_t* dut_get_io_id(io_t* io_cfg, uint8_t id, const char* name)
{
    char name_id[IO_PIN_NAME_MAX_LEN + 8];

    if (snprintf(name_id, sizeof(name_id), "%s[%d]", name, id) >= sizeof(name_id))
        return NULL; // OVERFLOW
    uint16_t i = 0;
    while ((io_cfg[i]).btb_pin != IO_ARR_END_ID)
    {
        if (strcmp(io_cfg[i].pin_name, name_id) == 0)
            return &(io_cfg[i]);
        i++;
    }
    return NULL;
}