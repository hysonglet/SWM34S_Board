
#ifndef _SYNWIT_BOARD_H
#define _SYNWIT_BOARD_H

#include "system.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef F_CPU
#define F_CPU       150000000UL
#endif

void delay_ms(uint32_t ms);

void led_init(void);
void led_turn(void);
void led_on(void);
void led_off(void);
void key_init(void);
bool key_is_push(void);
void uart0_init(void);
void sdram_init(void);
void rgb_lcd_init(uint32_t *lcd_buff, uint16_t width, uint16_t height);

#ifdef __cplusplus
}
#endif

#endif
