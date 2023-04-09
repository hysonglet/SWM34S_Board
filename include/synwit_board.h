
#ifndef _SYNWIT_BOARD_H
#define _SYNWIT_BOARD_H

#include "system.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef F_CPU
#define F_CPU       150000000UL
#endif


#define LED_PORT    GPIOA
#define LED_PIN     PIN15
#define KEY_PORT    GPIOA
#define KEY_PIN		PIN14
#define KEY_PUSH_STATUE 0

#define LCD_BL_PORT		GPIOB
#define LCD_BL_PIN      PIN13

#define SPI0_CS_PORT	GPIOM
#define SPI0_CS_PIN		PIN3
#define SPI0_SCLK_PORT	PORTM
#define SPI0_SCLK_PIN	PIN2
#define SPI0_SCLK_FUN   PORTM_PIN2_SPI0_SCLK
#define SPI0_MISO_PORT	PORTM
#define SPI0_MISO_PIN	PIN4
#define SPI0_MISO_FUN   PORTM_PIN4_SPI0_MISO
#define SPI0_MOSI_PORT	PORTM
#define SPI0_MOSI_PIN	PIN5
#define SPI0_MOSI_FUN   PORTM_PIN5_SPI0_MOSI

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
void rtc_init(uint16_t year, uint8_t month, uint8_t date, 
				uint8_t hour, uint8_t minute, uint8_t second,
				bool second_ie, bool minute_en);
void rtc_alarm_init(uint8_t alarm_day_mask, uint8_t hour, uint8_t minute, 
					uint8_t second, bool alarm_ie);
void rtc_datetime_get(RTC_DateTime * dateTime);
void spi0_init(void);
void spi0_cs_en(bool en);
void spi0_write_bytes(uint8_t *buff, size_t len);
size_t spi0_read_bytes(uint8_t *buff, size_t len, uint32_t timeout_ms);
#define LCD_WIDTH               480
#define LCD_HEIGHT              272
#define LCD_BUFF_ADDR           SDRAMM_BASE   
#define SDRAM_MEM_SIZE          (8*1024*1024)   



bool sdcard_init(int freq);
bool sdcard_disk_read(uint8_t *buff, size_t cnt, size_t sector);
bool sdcard_disk_write(uint8_t *buff, size_t cnt, size_t sector);
bool sdcard_is_initialized(void);

#ifdef __cplusplus
}
#endif

#endif
