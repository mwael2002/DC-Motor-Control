/*
 * Ex_Interrupt.c
 *
 *  Created on: Oct 1, 2021
 *      Author: mwael
 */
#include "STD_Types.h"
#include"bit_calc.h"
#include "Ex_Interrupt_interface.h"
#include "Ex_Interrupt_register.h"


void (*pvoidcallback[3])(void)={NULL};

void Ex_Int_Enable(U8 Int_index){
	switch(Int_index){
	case Ex_Int_0:
		set_bit(GICR,GICR_INT0);
	break;
	case Ex_Int_1:
		set_bit(GICR,GICR_INT1);
		break;
	case Ex_Int_2:
		set_bit(GICR,GICR_INT2);
		break;
	}
}
void Ex_Int_Disable(U8 Int_index){
	switch(Int_index){
	case Ex_Int_0:
		clear_bit(GICR,GICR_INT0);
	break;
	case Ex_Int_1:
		clear_bit(GICR,GICR_INT1);
		break;
	case Ex_Int_2:
		clear_bit(GICR ,GICR_INT2);
		break;
	}
}
U8 Ex_Int_set_level(U8 Int_index,U8 Int_level){
	U8 error_state=OK;
	switch(Int_index){
	case Ex_Int_0 :
	assign_bit(MCUCR,MCUCR_ISC00,get_bit(Int_level,0));
	assign_bit(MCUCR,MCUCR_ISC01,get_bit(Int_level,1));
	break;
	case Ex_Int_1 :
		assign_bit(MCUCR,MCUCR_ISC10,get_bit(Int_level,0));
		assign_bit(MCUCR,MCUCR_ISC11,get_bit(Int_level,1));
		break;
	case Ex_Int_2 :
		if((Int_level!=Low_level)&&(Int_level!=Any_logical_change)){
		assign_bit(MCUCSR,MCUCSR_ISC2,(Int_level-2));
		}
		else{
			error_state=NOK;
		}
		break;
	default:
		error_state=NOK;
	}
	return error_state;
}



void __vector_1(void) __attribute__((signal));
void __vector_1(void){
	if(pvoidcallback[0]!=NULL){
	pvoidcallback[0]();
}
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void){
	if(pvoidcallback[1]!=NULL){
	pvoidcallback[1]();
}
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void){
	if(pvoidcallback[2]!=NULL){
	pvoidcallback[2]();
	}
}


U8 Ex_Int_call_back(void (*ptr)(void),U8 Int_index){
U8 error_state=OK;
if(ptr!=NULL){
	pvoidcallback[Int_index]=ptr;
}
else{
	error_state=NULL_POINTER;
}
return error_state;
}
