#include "bsp_init.h"

comm_t* default_comm;

void bsp_init()
{
    // initial cdelay module
    if (cdelay_init() == 0)
        Error_Handler();


    #if(CARROT_CONTROLLER_HW == STM32H563_CONTROLLER)
    // set board default switches
    bsp_sw_default();
    uint16_t sw_status = bsp_sw_get_status();

    // initial ft2232h
    //comm_t* ft = bsp_ft_create(FT_D0_GPIO_Port);
    //ft->init(ft->handle);
    #endif

    // initial uart4 with ringbuf
    comm_t* uart4_ringbuf = bsp_uart_ringbuf_create(&huart4);
    uart4_ringbuf->init(uart4_ringbuf->handle);

    default_comm = uart4_ringbuf;

    // initial psram
    bsp_psram_reset();

    // set protocol comm
    carrot_ascii_protocol_config.comm = default_comm;
    //carrot_ascii_protocol_config.comm = uart4_ringbuf;
    //carrot_ascii_protocol_config.comm = ft;

    // set protocol data type
    //carrot_ascii_protocol_config.data_protocol.data_width = CARROT_BINARY_PROTOCOL_DATA_WIDTH_16B;
    //carrot_ascii_protocol_config.data_protocol.data_encoding = CARROT_BINARY_PROTOCOL_DATA_ENCODING_OFFSET;
    //carrot_ascii_protocol_config.data_protocol.data_endian = CARROT_BINARY_PROTOCOL_DATA_ENDIAN_LITTLE;
    // use this when has one channel data
    //carrot_ascii_protocol_config.data_protocol.data_interleaved = CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_NOT_USED;
    //carrot_ascii_protocol_config.data_protocol.data_channel = 0x0;
    // use this when has multichannels data
    // carrot_ascii_protocol_config.data_protocol.data_interleaved = CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_USED;
    // carrot_ascii_protocol_config.data_protocol.data_interleaved_channel_mask = CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_CHANNEL_MASK_16CH;
}