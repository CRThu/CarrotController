#include "carrot_ascii_protocol.h"

carrot_ascii_protocol_config_t carrot_ascii_protocol_config;
// carrot_ascii_protocol_config_t carrot_ascii_protocol_config =
// {
//    .data_protocol = {
//        .msg_packet_id = CARROT_BINARY_PROTOCOL_ID_MSG_256,
//        .data_packet_id = CARROT_BINARY_PROTOCOL_ID_DATA_266,
//        .data_width = CARROT_BINARY_PROTOCOL_DATA_WIDTH_16B,
//        .data_encoding = CARROT_BINARY_PROTOCOL_DATA_ENCODING_OFFSET,
//        .data_endian = CARROT_BINARY_PROTOCOL_DATA_ENDIAN_LITTLE,
//        .data_channel = 0x00,
//        .data_interleaved = CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_NOT_USED,
//        .data_interleaved_channel_mask = CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_CHANNEL_MASK_NULL,
//        .using_crc = CARROT_BINARY_PROTOCOL_CRC_NOT_USED
//    }
// };

char fmt_buf[256];
carrot_binary_packet_266 pkt;

void write_msg(const char* format, ...)
{
    if (carrot_ascii_protocol_config.comm == NULL)
        return;

    va_list args;

    va_start(args, format);
    int len = vsnprintf(((char*)&fmt_buf), sizeof(fmt_buf) - 3, (char*)format, args);
    va_end(args);

    if (len <= 0) return;

    if (fmt_buf[len - 1] != '\n')
    {
        fmt_buf[len++] = '\r';
        fmt_buf[len++] = '\n';
        fmt_buf[len] = '\0';
    }

    carrot_ascii_protocol_config.comm->write(carrot_ascii_protocol_config.comm->handle, (uint8_t*)fmt_buf, len);
}

/**
 * @brief 发送通用数据
 * [ DATA [.PATH] ]: [KEY=] VALUE [,KEY=VALUE] \r\n
 * 示例: 
 * write_data("", "111");                   -> [DATA]:111
 * write_data("ADDR", "111");               -> [DATA.ADDR]:111
 * write_data("ADDR", "a=1,b=2");           -> [DATA.ADDR]:a=1,b=2
 * write_data("ADDR", "a=%d,b=%d", a, b);   -> [DATA.ADDR]:a=1,b=2
 */
void write_data(const char* path, const char* format, ...)
{
    if (carrot_ascii_protocol_config.comm == NULL) return;

    int len = 0;

    // 1. 拼装前缀
    if (path && path[0] != '\0')
    {
        len = snprintf(fmt_buf, sizeof(fmt_buf), "[DATA.%s]:", path);
    }
    else
    {
        len = snprintf(fmt_buf, sizeof(fmt_buf), "[DATA]:");
    }

    // 2. 拼装内容
    va_list args;
    va_start(args, format);
    len += vsnprintf(fmt_buf + len, sizeof(fmt_buf) - len, format, args);
    va_end(args);

    if (len <= 0) return;

    // 3. 补齐换行符
    if (len > sizeof(fmt_buf) - 3) len = sizeof(fmt_buf) - 3;
    fmt_buf[len++] = '\r';
    fmt_buf[len++] = '\n';
    fmt_buf[len] = '\0';

    carrot_ascii_protocol_config.comm->write(carrot_ascii_protocol_config.comm->handle, (uint8_t*)fmt_buf, len);
}

/**
 * @brief 发送寄存器数据
 * 格式: [REG.0x10]:255
 */
void reply_reg(uint32_t addr, uint32_t val)
{
    if (carrot_ascii_protocol_config.comm == NULL) return;

    int len = snprintf(fmt_buf, sizeof(fmt_buf), "[REG.0x%X]:0x%X\r\n", addr, val);
    
    carrot_ascii_protocol_config.comm->write(carrot_ascii_protocol_config.comm->handle, (uint8_t*)fmt_buf, len);
}

/**
 * @brief 发送位域数据
 * 格式: [REG.0x10.b3_0]:2
 */
void reply_bits(uint32_t addr, uint8_t start, uint8_t end, uint32_t val) {
    if (carrot_ascii_protocol_config.comm == NULL) return;

    int len = snprintf(fmt_buf, sizeof(fmt_buf), "[REG.0x%X.b%d_%d]:0x%X\r\n", addr, end, start, val);
    
    carrot_ascii_protocol_config.comm->write(carrot_ascii_protocol_config.comm->handle, (uint8_t*)fmt_buf, len);
}


//void write_data_internal(uint8_t* data, uint16_t size)
//{
//    if (carrot_ascii_protocol_config.comm == NULL)
//        return;
//
//    pkt.frame_start = CARROT_BINARY_PROTOCOL_FRAME_START;
//    pkt.protocol_id = CARROT_BINARY_PROTOCOL_ID_DATA_266;
//
//    pkt.control_flags = carrot_ascii_protocol_config.data_protocol.data_width << 11;
//    pkt.control_flags |= carrot_ascii_protocol_config.data_protocol.data_encoding << 10;
//    pkt.control_flags |= carrot_ascii_protocol_config.data_protocol.data_endian << 9;
//    pkt.control_flags |= carrot_ascii_protocol_config.data_protocol.data_interleaved << 8;
//    pkt.control_flags |= carrot_ascii_protocol_config.data_protocol.data_interleaved == CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_USED
//        ? carrot_ascii_protocol_config.data_protocol.data_interleaved_channel_mask >> 8
//        : CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_CHANNEL_MASK_NULL;
//
//    pkt.stream_id = carrot_ascii_protocol_config.data_protocol.data_interleaved == CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_USED
//        ? (carrot_ascii_protocol_config.data_protocol.data_interleaved_channel_mask & 0xFF)
//        : carrot_ascii_protocol_config.data_protocol.data_channel;
//
//    pkt.payload_len = size;
//    memcpy(pkt.payload, data, sizeof(uint8_t) * size);
//    if (size < 256)
//        memset(pkt.payload + sizeof(uint8_t) * size, 0, sizeof(uint8_t) * (CARROT_BINARY_PROTOCOL_MAX_PAYLOAD_SIZE_DATA_266 - size));
//    pkt.crc = 0xcccc;
//    pkt.frame_end = CARROT_BINARY_PROTOCOL_FRAME_END;
//
//    carrot_ascii_protocol_config.comm->write(carrot_ascii_protocol_config.comm->handle, (uint8_t*)&pkt, sizeof(pkt));
//}
//
//void write_data(uint8_t* data, uint16_t size)
//{
//    if (carrot_ascii_protocol_config.comm == NULL || data == NULL || size == 0)
//        return;
//
//    uint8_t* pdata = data;
//    uint16_t remain_size = size;
//    const uint16_t max_payload_size = CARROT_BINARY_PROTOCOL_MAX_PAYLOAD_SIZE_DATA_266;
//
//    while (remain_size > 0)
//    {
//        uint16_t chunk_size = (remain_size > max_payload_size) ? max_payload_size : remain_size;
//
//        write_data_internal(pdata, chunk_size);
//
//        pdata += chunk_size;
//        remain_size -= chunk_size;
//    }
//}