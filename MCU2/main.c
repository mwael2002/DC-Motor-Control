#include <avr/delay.h>
#include "STD_Types.h"
#include "DIO_interface.h"
#include "Timer_interface.h"
#include "ADC_interface.h"
#include "USART_interface.h"
#include "LCD_interface.h"

/*
variable that holds the state of the motor if it will be controlled by potentiometer or it's speed will decrease gradually until it reaches zero
0: it;s the initial state, it will be controlled by potentiometer
1: decrease it's speed until it reaches zero
2: the motor has stopped after decreasing it's speed
*/
U8 motor_flag=0;

void application_init(void);
void leds_control(void);
void motor_control(void);

void main(void){

 LCD_init();
  
   
   application_init();
  
   while(1){
      
      leds_control();
     motor_control();
      
      }

  
}

void application_init(void){

   DIO_set_pin_direction(Group_D,DIO_Pin_0 ,INPUT);                                    // set RX of UART input pin
   DIO_set_pin_direction(Group_D,DIO_Pin_1 ,OUTPUT);                                // set TX of UART output pin
 /******************set three pins of leds OUTPUT******************/
   DIO_set_pin_direction(Group_B,DIO_Pin_5 ,OUTPUT);
   DIO_set_pin_direction(Group_B,DIO_Pin_6 ,OUTPUT);
   DIO_set_pin_direction(Group_B,DIO_Pin_7 ,OUTPUT);
 /************************************************************************/
   DIO_set_pin_direction(Group_D,DIO_Pin_7 ,OUTPUT);                                // set motor pin output
   
    USART_init();                                                                                            // Initialize UART
    ADC_init();                                                                                              // Initialize ADC
    Timer2_init();                                                                                           // Initialize Timer2
   
   }

void leds_control(void){
 U16 temp_reading;                                         // variable that stores temprature reading
   
   temp_reading=USART_receive_no();                  // recieve tempratue reading from UART
         
   if(temp_reading==200){                             // check on the special code of pushing the button
      motor_flag=1;       
LCD_write_no_pos(temp_reading,0,0);
	return; 
      }
      if(temp_reading==300){                              // check on the special code of releasing the button
      motor_flag=0;  
LCD_write_no_pos(temp_reading,1,0);

     return; 
       }
       
LCD_write_string_pos("Temprature:",0,0); 
LCD_write_no_pos(temp_reading,0,11);
       
 if(temp_reading<20){
 
    DIO_set_pin_value(Group_B,DIO_Pin_5 ,HIGH);                      //  Green ON
    DIO_set_pin_value(Group_B,DIO_Pin_6 ,LOW);                      // Yellow OFF
    DIO_set_pin_value(Group_B,DIO_Pin_7 ,LOW);                     // Red OFF
   }
  else  if((temp_reading>=20)&&(temp_reading<40)){
 
     DIO_set_pin_value(Group_B,DIO_Pin_6 ,HIGH);                     // Yellow ON
     DIO_set_pin_value(Group_B,DIO_Pin_5 ,LOW);                     //  Green OFF
     DIO_set_pin_value(Group_B,DIO_Pin_7 ,LOW);                     // Red OFF

   }
   else{
      DIO_set_pin_value(Group_B,DIO_Pin_7 ,HIGH);                     // Red ON
      DIO_set_pin_value(Group_B,DIO_Pin_5 ,LOW);                     //  Green OFF
      DIO_set_pin_value(Group_B,DIO_Pin_6 ,LOW);                     // Yellow OFF
      }
     

    
}

void motor_control(void){
  if(motor_flag==2){                              // check if the motor has stopped afterpushing the button
     USART_send_no(0);                         // send zero speed until the button is released (motor_flag=0)
  }
  else{
      static U8 motor_speed;                           // variable that holds a number that represents speed of motor (0->255) not the actual speed and it's static it's value is used during the whole program 
      
      if(motor_flag==0){                         // check if the motor will be controlled by potentiometer
      ADC_Start_Conversion_Synch(ADC_CH_0,&motor_speed);                  //Get reading of potentiometer from channel 0 in ADC and save it in speed variable
      set_comparematch_value(TIMER2_ID,motor_speed);                           //set compare match value to vary duty cycle
      USART_send_no(motor_speed);                                                           // send speed to MCU1
      }
       
   
       if(motor_flag==1){                      // check if the button is pushed
        motor_speed--;                                   // decrease motor speed by one each time the function is called in while(1) to make it decrease gradually
	set_comparematch_value(TIMER2_ID,motor_speed);         //set compare match value to vary duty cycle
	USART_send_no(motor_speed); 
         
	 if(motor_speed==0){                            // check if speed of motor is zero
	 motor_flag=2;     
	  }
       }
    } 
}
