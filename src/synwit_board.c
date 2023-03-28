

#include "synwit_board.h"
#include <SWM341.h>
#include <stdio.h>
#include <stdarg.h>

#if (F_CPU == 150000000)
#define DELAY_MS_CNT   0x4000U
#else
#define DELAY_MS_CNT   0x4189UL
#warning "The main frequency of the mcu is temporarily not adapted"
#endif

void delay_ms(uint32_t ms)
{
	while (ms--){
    	volatile uint32_t cnt = DELAY_MS_CNT;
    	while(cnt--);
	}

}
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

void key_init(void)
{
	GPIO_Init(KEY_PORT, KEY_PIN, 0, 1, 0, 0);
}

bool key_is_push(void)
{
	return GPIO_GetBit(KEY_PORT, KEY_PIN) == KEY_PUSH_STATUE;
}

void uart0_init(void)
{
    UART_InitStructure UART_initStruct;
	
	PORT_Init(PORTM, PIN0, PORTM_PIN0_UART0_RX, 1);	
	PORT_Init(PORTM, PIN1, PORTM_PIN1_UART0_TX, 0);	
 	
 	UART_initStruct.Baudrate = 115200;
	UART_initStruct.DataBits = UART_DATA_8BIT;
	UART_initStruct.Parity = UART_PARITY_NONE;
	UART_initStruct.StopBits = UART_STOP_1BIT;
	UART_initStruct.RXThreshold = 3;
	UART_initStruct.RXThresholdIEn = 0;
	UART_initStruct.TXThreshold = 3;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutTime = 10;
	UART_initStruct.TimeoutIEn = 0;
 	UART_Init(UART0, &UART_initStruct);
	UART_Open(UART0);
}

inline int putchar(int ch)
{
	UART_WriteByte(UART0, ch);
	while(UART_IsTXBusy(UART0));
	return ch;
}

#ifdef __GNUC__
int _write(int fd, char *ptr, int len)
{ 
	for(int i = 0; i < len; i++){
		putchar(ptr[i]);
	}
	return len;
}
#else
int fputc(int ch, FILE *f)
{
	UART_WriteByte(UART0, ch);
	while(UART_IsTXBusy(UART0));
	return ch;
}
#endif

#if 0
void __wrap_printf(const char *format,...) 
{
    va_list args;
    int n;
    static char xmon_outbuf[1024];
    va_start(args, format);
    n = vsnprintf(xmon_outbuf, sizeof(xmon_outbuf), format, args);
    va_end(args);
    for(size_t i = 0; i < n; i++){
        putchar(xmon_outbuf[i]);
    }
}
#endif

void sdram_init(void)
{
#if 1
	PORT_Init(PORTM, PIN13, PORTM_PIN13_SDR_CLK, 0);
	PORT_Init(PORTM, PIN14, PORTM_PIN14_SDR_CKE, 0);
	PORT_Init(PORTB, PIN7,  PORTB_PIN7_SDR_WE,   0);
	PORT_Init(PORTB, PIN8,  PORTB_PIN8_SDR_CAS,  0);
	PORT_Init(PORTB, PIN9,  PORTB_PIN9_SDR_RAS,  0);
	PORT_Init(PORTB, PIN10, PORTB_PIN10_SDR_CS,  0);
	PORT_Init(PORTE, PIN15, PORTE_PIN15_SDR_BA0, 0);
	PORT_Init(PORTE, PIN14, PORTE_PIN14_SDR_BA1, 0);
	PORT_Init(PORTN, PIN14, PORTN_PIN14_SDR_A0,  0);
	PORT_Init(PORTN, PIN13, PORTN_PIN13_SDR_A1,  0);
	PORT_Init(PORTN, PIN12, PORTN_PIN12_SDR_A2,  0);
	PORT_Init(PORTN, PIN11, PORTN_PIN11_SDR_A3,  0);
	PORT_Init(PORTN, PIN10, PORTN_PIN10_SDR_A4,  0);
	PORT_Init(PORTN, PIN9,  PORTN_PIN9_SDR_A5,   0);
	PORT_Init(PORTN, PIN8,  PORTN_PIN8_SDR_A6,   0);
	PORT_Init(PORTN, PIN7,  PORTN_PIN7_SDR_A7,   0);
	PORT_Init(PORTN, PIN6,  PORTN_PIN6_SDR_A8,   0);
	PORT_Init(PORTN, PIN3,  PORTN_PIN3_SDR_A9,   0);
	PORT_Init(PORTN, PIN15, PORTN_PIN15_SDR_A10, 0);
	PORT_Init(PORTN, PIN2,  PORTN_PIN2_SDR_A11,  0);
	PORT_Init(PORTM, PIN15, PORTM_PIN15_SDR_A12, 0);
	PORT_Init(PORTE, PIN7,  PORTE_PIN7_SDR_D0,   1);
	PORT_Init(PORTE, PIN6,  PORTE_PIN6_SDR_D1,   1);
	PORT_Init(PORTE, PIN5,  PORTE_PIN5_SDR_D2,   1);
	PORT_Init(PORTE, PIN4,  PORTE_PIN4_SDR_D3,   1);
	PORT_Init(PORTE, PIN3,  PORTE_PIN3_SDR_D4,   1);
	PORT_Init(PORTE, PIN2,  PORTE_PIN2_SDR_D5,   1);
	PORT_Init(PORTE, PIN1,  PORTE_PIN1_SDR_D6,   1);
	PORT_Init(PORTE, PIN0,  PORTE_PIN0_SDR_D7,   1);
	PORT_Init(PORTE, PIN8,  PORTE_PIN8_SDR_D8,   1);
	PORT_Init(PORTE, PIN9,  PORTE_PIN9_SDR_D9,   1);
	PORT_Init(PORTE, PIN10, PORTE_PIN10_SDR_D10, 1);
	PORT_Init(PORTE, PIN11, PORTE_PIN11_SDR_D11, 1);
	PORT_Init(PORTE, PIN12, PORTE_PIN12_SDR_D12, 1);
	PORT_Init(PORTE, PIN13, PORTE_PIN13_SDR_D13, 1);
	PORT_Init(PORTC, PIN14, PORTC_PIN14_SDR_D14, 1);
	PORT_Init(PORTC, PIN15, PORTC_PIN15_SDR_D15, 1);
	PORT_Init(PORTB, PIN6,  PORTB_PIN6_SDR_LDQM, 0);
	PORT_Init(PORTM, PIN12, PORTM_PIN12_SDR_UDQM,0);
#else
	PORTB->FUNC0 &= ~0xFF000000;
	PORTB->FUNC0 |=  0x22000000;
	PORTB->FUNC1 &= ~0x00000FFF;
	PORTB->FUNC1 |=  0x00000444;
	
	PORTC->FUNC1 &= ~0xFF000000;
	PORTC->FUNC1 |=  0x11000000;
	PORTC->INEN  |= (1 << 15) | (1 << 14);
	
	PORTE->FUNC0 = 0x11111111;
	PORTE->FUNC1 = 0x11111111;
	PORTE->INEN  |= 0x3FFF;
	
	PORTM->FUNC1 &= ~0xFFFF0000;
	PORTM->FUNC1 |=  0x33220000;
	
	PORTN->FUNC0 &= ~0xFF00FF00;
	PORTN->FUNC0 |=  0x11002100;
	PORTN->FUNC1 = 0x11111111;
#endif
	SDRAM_InitStructure SDRAM_InitStruct;
	SDRAM_InitStruct.Size = SDRAM_SIZE_8MB;
	SDRAM_InitStruct.ClkDiv = SDRAM_CLKDIV_1;
	SDRAM_InitStruct.CASLatency = SDRAM_CASLATENCY_2;
	SDRAM_InitStruct.TimeTRP  = SDRAM_TRP_2;
	SDRAM_InitStruct.TimeTRCD = SDRAM_TRCD_2;
	SDRAM_InitStruct.TimeTRFC  = SDRAM_TRFC_7;
	SDRAM_Init(&SDRAM_InitStruct);
}


void rgb_lcd_init(uint32_t *lcd_buff, uint16_t width, uint16_t height)
{
	LCD_InitStructure LCD_initStruct;
	
	/* lcd背光 */
	GPIO_Init(LCD_BL_PORT, LCD_BL_PIN, 1, 1, 0, 0);		//屏幕背光
	GPIO_SetBit(LCD_BL_PORT, LCD_BL_PIN);
	
	delay_ms(50);

	// R- 5 bit : [ 3 ~ 7 ]
//	PORT_Init(PORTC, PIN4, PORTC_PIN4_LCD_R0, 0);
//	PORT_Init(PORTC, PIN5, PORTC_PIN5_LCD_R1, 0);
//	PORT_Init(PORTC, PIN8, PORTC_PIN8_LCD_R2, 0);
    PORT_Init(PORTC, PIN9, PORTC_PIN9_LCD_R3, 0);
    PORT_Init(PORTC, PIN10, PORTC_PIN10_LCD_R4, 0);
    PORT_Init(PORTC, PIN11, PORTC_PIN11_LCD_R5, 0);
    PORT_Init(PORTC, PIN12, PORTC_PIN12_LCD_R6, 0);
    PORT_Init(PORTC, PIN13, PORTC_PIN13_LCD_R7, 0);

    // G- 6 bit : [ 2 ~ 7 ]
//	PORT_Init(PORTA, PIN12, PORTA_PIN12_LCD_G0, 0);
//	PORT_Init(PORTA, PIN13, PORTA_PIN13_LCD_G1, 0);
    PORT_Init(PORTA, PIN14, PORTA_PIN14_LCD_G2, 0);
    PORT_Init(PORTA, PIN15, PORTA_PIN15_LCD_G3, 0);
    PORT_Init(PORTC, PIN0, PORTC_PIN0_LCD_G4, 0);
    PORT_Init(PORTC, PIN1, PORTC_PIN1_LCD_G5, 0);
    PORT_Init(PORTC, PIN2, PORTC_PIN2_LCD_G6, 0);
    PORT_Init(PORTC, PIN3, PORTC_PIN3_LCD_G7, 0);

    // B- 5 bit : [ 3 ~ 7 ]
//	PORT_Init(PORTB, PIN1, PORTB_PIN1_LCD_B0, 0);
//	PORT_Init(PORTB, PIN11, PORTB_PIN11_LCD_B1, 0);
//	PORT_Init(PORTB, PIN13, PORTB_PIN13_LCD_B2, 0);
    PORT_Init(PORTB, PIN15, PORTB_PIN15_LCD_B3, 0);
    PORT_Init(PORTA, PIN2, PORTA_PIN2_LCD_B4, 0);
    PORT_Init(PORTA, PIN9, PORTA_PIN9_LCD_B5, 0);
    PORT_Init(PORTA, PIN10, PORTA_PIN10_LCD_B6, 0);
    PORT_Init(PORTA, PIN11, PORTA_PIN11_LCD_B7, 0);

    // VS / HS / DE / CLK
    PORT_Init(PORTB, PIN2, PORTB_PIN2_LCD_VSYNC, 0);
    PORT_Init(PORTB, PIN3, PORTB_PIN3_LCD_HSYNC, 0);
    PORT_Init(PORTB, PIN4, PORTB_PIN4_LCD_DEN, 0);
    PORT_Init(PORTB, PIN5, PORTB_PIN5_LCD_DCLK, 0);
	
	/* JLT4303B-PSS */
	LCD_initStruct.ClkDiv = 10;
	LCD_initStruct.Format = LCD_FMT_RGB565;
	LCD_initStruct.HnPixel = width;
	LCD_initStruct.VnPixel = height;
	LCD_initStruct.Hfp = 5;
	LCD_initStruct.Hbp = 40;
	LCD_initStruct.Vfp = 8;
	LCD_initStruct.Vbp = 8;
	LCD_initStruct.HsyncWidth = 5; 
	LCD_initStruct.VsyncWidth = 5; 
	LCD_initStruct.DataSource = (uint32_t)lcd_buff;
	LCD_initStruct.Background = 0xFFFFFF;
	LCD_initStruct.SampleEdge = LCD_SAMPLE_FALL;
	LCD_initStruct.IntEOTEn = 0;

	LCD_Init(LCD, &LCD_initStruct);

	LCD_Start(LCD);
}

//开启该中断可以给用户提供接口,以测试最真实的帧率
void LCD_Handler(void)
{
    LCD_INTClr(LCD);
    LCD_Start(LCD);
	/*两次帧中断的间隔用时,即为帧率 */
	//uint32_t frame_ms = systick_over - systick_start;
}

inline void lcd_pixel_set_565(uint32_t lcd_buff_addr, uint16_t x, uint16_t y, uint16_t pix)
{
	uint16_t *lcd;
	lcd = (uint16_t *)lcd_buff_addr;
	lcd[LCD_WIDTH*y + x] = pix;
}

void rtc_init(uint16_t year, uint8_t month, uint8_t date, 
				uint8_t hour, uint8_t minute, uint8_t second,
				bool second_ie, bool minute_en)
{
	RTC_InitStructure RTC_initStruct;
	RTC_initStruct.clksrc = RTC_CLKSRC_LRC32K;
	RTC_initStruct.Year = year;
	RTC_initStruct.Month = month;
	RTC_initStruct.Date = date;
	RTC_initStruct.Hour = hour;
	RTC_initStruct.Minute = minute;
	RTC_initStruct.Second = second;
	RTC_initStruct.SecondIEn = (uint8_t)second_ie;
	RTC_initStruct.MinuteIEn = (uint8_t)minute_en;
	RTC_Stop(RTC);
	RTC_Init(RTC, &RTC_initStruct);
	RTC_Start(RTC);
}

void rtc_alarm_init(uint8_t alarm_day_mask, uint8_t hour, uint8_t minute, 
					uint8_t second, bool alarm_ie)
{
	RTC_AlarmStructure alarmStruct;
	alarmStruct.Days = alarm_day_mask;
	alarmStruct.Hour = hour;
	alarmStruct.Minute = minute;
	alarmStruct.Second = second;
	alarmStruct.AlarmIEn = (uint8_t)alarm_ie;
	
	RTC_AlarmSetup(RTC, &alarmStruct);
}

void rtc_datetime_get(RTC_DateTime * dateTime)
{
	RTC_GetDateTime(RTC, dateTime);
}

void spi0_init(void)
{
	GPIO_Init(SPI0_CS_PORT, SPI0_CS_PIN, 1, 0, 0, 0);
	spi0_cs_en(false);

	PORT_Init(SPI0_SCLK_PORT, SPI0_SCLK_PIN, SPI0_SCLK_FUN, 0);
	PORT_Init(SPI0_MISO_PORT, SPI0_MISO_PIN, SPI0_MISO_FUN, 1);
	PORT_Init(SPI0_MOSI_PORT, SPI0_MOSI_PIN, SPI0_MOSI_FUN, 0);
	
	SPI_InitStructure SPI_initStruct;
	SPI_initStruct.clkDiv = SPI_CLKDIV_32;
	SPI_initStruct.FrameFormat = SPI_FORMAT_SPI;
	SPI_initStruct.SampleEdge = SPI_SECOND_EDGE;
	SPI_initStruct.IdleLevel = SPI_HIGH_LEVEL;
	SPI_initStruct.WordSize = 8;
	SPI_initStruct.Master = 1;
	SPI_initStruct.RXThreshold = 0;
	SPI_initStruct.RXThresholdIEn = 0;
	SPI_initStruct.TXThreshold = 0;
	SPI_initStruct.TXThresholdIEn = 0;
	SPI_initStruct.TXCompleteIEn = 0;
	SPI_Init(SPI0, &SPI_initStruct);
	SPI_Open(SPI0);
}
void spi0_cs_en(bool en)
{
	if(en){
		GPIO_ClrBit(SPI0_CS_PORT, SPI0_CS_PIN);
	}
	else{
		GPIO_SetBit(SPI0_CS_PORT, SPI0_CS_PIN);
	}
}
void spi0_write_bytes(uint8_t *buff, size_t len)
{
	spi0_cs_en(true);
	for(size_t i = 0; i < len; i++){
		SPI_WriteWithWait(SPI0, (uint32_t)buff[i]);
	}
	spi0_cs_en(false);
}

size_t spi0_read_bytes(uint8_t *buff, size_t len, uint32_t timeout_ms)
{
	size_t cnt = 0;
	uint32_t tm = 0;

	do{
		if(SPI_IsRXEmpty(SPI0)){
			if(tm++ < timeout_ms){
				delay_ms(1);
				continue;
			}
			else{
				break;
			}
		}
		buff[cnt++] = SPI_Read(SPI0);
		tm = 0;
	}while(cnt < len);
	
	return cnt;
}