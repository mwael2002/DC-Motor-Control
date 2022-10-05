/*
 * ADC_config.h
 *
 *  Created on: Jul 9, 2022
 *      Author: mwael
 */
#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/*Choose Options to select reference voltage:
 * 1-AREF               Voltage on AREF pin
 * 2-AVCC               Same voltage of ADC with external capacitor at AREF pin
 * 3-INTERNAL_REF       Internal 2.56V Voltage Reference with external capacitor at AREF pin
 */


#define REF_V                         AVCC
/*
 * Choose maximum voltage of ADC either it's in AREF OR AVCC mode
 */
#define Max_voltage                     5


/*Choose resolution:
 * 1-EIGHT_BITS_RES
 * 2-TEN_BITS_RES
 */
#define RES     TEN_BITS_RES


/*Choose Prescaler:
DIVISION_BY_2
DIVISION_BY_4
DIVISION_BY_8
DIVISION_BY_16
DIVISION_BY_32
DIVISION_BY_64
DIVISION_BY_128
*/
#define ADC_PRESCALER            DIVISION_BY_128


/*
 * Choose Conversion mode:
 * 1-AUTO_TRIGGER
 * 2-SINGLECONVERSION
 */
#define ADC_CONVERSION_MODE     SINGLE_CONVERSION


/*Choose mode of Auto trigger:
 * 1-FREE_RUNNING MODE
 * 2-ANALOG_COMPARATOR
 * 3-EXTERNAL_INTERRUPT_REQUEST_0
 * 4-TIMER0_COMPARE_MATCH
 * 5-TIMER0_OVERFLOW
 * 6-IMER_COMPARE_MATCH_B
 * 7-TIMER_COUNTER1_OVERFLOW
 * TIMER_COUNTER1_CAPTURE_EVENT
 */
#define AUTO_TRIGGER_MODE       FREE_RUNNING_MODE

#define ADC_TIME_OUT            50000
#endif /* ADC_CONFIG_H_ */
