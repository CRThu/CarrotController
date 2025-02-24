#include "bsp_inc.h"


gpio_config_status_t gpio_init(io_t* gpio)
{
    if (!gpio)
    {
        return -1;
    }

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    /* GPIO Ports Clock Enable */
    if (gpio->port == GPIO_PORT(A))  GPIO_CLOCK(A);
    if (gpio->port == GPIO_PORT(B))  GPIO_CLOCK(B);
    if (gpio->port == GPIO_PORT(C))  GPIO_CLOCK(C);
    if (gpio->port == GPIO_PORT(D))  GPIO_CLOCK(D);
    if (gpio->port == GPIO_PORT(E))  GPIO_CLOCK(E);
    if (gpio->port == GPIO_PORT(F))  GPIO_CLOCK(F);
    if (gpio->port == GPIO_PORT(G))  GPIO_CLOCK(G);
    if (gpio->port == GPIO_PORT(H))  GPIO_CLOCK(H);
    if (gpio->port == GPIO_PORT(I))  GPIO_CLOCK(I);


    switch (gpio->func)
    {
    case BSP_IO_FUNC_NONE:
        return -2;
        break;
    case BSP_IO_FUNC_OUT:
    case BSP_IO_SWITCH_SEL:
        /*Configure GPIO pin Output Level */
        GPIO_WRITE(gpio, gpio->state);

        /*Configure GPIO pin */
        GPIO_InitStruct.Pin = gpio->pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(gpio->port, &GPIO_InitStruct);

        return GPIO_CONFIG_STATUS_NO_ERR;
        break;
    case BSP_IO_FUNC_IN:
        /*Configure GPIO pin */
        GPIO_InitStruct.Pin = gpio->pin;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(gpio->port, &GPIO_InitStruct);
        return GPIO_CONFIG_STATUS_NO_ERR;
        break;
    default:
        return -3;
        break;
    }
}
