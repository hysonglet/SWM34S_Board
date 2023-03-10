

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