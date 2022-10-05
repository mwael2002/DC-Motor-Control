/*
 * Timer_0_ov_private.h
 *
 *  Created on: Oct 22, 2021
 *      Author: mwael
 */

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#define  TIMSK         *((volatile U8*)0x59)

#define  TOIE2   6
#define  OCIE2   7

#define  TICIE1  5
#define  OCIE1A  4
#define  OCIE1B  3
#define  TOIE1   2

#define  OCIE0   1
#define  TOIE0   0


/*timer0***************************************************************************************************************/
#define  OCR0          *((volatile U8*)0x5c)

#define  TCCR0         *((volatile U8*)0x53)
#define  WGM00   6
#define  WGM01   3
#define  COM00   4
#define  COM01   5


#define  TCNT0         *((volatile U8*)0x52)


/**********************************************************************************************************/

/*timer1***************************************************************************************************/
#define  OCR1A           *((volatile U16*)0x4A)

#define  OCR1B           *((volatile U16*)0x48)

#define  ICR1            *((volatile U16*)0x46)

#define  TCNT1           *((volatile U16*)0x4C)


#define  TCCR1A          *((volatile U8*)0x4F)
#define  WGM10    0
#define  WGM11    1
#define  COM1A1   7
#define  COM1A0   6
#define  COM1B1   5
#define  COM1B0   4

#define  TCCR1B          *((volatile U8*)0x4E)
#define  WGM13    4
#define  WGM12    3
#define  ICNC1    7
#define  CS10     0
#define  CS11     1
#define  CS12     2
#define  ICES1    6


/**********************************************************************************************************/

/*timer2*****************************************************************************************************/
#define  OCR2          *((volatile U8*)0x43)

#define  TCCR2         *((volatile U8*)0x45)
#define  WGM20   6
#define  WGM21   3
#define  COM20   4
#define  COM21   5

#define  TCNT2         *((volatile U8*)0x44)

/**********************************************************************************************************/


#endif /* TIMER_REGISTER_H_ */
