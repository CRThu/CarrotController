/****************************
 * CEVENT
 * CARROT HU
 * 2025.05.22
 *****************************/
#pragma once
#ifndef _CEVENT_H_
#define _CEVENT_H_

#ifdef __cplusplus
extern "C"
{
    #endif
    #define CEVENT_VERSION "1.0.0"

    #include <stdint.h>
    #include <string.h>

    /*
        EVENT IMPL:
            volatile uint32_t cnt = 0;
            void tim_callback(TIM_HandleTypeDef* htim)
            {
                cnt++;
                if (cevent_raise(&global_event, 0))
                    bsp_uart_printf("QUENE FULL\r\n");
                if (cnt % 10 == 0)
                {
                    if (cevent_raise(&global_event, 1))
                        bsp_uart_printf("QUENE FULL\r\n");
                }
            }

            void send_event()
            {
                bsp_uart_printf("%ld\r\n", cnt);
            }
            void send_hello()
            {
                bsp_uart_printf("hello\r\n");
            }

        INITIAL:
            cevent_init(&global_event);
            cevent_register(&global_event, 0, send_event);
            cevent_register(&global_event, 1, send_hello);
        USAGE:
            while(1)
            {
                cevent_run(&global_event);
            }
     */

    #define CEVENT_MAX_EVENT_NUM            16
    #define CEVNET_MAX_EVENT_HANDLER_NUM    16
    #define CEVNET_QUENE_SIZE               4

    #define CEVENT_IDLE                     do{} while(0)

    #define CEVENT_NO_ERR                   0
    #define CEVENT_ERR_QUENE_FULL           -1
    #define CEVENT_ERR_ID_OUT_OF_RANGE      -2
    #define CEVENT_ERR_HANDLER_FULL         -3

    typedef uint8_t cevent_size_t;
    typedef void (*cevent_handler_t)();
    typedef int8_t cevent_status_t;
    typedef struct {
        cevent_handler_t handler[CEVENT_MAX_EVENT_NUM][CEVNET_MAX_EVENT_HANDLER_NUM];
        cevent_size_t quene[CEVNET_QUENE_SIZE];
        cevent_size_t quene_head;
        cevent_size_t quene_tail;
    }cevent_t;

    extern cevent_t global_event;

    void cevent_init(cevent_t* e);
    cevent_status_t cevent_register(cevent_t* e, cevent_size_t eventid, cevent_handler_t handler);
    cevent_status_t cevent_raise(cevent_t* e, cevent_size_t eventid);
    void cevent_run(cevent_t* e);
    void cevent_runloop(cevent_t* e);

    #ifdef __cplusplus
}
#endif

#endif // _UART_COMM_H_
