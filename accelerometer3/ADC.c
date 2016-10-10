#include "ADC.h"
volatile static uint16_t result0,result1,result2;

int adcInit(void)
{

	//Enable the ADC1 module.
	//Enable clock on ADC1
	SYSCTL_RCGCADC_R = (1<<1);
	//Enable PORT E
	SYSCTL_RCGCGPIO_R = (1<<4);
	//SET PORTE_1-3 to input
	GPIO_PORTE_DIR_R &= ~(1<<1);
	GPIO_PORTE_DIR_R &= ~(1<<2);
	GPIO_PORTE_DIR_R &= ~(1<<3);
	//Alternate function select to PORTE_1-3
	GPIO_PORTE_AFSEL_R = (1<<1);
	GPIO_PORTE_AFSEL_R = (1<<2);
	GPIO_PORTE_AFSEL_R = (1<<3);
	//Disable Digital function of PORTE_1-3
	GPIO_PORTE_DEN_R &= ~(1<<1);
	GPIO_PORTE_DEN_R &= ~(1<<2);
	GPIO_PORTE_DEN_R &= ~(1<<3);
	//Disable analog isolation circuit
	GPIO_PORTE_AMSEL_R = (1<<1);
	GPIO_PORTE_AMSEL_R = (1<<2);
	GPIO_PORTE_AMSEL_R = (1<<3);

	//Configure the sample sequencer 0-2
	//Disable the sequencer 0-2
	ADC1_ACTSS_R &= (1<<0);
	ADC1_ACTSS_R &= (1<<1);
	ADC1_ACTSS_R &= (1<<2);
	//Set the type of event triggering - Continuous sampling
	ADC1_EMUX_R &= ~(0xFFF);
	//Set input source-MUX2
	ADC1_SSMUX0_R = 0;
	ADC1_SSMUX1_R = 1;
	ADC1_SSMUX2_R = 2;
	//This control register sets the end bit at 1st sample
	ADC1_SSCTL0_R = 2;
	ADC1_SSCTL1_R = 2;
	ADC1_SSCTL2_R = 2;
	ADC1_SSPRI_R = 0x3201;
	//Enable the sequencer 0-2
	ADC1_ACTSS_R |= (1<<0);
	ADC1_ACTSS_R |= (1<<1);
	ADC1_ACTSS_R |= (1<<2);
}

uint16_t getAdcVal0(){
	//Get value from FIFO0
	ADC1_PSSI_R |= (1<<0);
	result0 = ADC1_SSFIFO0_R;
	ADC1_PSSI_R &= ~(1<<0);
	return result0;
}
uint16_t getAdcVal1(){
	//Get value from FIFO1
	ADC1_PSSI_R |= (1<<1);
	result1 = ADC1_SSFIFO1_R;
	ADC1_PSSI_R &= ~(1<<1);
	return result1;
}
uint16_t getAdcVal2(){
	//Get value from FIFO2
	ADC1_PSSI_R |= (1<<2);
	result2 = ADC1_SSFIFO2_R;
	ADC1_PSSI_R &= ~(1<<2);
	return result2;
}
