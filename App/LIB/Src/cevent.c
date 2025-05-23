#include "cevent.h"

cevent_t global_event;

void cevent_init(cevent_t* e)
{
    e->quene_head = 0;
    e->quene_tail = 0;
}

cevent_status_t cevent_register(cevent_t* e, cevent_size_t eventid, cevent_handler_t handler)
{
    if (eventid >= CEVENT_MAX_EVENT_NUM)
        return CEVENT_ERR_ID_OUT_OF_RANGE;
    for (int handlerid = 0; handlerid < CEVNET_MAX_EVENT_HANDLER_NUM; handlerid++)
    {
        if (e->handler[eventid][handlerid] == NULL)
        {
            e->handler[eventid][handlerid] = handler;
            return CEVENT_NO_ERR;
        }
    }
    return CEVENT_ERR_HANDLER_FULL;
}

cevent_status_t cevent_raise(cevent_t* e, cevent_size_t eventid)
{
    if (eventid >= CEVENT_MAX_EVENT_NUM)
        return CEVENT_ERR_ID_OUT_OF_RANGE;

    CEVENT_CRITICAL_BEGIN();
    cevent_size_t curr_tail = e->quene_tail;
    cevent_size_t next_tail = (curr_tail + 1) % CEVNET_QUENE_SIZE;
    if (next_tail == e->quene_head)
    {
        CEVENT_CRITICAL_END();
        return CEVENT_ERR_QUENE_FULL; // FULL
    }
    e->quene[e->quene_tail] = eventid;
    e->quene_tail = next_tail;
    CEVENT_CRITICAL_END();
    return CEVENT_NO_ERR;
}

void cevent_run(cevent_t* e)
{
    cevent_size_t eventid;
    CEVENT_CRITICAL_BEGIN();
    cevent_size_t curr_head = e->quene_head;
    if (curr_head == e->quene_tail)
    {
        CEVENT_CRITICAL_END();
        return;
    }

    eventid = e->quene[curr_head];
    e->quene_head = (curr_head + 1) % CEVNET_QUENE_SIZE;
    CEVENT_CRITICAL_END();

    int handlerid = 0;
    while (handlerid < CEVNET_MAX_EVENT_HANDLER_NUM && e->handler[eventid][handlerid] != NULL)
    {
        e->handler[eventid][handlerid]();
        handlerid++;
    }
}

void cevent_runloop(cevent_t* e)
{
    while (1)
    {
        cevent_run(e);
        CEVENT_IDLE();
    }
}