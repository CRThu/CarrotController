#include "bsp_inc.h"
#include "spi.h"

spi_t spi_instances[] =
{
    {.id = 1, .instance = &hspi1},
    {.id = 2, .instance = &hspi3},
    {.id = -1}
};