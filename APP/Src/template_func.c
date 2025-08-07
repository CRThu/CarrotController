/****************************
* TEMPLATE FUNC
* CRTHu
* 2025.08.07
*****************************/
#include "template_func.h"

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<< FOR PROTOCOL TEST >>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void print_hex(dyn_hex64p_t a)
{
    //PRINT_FUNC_SIGNATURE();
    printf("[info]: print_hex(0x%"PRIX64") Called.\r\n", PVAL(a));
}

void print_string(dyn_string_t a)
{
    //PRINT_FUNC_SIGNATURE();
    printf("[info]: print_string(%s) Called.\r\n", PREF(a));
}

function_group_t template_func_group =
{
    FUNCTION_GROUP("template_func_group",
        FUNCTION_INFO(print_hex, T_NULL, T_HEX64),
        FUNCTION_INFO(print_string, T_NULL, T_STRING),
    )
};
