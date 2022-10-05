/*
 * Ex_I_register.h
 *
 *  Created on: Oct 1, 2021
 *      Author: mwael
 */

#ifndef EX_INTERRUPT_REGISTER_H_

#define EX_INTERRUPT_REGISTER_H_
#define MCUCR *((volatile U8*)0x55)
#define MCUCR_ISC11  3                     //Int1 sense control bit 1
#define MCUCR_ISC10  2                     //Int1 sense control bit 0
#define MCUCR_ISC01  1                     //Int0 sense control bit 1
#define MCUCR_ISC00  0                     //Int0 sense control bit 0

#define MCUCSR *((volatile U8*)0x54)
#define MCUCSR_ISC2  6

#define GICR *((volatile U8*)0x5B)
#define GICR_INT1    7
#define GICR_INT0    6
#define GICR_INT2    5

#endif /* EX_INTERRUPT_REGISTER_H_ */
