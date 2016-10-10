#include "UART.h"

void uartInit(){
	//Set clock
	SysCtlClockSet( SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_SYSDIV_4 );
	//Enable UART0
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	//Enable GPIOA
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	//Set GPIO to be output
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, (GPIO_PIN_0 | GPIO_PIN_1));

	//Configure UART to use baud = 9600, 8-bit data, 1 stop bit, no parity
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600,
	     UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
	     UART_CONFIG_PAR_NONE);
}

void uartWrite(uint16_t val,char c){
	char str[10];
	int i;
	//UARTCharPut(UART0_BASE,c);
	sprintf(str,"%d",val);
	for(i=0;str[i]!= '\0';i++){
		UARTCharPut(UART0_BASE,str[i]);
	}
	UARTCharPut(UART0_BASE,'\n');
}

int32_t uartRead(){
	return UARTCharGet(UART0_BASE);
}

