
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
void lcd_pixel_set_565(uint32_t lcd_buff_addr, uint16_t x, uint16_t y, uint16_t pix);

#define LCD_WIDTH               480
#define LCD_HEIGHT              272
#define LCD_BUFF_ADDR           SDRAMM_BASE   
#define SDRAM_MEM_SIZE          (8*1024*1024)   

#ifdef __cplusplus
}
#endif

#endif
