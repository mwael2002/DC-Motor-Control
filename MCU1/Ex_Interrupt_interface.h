/*
 * Ex_I_interface.h
 *
 *  Created on: Oct 1, 2021
 *      Author: mwael
 */

#ifndef EX_INTERRUPT_INTERFACE_H_
#define EX_INTERRUPT_INTERFACE_H_

#define Ex_Int_0 0
#define Ex_Int_1 1
#define Ex_Int_2 2


#define Low_level 0b00                 // for INT0&INT1 only
#define Any_logical_change 0b01        // for INT0&INT1 only

#define Ex_Int_Falling_edge 0b10
#define Ex_Int_Rising_edge  0b11


void Ex_Int_Enable(U8 Int_index);
void Ex_Int_Disable(U8 Int_index);

U8 Ex_Int_set_level(U8 Int_index,U8 Int_level);
U8 Ex_Int_call_back(void (*ptr)(void),U8 Int_index);

#endif /* EX_INTERRUPT_INTERFACE_H_ */
