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
			uartWrite(getAdcVal0(),'a');
			uartWrite(getAdcVal1(),'b');
			uartWrite(getAdcVal2(),'c');
		}
	}
}
