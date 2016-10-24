#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "UART.h"
#include "ADC.h"
int main(void){
	int32_t data;
	uartInit();
	adcInit();
	while(1){
		data = uartRead();
		if (data == 'K'){
			GPIO_PORTB_DATA_R |= (1<<2);
			uartWrite(getAdcVal0());
			uartWrite(getAdcVal1());
			uartWrite(getAdcVal2());
			uartWrite(getAdcVal3());
		}
		GPIO_PORTB_DATA_R &= ~(1<<2);
	}
}
