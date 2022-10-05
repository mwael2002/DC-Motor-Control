/*
 * ADC_program.c
 *
 *  Created on: Oct 8, 2021
 *      Author: mwael
 */
#include "STD_Types.h"
#include"bit_calc.h"
#include "ADC_register.h"
#include"ADC_private.h"
#include "ADC_config.h"
#include"ADC_interface.h"


//global pointer to hold the conv. result
static U16* ADC_Conversion_Result=NULL;

//global pointer to hold the notification function
static void(*ADC_Notification_Func)(void)=NULL;

//global variable to indicate for ADCperipheral state
static U8 ADC_Busy_State=IDLE;

static U8 ADC_ISR_Source;

static U8* ADC_Chain_Channel=NULL;
static U8 ADC_Chain_Size;
static U8 ADC_Chain_Index;

void ADC_init(void){

#if REF_V==AREF
	    clear_bit(ADMUX,REFS1);
		clear_bit(ADMux,REFS0);
#elif REF_V==AVCC
	    clear_bit(ADMUX,REFS1);
		set_bit(ADMUX,REFS0);
#elif REF_V==INTERNAL_REF
		set_bit(ADMUX,REFS1);
		set_bit(ADMUX,REFS0);
#else
#error "Incorrect reference voltage configuration"
#endif

		ADCSRA &= PRESCALER_MASK;     //Configuring prescaler
		ADCSRA |= ADC_PRESCALER;

		set_bit(ADMUX,ADLAR); //Left Adjustment


#if ADC_CONVERSION_MODE==SINGLE_CONVERSION
	    clear_bit(ADCSRA,ADATE);
#elif ADC_CONVERSION_MODE==AUTO_TRIGGER
		set_bit(ADCSRA,ADATE);   //enable auto trigger

		SFIOR &= AUTO_TRIGGER_MASK;
		SFIOR = (SFIOR | (AUTO_TRIGGER_MODE<<5));

#else
#error "Incorrect conversion mode configuration"
#endif
		set_bit(ADCSRA,ADEN); // ADC Enable
}




U8 ADC_Start_Conversion_Synch(U8 Channel,U16* post_result){

U8 error_state=OK;
U32 counter=0;

if(post_result != NULL){
	   if(ADC_Busy_State==IDLE){

		   ADC_Busy_State=BUSY;

	ADMUX &= CHANNEL_MASK; // channel selection
	ADMUX |= Channel;


	set_bit(ADCSRA,ADSC); // start conversion(single conversion)

	while((get_bit(ADCSRA,ADIF)==0)&&(counter<ADC_TIME_OUT)){
		counter++;
	}
	if(counter==ADC_TIME_OUT){
       error_state=TIMEOUT_STATE;
	}
	else{
	set_bit(ADCSRA,ADIF);  //clear flag

	#if RES==EIGHT_BITS_RES
	*post_result=ADCH;
    #elif RES==TEN_BITS_RES
	U16 res = (ADCL>>6);
	U16 Copy_ADCH=ADCH;
	res |= (Copy_ADCH<<2);
	*post_result=res;
    #else
    #error "Incorrect resolution mode configuration"
    #endif

         }
	    ADC_Busy_State=IDLE;
	   }

	   else{
		   error_state=BUSY_FUNC;
	   }

    }
else {
	error_state=NULL_POINTER;

}

    return error_state;
}
U8 ADC_Start_Conversion_Asynch(U8 Channel,U16* Post_Result,void (*ptr)(void)){

    U8 error_state=OK;
	if((Post_Result!=NULL)&&(ptr!= NULL)){

		//check if it is busy with another conv.
		if(ADC_Busy_State==IDLE){
			//ADC now is busy
			ADC_Busy_State=BUSY;

			ADC_ISR_Source=SINGLE_CONVERSION;

		//initialize the global pointer to point to result
		ADC_Conversion_Result=Post_Result;

		//initialize the global pointer to point to notification function
		ADC_Notification_Func=ptr;

		ADMUX &= CHANNEL_MASK; // channel selection
		ADMUX |= Channel;


		set_bit(ADCSRA,ADSC); // start conversion(single conversion)

		//EENABLE ADC CONV. COMPLETE INTERRUPT
		set_bit(ADCSRA,ADIE);
		}
		else {
			error_state=BUSY_FUNC;
		}

	}
	else {
		error_state=NULL_POINTER;

	}
	return error_state;
}


U8 ADC_Start_Chain_Conversion_Asynch(ADC_Chain* Copy_Chain){

	U8 error_state=OK;

if((Copy_Chain != NULL)&&(Copy_Chain->Chain_Notification_Func!=NULL)){

		if(ADC_Busy_State==IDLE){

			ADC_Busy_State=BUSY;

			ADC_ISR_Source=CHAIN_CONVERSION;

			ADC_Chain_Channel=Copy_Chain-> Chain_Channel;
			ADC_Conversion_Result=Copy_Chain-> Chain_Result;
			ADC_Chain_Size=Copy_Chain->Chain_Size;
			ADC_Notification_Func=Copy_Chain->Chain_Notification_Func;

			ADC_Chain_Index=0;

			//SET THE REQUIRED CHANNEL
			ADMUX&=CHANNEL_MASK;
			ADMUX|=ADC_Chain_Channel[ADC_Chain_Index];

			//START CONV.
			set_bit(ADCSRA,ADSC);

			//EENABLE ADC CONV. COMPLETE INTERRUPT
			set_bit(ADCSRA,ADIE);

		}
		else error_state=BUSY_FUNC;
	}
	else{
		error_state=NULL_POINTER;
	}
	return error_state;
}



void __vector_16(void) __attribute__((signal));
void __vector_16(void){

	if(ADC_ISR_Source==SINGLE_CONVERSION){

	//read the conv. result
    #if RES==EIGHT_BITS_RES
    *ADC_Conversion_Result=ADCH;
    #elif RES==TEN_BITS_RES
    U16 res = (ADCL>>6);
    U16 Copy_ADCH=ADCH;
    res |= (Copy_ADCH<<2);
    *ADC_Conversion_Result=res;
    #else
    #error "Incorrect resolution mode configuration"
    #endif


	//release the ADC busy state,ADC is now idle
	ADC_Busy_State=IDLE;

	//disable the conv. complete interrupt enable
		clear_bit(ADCSRA,ADIE);

	//invoke the call back notification
	if(ADC_Notification_Func!=NULL){
		ADC_Notification_Func();
	    }
	}
	else{ //chain conversion

			//read the conv. result
            #if RES==EIGHT_BITS_RES
		    ADC_Conversion_Result[ADC_Chain_Index]=ADCH;
            #elif RES==TEN_BITS_RES
            U16 res = (ADCL>>6);
            U16 Copy_ADCH=ADCH;
            res |= (Copy_ADCH<<2);
            ADC_Conversion_Result[ADC_Chain_Index]=res;
            #else
            #error "Incorrect resolution mode configuration"
            #endif


			ADC_Chain_Index++;

			if(ADC_Chain_Index==ADC_Chain_Size){

				//chain is finished

				ADC_Busy_State=IDLE;

				//disable the conv. complete interrupt enable
				clear_bit(ADCSRA,ADIE);

				//invoke the call back notification
				if(ADC_Notification_Func!=NULL){
					ADC_Notification_Func();
				}
			}
			else {

				//SET THE REQUIRED CHANNEL
				ADMUX &= CHANNEL_MASK;
				ADMUX |= ADC_Chain_Channel[ADC_Chain_Index];

				//START CONV.
				set_bit(ADCSRA,ADSC);
			}


		}
}
