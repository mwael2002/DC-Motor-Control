/*
 * Timer_0_ov_interface.h
 *
 *  Created on: Oct 22, 2021
 *      Author: mwael
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_


#define TIMER0_ID                                      0
#define TIMER1_ID                                      1
#define TIMER2_ID                                      2

#define CMPA                                           0
#define CMPB                                           1

#define FALLING_EDGE                                   0
#define RISING_EDGE                                    1

#define TIMER_INT_ENABLE                               1
#define TIMER_INT_DISABLE                              0

#define TIMER0_OVERFLOW_INT                            0
#define TIMER0_CTC_INT                                 1
#define TIMER1_OVERFLOW_INT                            2
#define TIMER1_CTCB_INT                                3
#define TIMER1_CTCA_INT                                4
#define TIMER1_ICU_INT                                 5
#define TIMER2_OVERFLOW_INT                            6
#define TIMER2_CTC_INT                                 7

void Timer0_init(void);
void Timer1_init(void);
void Timer2_init(void);

U32 Overflow_time_calculate(U8 Timer_Id);
void Overflow_restart_count(U8 Timer_Id);
void set_comparematch_value(U8 Timer_Id,U8 ctc_value);
void Timer1_set_comparematch_value(U8 Compare_Register ,U16 ctc_value);

U16 ICU_Read_Input_Capture(void);
U8 ICU_CallBack(void (*ptr)(void));
void ICU_Set_Trigger(U8 Trigger_Source);
void Set_ICR1(U16 ICR1_Value);

void Timer_Int_Enable_Disable(U8 Timer_interrupt,U8 Enable_Disable);

U8 Timer_callback(U8 Timer_Id,void(*ptr)(void));

#if TIMER1_USE_CMPB==1
U8 CompareB_callback(void(*ptr)(void));
#endif





#endif /* TIMER_INTERFACE_H_ */
