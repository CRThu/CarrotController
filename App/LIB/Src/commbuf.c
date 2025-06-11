#include "commbuf.h"
#include <string.h>
#include <stdlib.h>

// 创建环形缓冲区
commbuf_t* commbuf_create(commbuf_size_t size)
{
    commbuf_t* cb = (commbuf_t*)malloc(sizeof(commbuf_t));
    if (!cb) return NULL;

    cb->buf = (uint8_t*)malloc(size);
    if (!cb->buf)
    {
        free(cb);
        return NULL;
    }

    cb->size = size;
    cb->head = 0;
    cb->tail = 0;
    return cb;
}

// 释放环形缓冲区
void commbuf_free(commbuf_t* buf)
{
    if (buf)
    {
        if (buf->buf) free(buf->buf);
        free(buf);
    }
}

// 获取缓冲区数据长度
commbuf_size_t commbuf_get_len(commbuf_t* buf)
{
    if (!buf) return 0;

    COMMBUF_ENTER_CRITICAL();
    commbuf_size_t len = (buf->head >= buf->tail) ?
        (buf->head - buf->tail) :
        (buf->size - buf->tail + buf->head);
    COMMBUF_EXIT_CRITICAL();
    return len;
}

// 获取缓冲区剩余空间
commbuf_size_t commbuf_get_space(commbuf_t* buf)
{
    if (!buf) return 0;

    return buf->size - 1 - commbuf_get_len(buf);  // 保留一个字节区分空/满状态
}

// 清空缓冲区
void commbuf_flush(commbuf_t* buf)
{
    if (!buf) return;

    COMMBUF_ENTER_CRITICAL();
    buf->head = 0;
    buf->tail = 0;
    COMMBUF_EXIT_CRITICAL();
}

// 从缓冲区读取数据
commbuf_size_t commbuf_read(commbuf_t* buf, uint8_t* dest, commbuf_size_t destsize)
{
    if (!buf || !dest || destsize == 0) return 0;

    COMMBUF_ENTER_CRITICAL();

    commbuf_size_t available = (buf->head >= buf->tail) ?
        (buf->head - buf->tail) :
        (buf->size - buf->tail + buf->head);
    commbuf_size_t to_read = (destsize < available) ? destsize : available;

    if (to_read > 0)
    {
        // 计算连续空间
        commbuf_size_t first_chunk = buf->size - buf->tail;
        if (to_read <= first_chunk)
        {
            memcpy(dest, &buf->buf[buf->tail], to_read);
            buf->tail += to_read;
        }
        else
        {
            memcpy(dest, &buf->buf[buf->tail], first_chunk);
            memcpy(dest + first_chunk, &buf->buf[0], to_read - first_chunk);
            buf->tail = to_read - first_chunk;
        }

        if (buf->tail >= buf->size)
        {
            buf->tail -= buf->size;
        }
    }

    COMMBUF_EXIT_CRITICAL();
    return to_read;
}

// 向缓冲区写入数据
commbuf_size_t commbuf_write(commbuf_t* buf, uint8_t* src, commbuf_size_t srcsize)
{
    if (!buf || !src || srcsize == 0) return 0;

    COMMBUF_ENTER_CRITICAL();

    commbuf_size_t data_len = (buf->head >= buf->tail) ?
        (buf->head - buf->tail) :
        (buf->size - buf->tail + buf->head);
    commbuf_size_t free_space = buf->size = data_len - 1;
    commbuf_size_t to_write = (srcsize < free_space) ? srcsize : free_space;

    if (to_write > 0)
    {
        // 计算连续空间
        commbuf_size_t first_chunk = buf->size - buf->head;
        if (to_write <= first_chunk)
        {
            memcpy(&buf->buf[buf->head], src, to_write);
            buf->head += to_write;
        }
        else
        {
            memcpy(&buf->buf[buf->head], src, first_chunk);
            memcpy(&buf->buf[0], src + first_chunk, to_write - first_chunk);
            buf->head = to_write - first_chunk;
        }

        if (buf->head >= buf->size)
        {
            buf->head -= buf->size;
        }
    }

    COMMBUF_EXIT_CRITICAL();
    return to_write;
}

// 查看缓冲区数据（不移动指针）
commbuf_error_t commbuf_peek(commbuf_t* buf, commbuf_size_t offset, uint8_t* val)
{
    if (!buf || !val)
        return COMMBUF_ERR_NULL;

    COMMBUF_ENTER_CRITICAL();

    commbuf_size_t len = (buf->head >= buf->tail) ?
        (buf->head - buf->tail) :
        (buf->size - buf->tail + buf->head);
    commbuf_error_t ret = COMMBUF_ERR_OUT_OF_RANGE;

    if (offset < len)
    {
        commbuf_size_t idx = buf->tail + offset;

        if (idx >= buf->size)
        {
            idx -= buf->size;
        }
        *val = buf->buf[idx];
        ret = COMMBUF_NO_ERR;
    }

    COMMBUF_EXIT_CRITICAL();
    return ret;
}