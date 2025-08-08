#ifndef _CARROT_BINARY_PROTOCOL_H
#define _CARROT_BINARY_PROTOCOL_H

#ifdef __cplusplus
extern "C"
{
    #endif
    #include <inttypes.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdarg.h>

    #define CARROT_BINARY_PROTOCOL_VERSION "1.1.0"


    #define CARROT_PROTOCOL_CRC 0

    #define CARROT_BINARY_PROTOCOL_FRAME_START 		0x3C
    #define CARROT_BINARY_PROTOCOL_FRAME_END 		0x3E
    #define CARROT_BINARY_PROTOCOL_ID_MSG_64 		0x31
    #define CARROT_BINARY_PROTOCOL_ID_MSG_256 		0x32
    #define CARROT_BINARY_PROTOCOL_ID_MSG_2048      0x33
    #define CARROT_BINARY_PROTOCOL_ID_DATA_74       0x41
    #define CARROT_BINARY_PROTOCOL_ID_DATA_266 		0x42
    #define CARROT_BINARY_PROTOCOL_ID_DATA_2058		0x43

    #define CARROT_BINARY_PROTOCOL_MAX_PAYLOAD_SIZE_DATA_74     64
    #define CARROT_BINARY_PROTOCOL_MAX_PAYLOAD_SIZE_DATA_266    256
    #define CARROT_BINARY_PROTOCOL_MAX_PAYLOAD_SIZE_DATA_2058   2048
    
    #define CARROT_BINARY_PROTOCOL_DATA_WIDTH_32B               0x00
    #define CARROT_BINARY_PROTOCOL_DATA_WIDTH_16B               0x01
    #define CARROT_BINARY_PROTOCOL_DATA_WIDTH_8B                0x02

    #define CARROT_BINARY_PROTOCOL_DATA_ENCODING_OFFSET         0x00
    #define CARROT_BINARY_PROTOCOL_DATA_ENCODING_COMP           0x01

    #define CARROT_BINARY_PROTOCOL_DATA_ENDIAN_LITTLE           0x00
    #define CARROT_BINARY_PROTOCOL_DATA_ENDIAN_BIG              0x01

    #define CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_NOT_USED    0x00
    #define CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_USED        0x01

    #define CARROT_BINARY_PROTOCOL_CRC_NOT_USED                 0x00
    #define CARROT_BINARY_PROTOCOL_CRC_USED                     0x01

    #define CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_CHANNEL_MASK_NULL   (0x0000)
    #define CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_CHANNEL_MASK_2CH    (0x0003)
    #define CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_CHANNEL_MASK_4CH    (0x000F)
    #define CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_CHANNEL_MASK_8CH    (0x00FF)
    #define CARROT_BINARY_PROTOCOL_DATA_INTERLEAVED_CHANNEL_MASK_16CH   (0xFFFF)

    #if CARROT_PROTOCOL_CRC == 0
    #define CRC_VERIFY_FUNC(ADDR, LEN) (0x0000)
    #elif CARROT_PROTOCOL_CRC == 1
    // HARD CRC CALC
    // STM32 F1/F4/L1 DEFAULT: CRC32
    // Uses CRC-32 (Ethernet) polynomial: 0x4C11DB7
    // X32 + X26 + X23 + X22 + X16 + X12 + X11 + X10 + X8 + X7 + X5 + X4 + X2 + X + 1
    // Single input/output 32-bit data register
    // reset to 0xFFFF FFFF
    // use whole packet with crc16=0x0000 to calc crc32 and get low 16bit
    #include "crc.h"
    #define CRC_PROTOCOL_INSTANCE hcrc
    #define CRC_VERIFY_FUNC(ADDR, LEN) (uint16_t) HAL_CRC_Calculate(&CRC_PROTOCOL_INSTANCE, (uint32_t *)(ADDR), (uint32_t)((LEN) / 4))
    #endif


    typedef struct {
        uint8_t msg_packet_id;
        uint8_t data_packet_id;
        uint8_t data_width;
        uint8_t data_encoding;
        uint8_t data_endian;
        uint8_t data_channel;
        uint8_t data_interleaved;
        uint16_t data_interleaved_channel_mask;
        uint8_t using_crc;
    } carrot_binary_protocol_config_t;


    // KEIL ARMCC and GNUC
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
    #ifndef __PROTOCOL_PACKED__
    #define __PROTOCOL_PACKED__ __attribute__((packed))
    #endif
    #elif defined(__GNUC__) && !defined(__CC_ARM) /* GNU Compiler */
    #ifndef __PROTOCOL_PACKED__
    #define __PROTOCOL_PACKED__ __attribute__((__packed__))
    #endif /* __PROTOCOL_PACKED__ */
    #else
    #ifndef __PROTOCOL_PACKED__
    #define __PROTOCOL_PACKED__
    #endif /* __PROTOCOL_PACKED__ */
    #endif /* __GNUC__ */

    // ALIGN START
    #if defined(_MSC_VER)
    #pragma pack(push, 1)
    #endif

    #define CARROT_BINARY_PACKET_GEN(len)       \
    typedef struct __PROTOCOL_PACKED__      \
    {                                       \
        uint8_t frame_start;                \
        uint8_t protocol_id;                \
        uint16_t control_flags;             \
        uint8_t stream_id;                  \
        uint16_t payload_len;               \
        uint8_t payload[len - 10];          \
        uint16_t crc;                       \
        uint8_t frame_end;                  \
    } carrot_binary_packet_##len;

    CARROT_BINARY_PACKET_GEN(256);
    CARROT_BINARY_PACKET_GEN(266);

    // ALIGN END
    #if defined(_MSC_VER)
    #pragma pack(pop)
    #endif

    #ifdef __cplusplus
}
#endif

#endif /* _CARROT_BINARY_PROTOCOL_H */
