/*
 * Timer_private.h
 *
 *  Created on: Aug 11, 2022
 *      Author: mwael
 */
#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

/*********************************************************************************************************/

#define TIMER0_NORMAL_MODE                             1
#define TIMER0_CTC_MODE                                2
#define TIMER0_FAST_PWM_MODE                           3
#define TIMER0_PHASECORRECT_PWM_MODE                   4


#define TIMER0_PRESCALER_MASK                          0b11111000

#define TIMER0_NO_DIVISION                             1
#define TIMER0_DIVIDE_BY_8                             2
#define TIMER0_DIVIDE_BY_64                            3
#define TIMER0_DIVIDE_BY_256                           4
#define TIMER0_DIVIDE_BY_1024                          5


#define TIMER0_CTC_PWM_MODE_MASK                       0b11001111

#define TIMER0_NO_CTC_OUTPUT                           0
#define TIMER0_CTC_TOGGLE                              1
#define TIMER0_CTC_CLEAR                               2
#define TIMER0_CTC_SET                                 3

#define TIMER0_FAST_PWM_CLEAR_CMP                      2
#define TIMER0_FAST_PWM_SET_CMP                        3

#define TIMER0_PHASECORRECT_PWM_CLEAR_CMP_COUNTUP      2
#define TIMER0_PHASECORRECT_PWM_SET_CMP_COUNTUP        3

/***********************************************************************************************************/

#define TIMER1_NORMAL_MODE                             1
#define TIMER1_CTC_MODE                                2
#define TIMER1_FAST_PWM_MODE_8_BIT                     3
#define TIMER1_FAST_PWM_MODE_9_BIT                     4
#define TIMER1_FAST_PWM_MODE_10_BIT                    5
#define TIMER1_FAST_PWM_MODE_ICU1_TOP                  6
#define TIMER1_PHASECORRECT_PWM_MODE_8_BIT             7
#define TIMER1_PHASECORRECT_PWM_MODE_9_BIT             8
#define TIMER1_PHASECORRECT_PWM_MODE_10_BIT            9
#define TIMER1_USE_ICU_WITH_NORMAL_MODE                10


#define TIMER1_PRESCALER_MASK                          0b11111000

#define TIMER1_NO_DIVISION                             1
#define TIMER1_DIVIDE_BY_8                             2
#define TIMER1_DIVIDE_BY_64                            3
#define TIMER1_DIVIDE_BY_256                           4
#define TIMER1_DIVIDE_BY_1024                          5


#define TIMER1_CMPA_NO_CTC_OUTPUT                      0
#define TIMER1_CMPA_CTC_TOGGLE                         1
#define TIMER1_CMPA_CTC_CLEAR                          2
#define TIMER1_CMPA_CTC_SET                            3

#define TIMER1_CMPB_NO_CTC_OUTPUT                      0
#define TIMER1_CMPB_CTC_TOGGLE                         1
#define TIMER1_CMPB_CTC_CLEAR                          2
#define TIMER1_CMPB_CTC_SET                            3

#define TIMER1_CMPA_CTC_PWM_MODE_MASK                  0b00111111
#define TIMER1_CMPB_CTC_PWM_MODE_MASK                  0b11001111

#define TIMER1_CMPA_FAST_PWM_CLEAR_CMP                 2
#define TIMER1_CMPA_FAST_PWM_SET_CMP                   3

#define TIMER1_CMPB_FAST_PWM_CLEAR_CMP                 2
#define TIMER1_CMPB_FAST_PWM_SET_CMP                   3

#define TIMER1_CMPA_PHASECORRECT_PWM_CLEAR_CMP_COUNTUP 2
#define TIMER1_CMPA_PHASECORRECT_PWM_SET_CMP_COUNTUP   3

#define TIMER1_CMPB_PHASECORRECT_PWM_CLEAR_CMP_COUNTUP 2
#define TIMER1_CMPB_PHASECORRECT_PWM_SET_CMP_COUNTUP   3

#define TIMER1_ICU_TRIGGER_FALLING                     0
#define TIMER1_ICU_TRIGGER_RISING                      1

/************************************************************************************************************/

#define TIMER2_NORMAL_MODE                             1
#define TIMER2_CTC_MODE                                2
#define TIMER2_FAST_PWM_MODE                           3
#define TIMER2_PHASECORRECT_PWM_MODE                   4

#define TIMER2_PRESCALER_MASK                          0b11111000

#define TIMER2_NO_DIVISION                             1
#define TIMER2_DIVIDE_BY_8                             2
#define TIMER2_DIVIDE_BY_32                            3
#define TIMER2_DIVIDE_BY_64                            4
#define TIMER2_DIVIDE_BY_128                           5
#define TIMER2_DIVIDE_BY_256                           6
#define TIMER2_DIVIDE_BY_1024                          7


#define TIMER2_CTC_PWM_MODE_MASK                       0b11001111

#define TIMER2_NO_CTC_OUTPUT                           0
#define TIMER2_CTC_TOGGLE                              1
#define TIMER2_CTC_CLEAR                               2
#define TIMER2_CTC_SET                                 3

#define TIMER2_FAST_PWM_CLEAR_CMP                      2
#define TIMER2_FAST_PWM_SET_CMP                        3

#define TIMER2_PHASECORRECT_PWM_CLEAR_CMP_COUNTUP      2
#define TIMER2_PHASECORRECT_PWM_SET_CMP_COUNTUP        3
/**********************************************************************************************************/

#endif

