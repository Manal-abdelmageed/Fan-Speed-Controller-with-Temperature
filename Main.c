/*
 * Mini_Project3.c
 *
 *  Created on: Oct 14, 2023
 *      Author: hp
 */
#include <avr/io.h>
#include "gpio.h"
#include "lm35_sensor.h"
#include "lcd.h"
#include "dcmotor.h"
#include "adc.h"

int main() {
	/*
	 set the parameters of ADC and initiate the needed drives
	 */
ADC_ConfigType ADC_parameters;
ADC_parameters.ref_volt = INTERNAL;
ADC_parameters.F_ADC = F_CPU_8;
ADC_init(&ADC_parameters);
LCD_init();
DcMotor_init();
	float speed;
	while (1) {
		/*
		 Get the temperature value then display it
		 */
		char adc_value = LM35_getTemperature();
		LCD_moveCursor(1, 10);
		LCD_intgerToString (adc_value);
		LCD_displayCharacter (' ');
		/*
		 set the speed value as a percentage of the full speed depending on the temperature value
		 */
		if (adc_value < 30) {
			speed = 0;
			LCD_moveCursor(0, 4);
			LCD_displayString("Fan is OFF");
			LCD_moveCursor(1, 4);
			LCD_displayString("Temp =   c");
		} else if (adc_value >= 30 && adc_value < 60) {
			speed = 0.25;
			LCD_moveCursor(0, 4);
			LCD_displayString("Fan is ON ");
			LCD_moveCursor(1, 4);
			LCD_displayString("Temp =   c");
		} else if (adc_value >= 60 && adc_value < 90) {
			speed = 0.5;
			LCD_moveCursor(0, 4);
			LCD_displayString("Fan is ON ");
			LCD_moveCursor(1, 4);
			LCD_displayString("Temp =   c");
		} else if (adc_value>= 90 && adc_value < 120) {
			speed = 0.75;
			LCD_moveCursor(0, 4);
			LCD_displayString("Fan is ON ");
			LCD_moveCursor(1, 4);
			LCD_displayString("Temp =   c");
		} else if (adc_value >= 120) {
			speed = 1;
			LCD_moveCursor(0, 4);
			LCD_displayString("Fan is ON ");
			LCD_moveCursor(1, 4);
			LCD_displayString("Temp =   c");
		}
		/*
		 make the motor rotates CW and with the needed speed by Timer 0 PWM
		 */
		DcMotor_rotate(CW, (speed*255));
	}
	return 0;
}
