#include "cdelay.h"

void cdelay_init()
{
    if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk))
    {
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    }

    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void cdelay_us(uint32_t us)
{
    uint32_t ticks = us * (SystemCoreClock / 1000000.0);
    uint32_t start = SysTick->VAL;
    uint32_t load = SysTick->LOAD;
    uint32_t elapsed;

    // 确保最小延时1个周期
    ticks = ticks < 1 ? 1 : ticks;

    do {
        uint32_t current = SysTick->VAL;
        // 处理计数器翻转
        elapsed = (start < current) ?
            (start + (load - current)) :
            (start - current);
    } while (elapsed < ticks);
}

void cdelay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}