/*
 * ADC_private.h
 *
 *  Created on: Jul 9, 2022
 *      Author: mwael
 */

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


#define AREF 1
#define AVCC 2
#define INTERNAL_REF 3


#define EIGHT_BITS_RES 1
#define TEN_BITS_RES 2


#define SINGLE_CONVERSION     1
#define CHAIN_CONVERSION      2
#define AUTO_TRIGGER          3

#define FREE_RUNNING_MODE              0
#define ANALOG_COMPARATOR              1
#define EXTERNAL_INTERRUPT_REQUEST_0   2
#define TIMER0_COMPARE_MATCH           3
#define TIMER0_OVERFLOW                4
#define TIMER_COMPARE_MATCH_B          5
#define TIMER_COUNTER1_OVERFLOW        6
#define TIMER_COUNTER1_CAPTURE_EVENT   7

#define AUTO_TRIGGER_MASK              0b00011111


#define DIVISION_BY_2    1
#define DIVISION_BY_4    2
#define DIVISION_BY_8    3
#define DIVISION_BY_16   4
#define DIVISION_BY_32   5
#define DIVISION_BY_64   6
#define DIVISION_BY_128  7

#define PRESCALER_MASK       0b11111000


#define CHANNEL_MASK         0b11100000


#define IDLE 0
#define BUSY 1;


#endif /* ADC_PRIVATE_H_ */
