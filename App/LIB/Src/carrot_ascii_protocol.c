#include "carrot_ascii_protocol.h"
#include "carrot_binary_protocol.h"

void protocol_write_msg(comm_func_t* c, const char* format, ...)
{
    char fmt_buf[256];
    uint16_t fmt_buf_len;
    va_list args;

    va_start(args, format);
    fmt_buf_len = vsnprintf(((char*)&fmt_buf), sizeof(fmt_buf), (char*)format, args);
    va_end(args);

    c->write(c->comm, (uint8_t*)fmt_buf, fmt_buf_len);
}

void protocol_write_data(comm_func_t* c, uint8_t channel, uint8_t* data, uint16_t len)
{
    carrot_binary_packet_266 pkt;
    carrot_binary_protocol_266_init(&pkt, channel, data, len);
    c->write(c->comm, (uint8_t*)&pkt, sizeof(pkt));
}