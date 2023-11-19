#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

# ifdef INTERRUPT
volatile uint16 data;
#endif
void ADC_init(const ADC_ConfigType *Config_Ptr) {
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = (ADMUX & 0x3F) | ((Config_Ptr->ref_volt)<<REFS0);
	ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr->F_ADC);
	ADCSRA |= (1 << ADEN) | (1 << ADIE);
}
uint16 ADC_readChannel(uint8 ch_num) {
	/*
	 inserting the channel number
	 */
	ADMUX = (ADMUX & 0xE0) | ch_num;
	/*
	 ADSC = 1 to start the conversion
	 */
	SET_BIT(ADCSRA, ADSC);
#ifndef INTERRUPT
	/*
	 define interrupt if we want to use it
	 if not use polling by a loop which will not end until the conversion is done
	 */
	while (BIT_IS_CLEAR(ADCSRA, ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA, ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
#elif
	return;
#endif
}
# ifdef INTERRUPT
ISR (INTERRUPT_ADC){
	data = ADC; /*Read the digital value from the data register */
}
#endif
