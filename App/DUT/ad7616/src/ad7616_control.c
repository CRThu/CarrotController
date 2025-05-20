/****************************
* AD7616 CONTROL
* CRTHu
* 2025.03.27
*****************************/
#include "ad7616_control.h"

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< FOR PROTOCOL TEST >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void print_hex(dyn_hex64p_t a)
{
    //PRINT_FUNC_SIGNATURE();
    bsp_uart_printf("[info]: print_hex(0x%"PRIX64") Called.\r\n", PVAL(a));
}

void print_string(dyn_string_t a)
{
    //PRINT_FUNC_SIGNATURE();
    bsp_uart_printf("[info]: print_string(%s) Called.\r\n", PREF(a));
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< AD7616 INIT OPER >>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< AD7616 REG OPER >>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< AD7616 SAMPLE OPER >>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< FUNCTION REGISTER >>>>>>>>>>>>>>>>>>>>>>>>>>>>>





function_group_t ad7616_func_group =
{
    FUNCTION_GROUP("default_func_group",
        FUNCTION_INFO(print_hex, T_NULL, T_HEX64),
        FUNCTION_INFO(print_string, T_NULL, T_STRING),
    )
};
