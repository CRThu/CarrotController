#include "ft_comm.h"

ft_comm_t* ft_comm_create(ft_t* hft, uint16_t dmabuf_len)
{
    ft_comm_t* comm = (ft_comm_t*)malloc(sizeof(ft_comm_t));
    if (!comm)
        return NULL;

    comm->instance = hft;
    comm->dmabuf_len = dmabuf_len;
    comm->rxdma_pos_wr = 0;
    comm->rxdma_pos_rd = 0;
    comm->rxdma_pos_parse = 0;
    comm->error = FT_COMM_NO_ERR;

    comm->rxdma_buf = (uint8_t*)malloc(comm->dmabuf_len);

    if (!comm->rxdma_buf)
    {
        free(comm->rxdma_buf);
        free(comm);
        return NULL;
    }
    return comm;
}

void ft_comm_destory(ft_comm_t* comm)
{
    if (comm)
    {
        free(comm->rxdma_buf);
        free(comm);
    }
}

void ft_comm_print_info(const ft_comm_t* comm)
{
    if (comm)
    {
        PRINTF("\n");
    }
}

void ft_comm_start(ft_comm_t* comm)
{

}

void ft_comm_stop(ft_comm_t* comm)
{

}

void ft_comm_write(ft_comm_t* comm, const uint8_t* txcmd, uint16_t size)
{
    comm->instance->write(txcmd, size);
}

uint16_t ft_comm_read(ft_comm_t* comm, uint8_t* buf, uint16_t size)
{
}
