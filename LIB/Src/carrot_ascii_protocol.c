#include "carrot_ascii_protocol.h"

carrot_ascii_protocol_config_t carrot_ascii_protocol_config =
{
    .data_protocol = {
        .msg_packet_id = CARROT_BINARY_PROTOCOL_ID_MSG_256,
        .data_packet_id = CARROT_BINARY_PROTOCOL_ID_DATA_266,
        .data_width = CARROT_BINARY_PROTOCOL_DATA_WIDTH_16B,
        .data_encoding = CARROT_BINARY_PROTOCOL_DATA_ENCODING_OFFSET,
        .data_endian = CARROT_BINARY_PROTOCOL_DATA_ENDIAN_LITTLE,
        .data_channel = 0x00,
        .data_interleaved = CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_NOT_USED,
        .data_interleaved_channel_mask = CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_CHANNEL_MASK_NULL,
        .using_crc = CARROT_BINARY_PROTOCOL_CRC_NOT_USED
    }
};

char fmt_buf[256];
carrot_binary_packet_266 pkt;

void write_msg(const char* format, ...)
{
    // TODO add \r\n
    if (carrot_ascii_protocol_config.comm == NULL)
        return;

    uint16_t fmt_buf_len;
    va_list args;

    va_start(args, format);
    fmt_buf_len = vsnprintf(((char*)&fmt_buf), sizeof(fmt_buf), (char*)format, args);
    va_end(args);

    carrot_ascii_protocol_config.comm->write(carrot_ascii_protocol_config.comm->handle, (uint8_t*)fmt_buf, fmt_buf_len);
}

void write_data_internal(uint8_t* data, uint16_t size)
{
    if (carrot_ascii_protocol_config.comm == NULL)
        return;

    pkt.frame_start = CARROT_BINARY_PROTOCOL_FRAME_START;
    pkt.protocol_id = CARROT_BINARY_PROTOCOL_ID_DATA_266;

    pkt.control_flags = carrot_ascii_protocol_config.data_protocol.data_width << 11;
    pkt.control_flags |= carrot_ascii_protocol_config.data_protocol.data_encoding << 10;
    pkt.control_flags |= carrot_ascii_protocol_config.data_protocol.data_endian << 9;
    pkt.control_flags |= carrot_ascii_protocol_config.data_protocol.data_interleaved << 8;
    pkt.control_flags |= carrot_ascii_protocol_config.data_protocol.data_interleaved == CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_USED
        ? carrot_ascii_protocol_config.data_protocol.data_interleaved_channel_mask >> 8
        : CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_CHANNEL_MASK_NULL;

    pkt.stream_id = carrot_ascii_protocol_config.data_protocol.data_interleaved == CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_USED
        ? (carrot_ascii_protocol_config.data_protocol.data_interleaved_channel_mask & 0xFF)
        : carrot_ascii_protocol_config.data_protocol.data_channel;

    pkt.payload_len = size;
    memcpy(pkt.payload, data, sizeof(uint8_t) * size);
    if (size < 256)
        memset(pkt.payload + sizeof(uint8_t) * size, 0, sizeof(uint8_t) * (CARROT_BINARY_PROTOCOL_MAX_PAYLOAD_SIZE_DATA_266 - size));
    pkt.crc = 0xcccc;
    pkt.frame_end = CARROT_BINARY_PROTOCOL_FRAME_END;

    carrot_ascii_protocol_config.comm->write(carrot_ascii_protocol_config.comm->handle, (uint8_t*)&pkt, sizeof(pkt));
}

void write_data(uint8_t* data, uint16_t size)
{
    if (carrot_ascii_protocol_config.comm == NULL || data == NULL || size == 0)
        return;

    uint8_t* pdata = data;
    uint16_t remain_size = size;
    const uint16_t max_payload_size = CARROT_BINARY_PROTOCOL_MAX_PAYLOAD_SIZE_DATA_266;

    while (remain_size > 0)
    {
        uint16_t chunk_size = (remain_size > max_payload_size) ? max_payload_size : remain_size;

        write_data_internal(pdata, chunk_size);

        pdata += chunk_size;
        remain_size -= chunk_size;
    }
}