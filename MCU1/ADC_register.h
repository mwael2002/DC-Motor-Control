/*
 * ADC_register.h
 *
 *  Created on: Oct 9, 2021
 *      Author: mwael
 */

#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

//ADC Multiplexer Selection Register
#define ADMUX       *((volatile U8*)0x27)
#define REFS1        7
#define REFS0        6
#define ADLAR        5
#define MUX4         4
#define MUX3         3
#define MUX2         2
#define MUX1         1
#define MUX0         0

//ADC Control and Status Register A
#define ADCSRA	 	*((volatile U8*)0x26)
#define ADEN        7
#define ADSC        6
#define ADATE       5
#define ADIF        4
#define ADIE        3
#define ADPS2       2
#define ADPS1       1
#define ADPS0       0

#define ADCH *((volatile U8*)0x25)      //ADC Data Register High Byte
#define ADCL *((volatile U8*)0x24)      //ADC Data Register Low Byte

#define SFIOR *((volatile U8*)0x50)

#endif /* ADC_REGISTER_H_ */
