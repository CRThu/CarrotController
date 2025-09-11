#include "bsp_ft.h"

#if(CARROT_CONTROLLER_HW == STM32H563_CONTROLLER)

void bsp_ft_init(comm_handle handle)
{
    BSP_FT_WRITE_RDN(handle, 1);
    BSP_FT_WRITE_WRN(handle, 1);
    BSP_FT_IO_SPEED(handle);
    BSP_FT_DDIR_IN(handle);
}

uint16_t bsp_ft_read(comm_handle handle, uint8_t* buffer, uint16_t size)
{
    uint16_t recv_len = 0;
    BSP_FT_DDIR_IN(handle);
    // read when ft2232h rxfn=0 and buffer is not end
    while (BSP_FT_READ_RXFN(handle) == 0 && recv_len < size)
    {
        // rdn=0
        BSP_FT_WRITE_RDN(handle, 0);
        // wait t3, t4, read byte, rdn=1
        BSP_FT_DELAY(BSP_FT_T_RD_D);
        buffer[recv_len] = BSP_FT_READ_D(handle);
        BSP_FT_WRITE_RDN(handle, 1);
        recv_len++;
        // wait t1, t3, until rxfn is valid to check next byte
        BSP_FT_DELAY(BSP_FT_T_RD_RXF);
    }
    return recv_len;
}

void bsp_ft_write(comm_handle handle, uint8_t* buffer, uint16_t size)
{
    uint16_t send_len = 0;
    BSP_FT_DDIR_OUT(handle);
    // write until buffer is end
    while (send_len < size)
    {
        // wait until ft2232h txen=0
        while (BSP_FT_READ_TXEN(handle) != 0)
        {
            ;
        }
        // wrn=0, write byte
        BSP_FT_WRITE_D(handle, buffer[send_len]);
        BSP_FT_WRITE_WRN(handle, 0);
        // wait t10 then wrn=1
        BSP_FT_DELAY(BSP_FT_T_WR);
        BSP_FT_WRITE_WRN(handle, 1);
        send_len++;
        // wait t6,t7, until txen is valid to check next byte
        BSP_FT_DELAY(BSP_FT_T_WR_TXE);
    }
    BSP_FT_DDIR_IN(handle);
}

comm_t* bsp_ft_create(GPIO_TypeDef* GPIOx)
{
    comm_t* comm = (comm_t*)malloc(sizeof(comm_t));
    if (!comm)
        return NULL;

    comm->id = "FT-A-ASYNC-FIFO";
    comm->handle = GPIOx;
    comm->init = bsp_ft_init;
    comm->read = bsp_ft_read;
    comm->write = bsp_ft_write;

    return comm;
}

void bsp_ft_destory(comm_t* comm)
{
    if (comm)
    {
        free(comm);
    }
}

#endif