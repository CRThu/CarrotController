#include "bsp_inc.h"

ft_t default_ft =
{
    .id = "FT2232H-CHA",
    .init = bsp_ft_init,
    .read = bsp_ft_read,
    .write = bsp_ft_write
};

ft_t* bsp_ft_get_instance()
{
    return &default_ft;
}

void bsp_ft_init()
{
    BSP_FT_WRITE_RDN(1);
    BSP_FT_WRITE_WRN(1);
    BSP_FT_IO_SPEED();
    BSP_FT_DDIR_IN();
}

uint16_t bsp_ft_read(uint8_t* buffer, uint16_t size)
{
    uint16_t recv_len = 0;
    BSP_FT_DDIR_IN();
    // read when ft2232h rxfn=0 and buffer is not end
    while (BSP_FT_READ_RXFN() == 0 && recv_len < size)
    {
        // rdn=0
        BSP_FT_WRITE_RDN(0);
        // wait t3, t4, read byte, rdn=1
        BSP_FT_DELAY(BSP_FT_T_RD_D);
        buffer[recv_len] = BSP_FT_READ_D();
        BSP_FT_WRITE_RDN(1);
        recv_len++;
        // wait t1, t3, until rxfn is valid to check next byte
        BSP_FT_DELAY(BSP_FT_T_RD_RXF);
    }
    return recv_len;
}

void bsp_ft_write(uint8_t* buffer, uint16_t size)
{
    uint16_t send_len = 0;
    BSP_FT_DDIR_OUT();
    // write until buffer is end
    while (send_len < size)
    {
        // wait until ft2232h txen=0
        while (BSP_FT_READ_TXEN() != 0)
        {
            ;
        }
        // wrn=0, write byte
        BSP_FT_WRITE_D(buffer[send_len]);
        BSP_FT_WRITE_WRN(0);
        // wait t10 then wrn=1
        BSP_FT_DELAY(BSP_FT_T_WR);
        BSP_FT_WRITE_WRN(1);
        send_len++;
        // wait t6,t7, until txen is valid to check next byte
        BSP_FT_DELAY(BSP_FT_T_WR_TXE);
    }
    BSP_FT_DDIR_IN();
}