/*
 * Timer_0_ov_program.c
 *
 *  Created on: Oct 22, 2021
 *      Author: mwael
 */
#include"bit_calc.h"
#include "STD_Types.h"
#include "Timer_register.h"
#include "Timer_private.h"
#include "Timer_config.h"
#include "Timer_interface.h"


static U16 TCNTX[3];
static U16 Timerx_prescaler[3]={TIMER0_PRESCALER,TIMER1_PRESCALER,TIMER2_PRESCALER};
static U16 Timerx_overflow_time[3]={TIMER0_OVERFLOW_TIME_MILLISECONDS,TIMER1_OVERFLOW_TIME_MILLISECONDS
		                   ,TIMER2_OVERFLOW_TIME_MILLISECONDS};



void (*timer_ptr[3]) (void);
void (*ICU_ptr)(void);

#if TIMER1_USE_CMPB==1
void (*CompareB_ptr) (void);
#endif



void Timer0_init(void){

	 //set the required prescaler
	 TCCR0 &= TIMER0_PRESCALER_MASK;
	 TCCR0 |= TIMER0_PRESCALER;

	#if TIMER0_MODE==TIMER0_NORMAL_MODE
		//initialize waveform generation mode to work as normal mode
		clear_bit(TCCR0,WGM00);
		clear_bit(TCCR0,WGM01);

		//set the required preload
		Overflow_time_calculate(TIMER0_ID);
		TCNT0=TCNTX[0];

		 //timer0 over flow interrupt enable
		 set_bit(TIMSK,TOIE0);

	#elif TIMER0_MODE==TIMER0_CTC_MODE

	    //initialize waveform generation mode to work as CTC mode
		clear_bit(TCCR0,WGM00);
		set_bit(TCCR0,WGM01);

		 //set compare match output mode
		 TCCR0 &= TIMER0_CTC_PWM_MODE_MASK;
		 TCCR0 |= (TIMER0_CTC_MODE_OUTPUT<<4);




		 //timer0 comp match interrupt enable
		 set_bit(TIMSK,OCIE0);



	#elif TIMER0_MODE==TIMER0_FAST_PWM_MODE
		    //initialize waveform generation mode to work as Fast PWM mode
		    set_bit(TCCR0,WGM00);
		    set_bit(TCCR0,WGM01);


		    //set compare match output mode
		    TCCR0 &= TIMER0_CTC_PWM_MODE_MASK;
		    TCCR0 |= (TIMER0_FAST_PWM_MODE_OUTPUT<<4);

	#elif TIMER0_MODE==TIMER0_PHASECORRECT_PWM_MODE
	    //initialize waveform generation mode to work as Phase Correct PWM mode
	    set_bit(TCCR0,WGM00);
	    clear_bit(TCCR0,WGM01);



	    //set compare match output mode
	    TCCR0 &= TIMER0_CTC_PWM_MODE_MASK;
	    TCCR0 |= (TIMER0_PHASECORRECT_PWM_MODE_OUTPUT<<4);

	#else
	#error "wrong mode"
	#endif

}

void __vector_11(void) __attribute__((signal));
void __vector_11(void){
timer_ptr[TIMER0_ID]();
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void){
timer_ptr[TIMER0_ID]();
}


/*********************************************************************************************************************/

void Timer1_init(void){

	 TCCR1B &= TIMER1_PRESCALER_MASK;
	 TCCR1B |= TIMER1_PRESCALER;


#if TIMER1_MODE==TIMER1_NORMAL_MODE
	//Waveform Generation Mode work as normal mode
	clear_bit(TCCR1A,WGM10);
	clear_bit(TCCR1A,WGM11);
	clear_bit(TCCR1B,WGM12);
	clear_bit(TCCR1B,WGM13);

	//set the required preload
    Overflow_time_calculate(TIMER1_ID);
    TCNT1=TCNTX[1];

    //timer0 over flow interrupt enable
    set_bit(TIMSK,TOIE1);

#elif TIMER1_MODE==TIMER1_CTC_MODE

	clear_bit(TCCR1A,WGM10);
	clear_bit(TCCR1A,WGM11);
	set_bit(TCCR1B,WGM12);
	clear_bit(TCCR1B,WGM13);

	TCCR1A &= TIMER1_CMPA_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPA_CTC_MODE_OUTPUT<<6);

    set_bit(TIMSK,OCIE1A);

#if TIMER1_USE_CMPB==1

    TCCR1A &= TIMER1_CMPB_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPB_CTC_MODE_OUTPUT<<4);

    set_bit(TIMSK,OCIE1B);

#endif


#elif TIMER1_MODE==TIMER1_FAST_PWM_MODE_8_BIT

	set_bit(TCCR1A,WGM10);
	clear_bit(TCCR1A,WGM11);
	set_bit(TCCR1B,WGM12);
	clear_bit(TCCR1B,WGM13);

	TCCR1A &= TIMER1_CMPA_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPA_FAST_PWM_MODE_OUTPUT<<6);

#if TIMER1_USE_CMPB==1

    TCCR1A &= TIMER1_CMPB_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPB_FAST_PWM_MODE_OUTPUT<<4);

#endif

#elif TIMER1_MODE==TIMER1_FAST_PWM_MODE_9_BIT

	clear_bit(TCCR1A,WGM10);
	set_bit(TCCR1A,WGM11);
	set_bit(TCCR1B,WGM12);
	clear_bit(TCCR1B,WGM13);

	TCCR1A &= TIMER1_CMPA_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPA_FAST_PWM_MODE_OUTPUT<<6);

#if TIMER1_USE_CMPB==1

    TCCR1A &= TIMER1_CMPB_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPB_FAST_PWM_MODE_OUTPUT<<4);

#endif

#elif TIMER1_MODE==TIMER1_FAST_PWM_MODE_10_BIT

	set_bit(TCCR1A,WGM10);
	set_bit(TCCR1A,WGM11);
	set_bit(TCCR1B,WGM12);
	clear_bit(TCCR1B,WGM13);

	TCCR1A &= TIMER1_CMPA_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPA_FAST_PWM_MODE_OUTPUT<<6);

#if TIMER1_USE_CMPB==1

    TCCR1A &= TIMER1_CMPB_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPB_FAST_PWM_MODE_OUTPUT<<4);

#endif


#elif TIMER1_MODE==TIMER1_FAST_PWM_MODE_ICU1_TOP

	clear_bit(TCCR1A,WGM10);
	set_bit(TCCR1A,WGM11);
	set_bit(TCCR1B,WGM12);
	set_bit(TCCR1B,WGM13);

	TCCR1A &= TIMER1_CMPA_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPA_FAST_PWM_MODE_OUTPUT<<6);

#if TIMER1_USE_CMPB==1

    TCCR1A &= TIMER1_CMPB_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPB_FAST_PWM_MODE_OUTPUT<<4);

#endif

#elif TIMER1_MODE==TIMER1_PHASECORRECT_PWM_MODE_8_BIT

	set_bit(TCCR1A,WGM10);
	clear_bit(TCCR1A,WGM11);
	clear_bit(TCCR1B,WGM12);
	clear_bit(TCCR1B,WGM13);

	TCCR1A &= TIMER1_CMPA_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPA_FAST_PWM_MODE_OUTPUT<<6);

#if TIMER1_USE_CMPB==1

    TCCR1A &= TIMER1_CMPB_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPB_FAST_PWM_MODE_OUTPUT<<4);

#endif

#elif TIMER1_MODE==TIMER1_PHASECORRECT_PWM_MODE_9_BIT

	clear_bit(TCCR1A,WGM10);
	set_bit(TCCR1A,WGM11);
	clear_bit(TCCR1B,WGM12);
	clear_bit(TCCR1B,WGM13);

	TCCR1A &= TIMER1_CMPA_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPA_FAST_PWM_MODE_OUTPUT<<6);

#if TIMER1_USE_CMPB==1

    TCCR1A &= TIMER1_CMPB_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPB_FAST_PWM_MODE_OUTPUT<<4);

#endif

#elif TIMER1_MODE==TIMER1_PHASECORRECT_PWM_MODE_10_BIT

	set_bit(TCCR1A,WGM10);
	set_bit(TCCR1A,WGM11);
	clear_bit(TCCR1B,WGM12);
	clear_bit(TCCR1B,WGM13);

	TCCR1A &= TIMER1_CMPA_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPA_FAST_PWM_MODE_OUTPUT<<6);

#if TIMER1_USE_CMPB==1

    TCCR1A &= TIMER1_CMPB_CTC_PWM_MODE_MASK;
    TCCR1A |= (TIMER1_CMPB_FAST_PWM_MODE_OUTPUT<<4);

#endif

#elif TIMER1_MODE==TIMER1_USE_ICU_WITH_NORMAL_MODE
	//Waveform Generation Mode work as normal mode
	clear_bit(TCCR1A,WGM10);
	clear_bit(TCCR1A,WGM11);
	clear_bit(TCCR1B,WGM12);
	clear_bit(TCCR1B,WGM13);


	//set trigger to rising edge initially
	assign_bit(TCCR1B,ICES1,TIMER1_ICU_INIT_TRIGGER);

	//set noise canceler
    #if TIMER1_ICU_NOISE_CANCELER==1
    set_bit(TCCR1B,ICNC1);
	#endif

	//set the required preload
    Overflow_time_calculate(TIMER1_ID);
    TCNT1=TCNTX[1];

    //timer1 over flow interrupt enable
    set_bit(TIMSK,TOIE1);

    //enable the ICU interrupt
	set_bit(TIMSK,TICIE1);


#else
#error "wrong mode"
#endif

}


void __vector_9(void) __attribute__((signal));
void __vector_9(void){
timer_ptr[TIMER1_ID]();
}
void __vector_7(void) __attribute__((signal));
void __vector_7(void){
timer_ptr[TIMER1_ID]();
}

#if TIMER1_USE_CMPB==1
void __vector_8(void) __attribute__((signal));
void __vector_8(void){
CompareB_ptr();
}
#endif



U16 ICU_Read_Input_Capture(void){
	return ICR1;
}

void Set_ICR1(U16 ICR1_Value){
	 ICR1=ICR1_Value;
}

void ICU_Set_Trigger(U8 Trigger_Source){
	switch(Trigger_Source){
	case FALLING_EDGE: clear_bit(TCCR1B,ICES1);
	break;
	case RISING_EDGE:  set_bit(TCCR1B,ICES1);
	break;
	}

}


U8 ICU_CallBack(void (*ptr)(void)){
	U8 error_state=OK;

	if(ptr != NULL){
		ICU_ptr = ptr;
	}
	else error_state=NOK;
	return error_state;
}

void __vector_6(void) __attribute((signal));
void __vector_6(void){
		ICU_ptr();
}

/*********************************************************************************************************************/



void Timer2_init(void){

	 //set the required prescaler
	 TCCR2 &= TIMER2_PRESCALER_MASK;
	 TCCR2 |= TIMER2_PRESCALER;

	#if TIMER2_MODE==TIMER2_NORMAL_MODE
		//initialize waveform generation mode to work as normal mode
		clear_bit(TCCR2,WGM20);
		clear_bit(TCCR2,WGM21);

		//set the required preload
		Overflow_time_calculate(TIMER2_ID);
		TCNT2=TCNTX[2];

		 //timer0 over flow interrupt enable
		 set_bit(TIMSK,TOIE2);

	#elif TIMER2_MODE==TIMER2_CTC_MODE

	    //initialize waveform generation mode to work as CTC mode
		clear_bit(TCCR2,WGM20);
		set_bit(TCCR2,WGM21);

		 //set compare match output mode
		 TCCR2 &= TIMER2_CTC_PWM_MODE_MASK;
		 TCCR2 |= (TIMER2_CTC_MODE_OUTPUT<<4);




		 //timer0 comp match interrupt enable
		 set_bit(TIMSK,OCIE2);



	#elif TIMER2_MODE==TIMER2_FAST_PWM_MODE
		    //initialize waveform generation mode to work as Fast PWM mode
		    set_bit(TCCR2,WGM20);
		    set_bit(TCCR2,WGM21);


		    //set compare match output mode
		    TCCR2 &= TIMER2_CTC_PWM_MODE_MASK;
		    TCCR2 |= (TIMER2_FAST_PWM_MODE_OUTPUT<<4);

	#elif TIMER2_MODE==TIMER2_PHASECORRECT_PWM_MODE
	    //initialize waveform generation mode to work as Phase correct PWM mode
	    set_bit(TCCR2,WGM20);
	    clear_bit(TCCR2,WGM21);



	    //set compare match output mode
	    TCCR2 &= TIMER2_CTC_PWM_MODE_MASK;
	    TCCR2 |= (TIMER2_PHASECORRECT_PWM_MODE_OUTPUT<<4);

	#else
	#error "wrong mode"
	#endif

}

void __vector_5(void) __attribute__((signal));
void __vector_5(void){
timer_ptr[TIMER2_ID]();
}

void __vector_4(void) __attribute__((signal));
void __vector_4(void){
timer_ptr[TIMER2_ID]();
}


/*********************************************************************************************************************/


void Timer_Int_Enable_Disable(U8 Timer_interrupt,U8 Enable_Disable){
	assign_bit(TIMSK,Timer_interrupt,Enable_Disable);
}

U32 Overflow_time_calculate(U8 Timer_Id){
    F32 count;
if(Timer_Id!=TIMER2_ID){

    if (Timerx_prescaler[Timer_Id]==TIMER0_NO_DIVISION){
    count=8000.0*Timerx_overflow_time[Timer_Id];
    }
    else if (Timerx_prescaler[Timer_Id]==TIMER0_DIVIDE_BY_8){
    count=(8000.0*Timerx_overflow_time[Timer_Id])/8;
    }
    else if (Timerx_prescaler[Timer_Id]==TIMER0_DIVIDE_BY_64){
    count=(8000.0*Timerx_overflow_time[Timer_Id])/64;
    }
    else if (Timerx_prescaler[Timer_Id]==TIMER0_DIVIDE_BY_256){
    count=(8000.0*Timerx_overflow_time[Timer_Id])/256;
    }
    else if (Timerx_prescaler[Timer_Id]==TIMER0_DIVIDE_BY_1024){
    count=(8000.0*Timerx_overflow_time[Timer_Id])/1024;
    }
  }

else if(Timer_Id==TIMER2_ID){
    if (Timerx_prescaler[Timer_Id]==TIMER2_NO_DIVISION){
    count=8000.0*Timerx_overflow_time[Timer_Id];
    }
    else if (Timerx_prescaler[Timer_Id]==TIMER2_DIVIDE_BY_8){
    count=(8000.0*Timerx_overflow_time[Timer_Id])/8;
    }
    else if (Timerx_prescaler[Timer_Id]==TIMER2_DIVIDE_BY_32){
    count=(8000.0*Timerx_overflow_time[Timer_Id])/32;
    }
    else if (Timerx_prescaler[Timer_Id]==TIMER2_DIVIDE_BY_64){
    count=(8000.0*Timerx_overflow_time[Timer_Id])/64;
    }
    else if (Timerx_prescaler[Timer_Id]==TIMER2_DIVIDE_BY_128){
    count=(8000.0*Timerx_overflow_time[Timer_Id])/128;
     }
    else if (Timerx_prescaler[Timer_Id]==TIMER2_DIVIDE_BY_256){
    count=(8000.0*Timerx_overflow_time[Timer_Id])/256;
    }
    else if (Timerx_prescaler[Timer_Id]==TIMER2_DIVIDE_BY_1024){
    count=(8000.0*Timerx_overflow_time[Timer_Id])/1024;
    }
  }


if(Timer_Id==TIMER1_ID){

	if(count>=65536){
	    count=count/65536;

	    TCNTX[Timer_Id]=(65536*(1-(count-(U32)count)));


	    return ((U32)count+1);
	   }
	   TCNTX[Timer_Id]=(65536-count);
	   return 1;
	}

if(count>=256){
    count=count/256;

    TCNTX[Timer_Id]=(256*(1-(count-(U32)count)));


    return ((U32)count+1);
   }
   TCNTX[Timer_Id]=(256-count);
   return 1;
}


void Overflow_restart_count(U8 Timer_Id){
	if(Timer_Id==TIMER0_ID){
	TCNT0=TCNTX[0];
	}
	else if(Timer_Id==TIMER1_ID){
		TCNT1=TCNTX[1];
	}
	else if(Timer_Id==TIMER2_ID){
		TCNT2=TCNTX[2];
	}
}

void set_comparematch_value(U8 Timer_Id,U8 ctc_value){
if(Timer_Id==TIMER0_ID){
		OCR0=ctc_value;
 }
else if(Timer_Id==TIMER2_ID){
	OCR2=ctc_value;
 }

}

void Timer1_set_comparematch_value(U8 Compare_Register ,U16 ctc_value){

if(Compare_Register==CMPA){
	OCR1A=ctc_value;
}
else if(Compare_Register==CMPB){
	OCR1B=ctc_value;
}

}



U8 Timer_callback(U8 Timer_Id,void(*ptr)(void)){
	U8 error_state=OK;

	if(ptr==NULL){
		error_state=NULL_POINTER;
		return error_state;
	}

	else{
	timer_ptr[Timer_Id]=ptr;
	}

return error_state;
}



#if TIMER1_USE_CMPB==1
U8 CompareB_callback(void(*ptr)(void)){
	U8 error_state=OK;

	if(ptr==NULL){
		error_state=NULL_POINTER;
		return error_state;
	}

	else{
	CompareB_ptr=ptr;
	}

return error_state;
}
#endif


