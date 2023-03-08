

#include "synwit_board.h"
#include <SWM341.h>

#if (F_CPU == 150000000)
#define DELAY_MS_CNT   0xfffff1U
#else
#define DELAY_MS_CNT   0xfffff1UL
#warning "The main frequency of the mcu is temporarily not adapted"
#endif

void delay_ms(uint32_t ms)
{
    volatile uint32_t cnt = DELAY_MS_CNT;
    while(cnt--);
}

#define LED_PORT    GPIOA
#define LED_PIN     PIN15

void led_init(void)
{
    GPIO_Init(LED_PORT, LED_PIN, 1, 1, 0, 0);
}

void led_turn(void)
{
    GPIO_InvBit(LED_PORT, LED_PIN);
}

void led_on(void)
{
    GPIO_SetBit(LED_PORT, LED_PIN);
}

void led_off(void)
{
    GPIO_ClrBit(LED_PORT, LED_PIN);
}