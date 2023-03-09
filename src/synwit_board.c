

#include "synwit_board.h"
#include <SWM341.h>
#include <stdio.h>
#include <stdarg.h>

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
#define KEY_PORT    GPIOA
#define KEY_PIN		PIN14
#define KEY_PUSH_STATUE 0

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