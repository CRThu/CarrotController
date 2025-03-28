/****************************
 * IO UTILS
 * CRTHu
 * 2025.01.22
 *****************************/
#pragma once
#ifndef _IO_UTILS_H_
#define _IO_UTILS_H_

#ifdef __cplusplus
extern "C"
{
#endif
    #define IO_UTILS_VERSION "1.0.0"

    /*
        USAGE:

        INITIAL:

     */


    /* from stm32h5xx.h
        #define SET_BIT(REG, BIT)     ((REG) |= (BIT))
        #define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
        #define READ_BIT(REG, BIT)    ((REG) & (BIT))
        #define CLEAR_REG(REG)        ((REG) = (0x0))
        #define WRITE_REG(REG, VAL)   ((REG) = (VAL))
        #define READ_REG(REG)         ((REG))
        #define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))
        #define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))
    */
    
    /*--------------------------- 位域操作宏 ------------------------------*/
    /* 生成连续位掩码 */
    #define BITSMASK(START, END) \
        ((((1U) << ((END) - (START) + 1)) - 1) << (START))
        /* @示例：生成3-5位掩码(0x38)
        *  BITSMASK(3,5) = 0b00111000 = 0x38 */

    /* 提取位域值 */
    #define BITS_GET(REG, START, END) \
        (((REG) & BITSMASK((START), (END))) >> (START))
        /* @示例：获取TIM2_CR1的3-5位
        *  uint8_t bits = BITS_GET(TIM2->CR1, 3,5) */

    /* 设置位域值 */
    #define BITS_SET(REG, START, END, DATA) \
        ((REG) & (~BITSMASK((START), (END))) | (((DATA) << (START)) & BITSMASK((START), (END))))
        /* @示例：设置ADC_CFGR的5-7位为0b101
        *  ADC1->CFGR = BITS_SET(ADC1->CFGR,5,7,5) */

    /*--------------------------- GPIO位操作核心宏 --------------------------*/
    /* 原子化设置/清除位 */
    #define WRITE_RS_REG(REG, DATA, MASK) \
        WRITE_REG((REG), ((DATA) & (MASK)) | ((~(DATA) & (MASK)) << 16U))
        /* @示例：同时设置PB0/PB1，清除PB2
        *  WRITE_RS_REG(GPIOB->BSRR, 0x03, 0x07) */

    /*--------------------------- 总线操作宏 ------------------------------*/
    /* 写入带掩码总线 */
    #define DB_WRITE_MASK(GPIOx, DATA, MASK) \
        WRITE_RS_REG((GPIOx)->BSRR, (DATA), (MASK))
        /* @示例：写入0xA5到PB0-7
        *  DB_WRITE_MASK(GPIOB, 0xA5, 0x00FF) */

    /* 读取带掩码总线 */
    #define DB_READ_MASK(GPIOx, MASK) \
        ((MASK) == 0 ? 0 : (uint32_t)(READ_REG((GPIOx)->IDR) & (MASK) >> __CTZ((MASK))))
        /* @示例：读取PC端口16位数据
        *  uint16_t val = DB_READ(GPIOC) */

    /* 写入完整数据总线 */
    #define DB_WRITE(GPIOx, DATA) \
        (WRITE_REG((GPIOx)->ODR), (DATA))
        /* @示例：写入0xA5到PB端口
        *  DB_WRITE(GPIOB, 0xA5) */

    /* 读取完整数据总线 */
    #define DB_READ(GPIOx) \
        (uint32_t)(READ_REG((GPIOx)->IDR))
        /* @示例：读取PC端口16位数据
        *  uint16_t val = DB_READ(GPIOC) */

    /*--------------------------- 单引脚操作宏 -----------------------------*/
    /* 设置单个引脚电平 */
    #define IO_WRITE(GPIOx, PINMASK, STATE) \
        WRITE_REG((GPIOx)->BSRR, ((STATE) ? (PINMASK) : (PINMASK) << 16U))
        /* @示例：设置PA5为高电平
        *  IO_WRITE(GPIOA, GPIO_PIN_5, 1) */
     
    /* 读取单个引脚状态 */
    #define IO_READ(GPIOx, PINMASK) \
        ((READ_REG((GPIOx)->IDR) & (PINMASK)) != 0 ? 1 : 0)
        /* @示例：读取PA6输入状态
        *  uint8_t state = IO_READ(GPIOA, GPIO_PIN_6) */

    
    /*------------------------- 单引脚方向控制扩展宏 -------------------------*/
    /* 单GPIO设置模式 0: Input, 1: Output */
    #define IO_SET_MODE(GPIOx, PIN, MODE) \
        MODIFY_REG((GPIOx)->MODER, (0x3UL << (2 * POSITION_VAL(PIN))), ((MODE) << (2 * POSITION_VAL(PIN))))
        /* @示例：设置PC13为输入
        *  IO_SET_MODE(GPIOC, GPIO_PIN_13, IN) */
    /* 单GPIO设置为输入模式 */
    #define IO_IN(GPIOx, PIN) \
        IO_SET_MODE((GPIOx), (PIN), 0)
        /* @示例：设置PC13为输入
        *  IO_IN(GPIOC, GPIO_PIN_13) */
     /* 单GPIO设置为输出模式 */
    #define IO_OUT(GPIOx, PIN) \
        IO_SET_MODE((GPIOx), (PIN), 1)
        /* @示例：设置PB3为输出
        *  IO_OUT(GPIOB, GPIO_PIN_3) */

    /*------------------------- 总线方向控制扩展宏 -------------------------*/
    
    /* 完整数据总线设置模式 0: Input, 1: Output */
    #define DB_SET_MODE(GPIOx, MODE) \
        (WRITE_REG((GPIOx)->MODER), (MODE == 0) ? 0x00000000UL : 0x55555555UL)
        /* @示例：设置PC端口为输入
        *  DB_SET_MODE(GPIOC, IN) */
    /* 完整数据总线设置为输入模式 */
    #define DB_IN(GPIOx) \
        DB_SET_MODE((GPIOx), 0)
        /* @示例：设置PC13为输入
        *  DB_IN(GPIOC) */
     /* 完整数据总线设置为输出模式 */
    #define DB_OUT(GPIOx) \
        DB_SET_MODE((GPIOx), 1)
        /* @示例：设置PB3为输出
        *  DB_OUT(GPIOB) */


#ifdef __cplusplus
}
#endif

#endif // _IO_UTILS_H_
