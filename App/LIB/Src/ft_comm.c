#include "ft_comm.h"

#define FT_COMM_TEMP_ARR_SIZE 256
uint8_t temp_arr[FT_COMM_TEMP_ARR_SIZE];

ft_comm_t* ft_comm_create(ft_t* hft, uint16_t dmabuf_len)
{
    ft_comm_t* comm = (ft_comm_t*)malloc(sizeof(ft_comm_t));
    if (!comm)
        return NULL;

    comm->instance = hft;
    comm->rxbuf = commbuf_create(dmabuf_len);

    if (!comm->rxbuf)
    {
        commbuf_free(comm->rxbuf);
        free(comm);
        return NULL;
    }
    return comm;
}

void ft_comm_free(ft_comm_t* comm)
{
    if (comm)
    {
        commbuf_free(comm->rxbuf);
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

void ft_comm_write(ft_comm_t* comm, const uint8_t* txcmd, uint16_t size)
{
    comm->instance->write(txcmd, size);
}

uint16_t ft_comm_read(ft_comm_t* comm, uint8_t* buf, uint16_t size)
{
    uint16_t read_size = fmin(FT_COMM_TEMP_ARR_SIZE, commbuf_get_space(comm->rxbuf));
    uint16_t rxsize = comm->instance->read(temp_arr, read_size);
    if (!rxsize) return 0;

    // received any data
    uint16_t written_size = commbuf_write(comm->rxbuf, temp_arr, rxsize);
    if (written_size != rxsize)
        return -1;

    // check protocol
    uint16_t len = commbuf_get_len(comm->rxbuf);
    uint8_t val;
    for (int i = 0; i < len; i++)
    {
        if (commbuf_peek(comm->rxbuf, i, &val) == COMMBUF_NO_ERR)
        {
            if (val == '\n')
            {
                if (size <= i) return -3;

                uint16_t read_size = commbuf_read(comm->rxbuf, buf, i + 1);
                if (read_size != i + 1)
                    return -1;
                else
                    return read_size;
            }
        }
        else
            return -2;
    }
}
