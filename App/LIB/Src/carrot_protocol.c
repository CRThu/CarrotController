#include "carrot_protocol.h"

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
    protocol_write_msg(c, "<data>");
    //protocol_write_msg(c, "<name>%s</name>", "databuf");
    //protocol_write_msg(c, "<desc>%s</desc>", "NULL");
    protocol_write_msg(c, "<format>binary</format>");
    protocol_write_msg(c, "<len>%lu</len>", len);
    protocol_write_msg(c, "<word>");
    //protocol_write_msg(c, "<interleaved>true</interleaved>");
    //protocol_write_msg(c, "<channels>");
    //protocol_write_msg(c, "<channel>%d</channel>",0);
    //protocol_write_msg(c, "<channel>%d</channel>",1);
    //protocol_write_msg(c, "<channel>%d</channel>",2);
    //protocol_write_msg(c, "<channel>%d</channel>",3);
    //protocol_write_msg(c, "</channels>");
    protocol_write_msg(c, "<bits>%d</bits>", 32);
    protocol_write_msg(c, "</word>");
    protocol_write_msg(c, "<bin>");
    c->write(c->comm, data, len);
    protocol_write_msg(c, "</bin>");
    protocol_write_msg(c, "</data>");
    protocol_write_msg(c, "\r\n");
}