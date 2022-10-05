#include "STD_Types.h"
#include "DIO_interface.h"
#include "USART_interface.h"
#include "ADC_interface.h"
#include "Ex_Interrupt_interface.h"
#include "GIE_interface.h"
#include "LCD_interface.h"

void application_init(void);
void switch_button(void);
void read_and_send_temp(void);
void fan_control(void);

int main()
 {
LCD_init();
    
application_init();
  
   while (1){
 
      read_and_send_temp();
       fan_control();

   }
   return 0;
 }
 
  void application_init(void){
    DIO_set_pin_direction(Group_D,DIO_Pin_0 ,INPUT);                                    // set RX of UART input pin
    DIO_set_pin_direction(Group_D,DIO_Pin_1 ,OUTPUT);                                // set TX of UART output pin
    
    DIO_set_pin_direction(Group_D,DIO_Pin_2 ,INPUT);                                    // set switch pin input
    DIO_set_pin_value(Group_D,DIO_Pin_2 ,HIGH);                                          // set switch pin high to enable pull up resistor
    
    DIO_set_pin_direction(Group_A,DIO_Pin_2 ,OUTPUT);                               // set fan pin output
     
    USART_init();                                                                                           // initialize UART
    ADC_init();                                                                                             // initialize ADC
 

    Ex_Int_set_level(Ex_Int_0,Ex_Int_Falling_edge);                                       // make Interrupt0 trigger falling edge (Pushing Switch)
    Ex_Int_call_back(&switch_button,Ex_Int_0);                                            // passing switch_button function to callback function of interrupts
    Ex_Int_Enable(Ex_Int_0);                                                                       // enable Interrupt0
    Global_Int_En_Dis(Global_Int_Enable);                                                   // enable global interrupt
   
    }
 
 void read_and_send_temp(void){
     U16 temp_reading;                                                                               // variable that stores temprature reading
    
     ADC_Start_Conversion_Synch(ADC_CH_1,& temp_reading);                   //Get reading of temprature sensor from channel 0 in ADC and save it in temp_reading variable
     
    /*
    temp_reading after ADC is the digital value
   maximum digital value is 1024 (10 bit resolution)
   maximum voltage is 5 V
    temp_reading -> 1023
    current volt   -> 5
    current volt= temp_reading*5/1023
   
    output of LM35 is 10 mV/ degree Celisus
    
    1 degree        -> 0.01 V
    current  temp -> current volt    
    
    current temp = current volt*100/1
    current temp = temp_reading*5*100/1023
    */
    
    temp_reading= temp_reading*5*100.0/1023.0;       
     USART_send_no(temp_reading);                                                                // sent temprature reading to MCU2
    }
 
void fan_control(void){

U32 motor_speed;                                                                                      // variable that holds a number that represents speed of motor (0->255) not the actual speed    

motor_speed=USART_receive_no();                                                             // recieve motor speed from MCU2

LCD_write_string_pos("Motor speed:",0,0);   
LCD_write_no_pos(motor_speed,0,12);    

   
 if(motor_speed>(0.7*255)){                                                                      // check if the motor speed is greater than 70% speed of the maximum speed
                                
    DIO_set_pin_value(Group_A,DIO_Pin_2,HIGH);                                     // fan is ON
    
    }
    
    else{
    DIO_set_pin_value(Group_A,DIO_Pin_2,LOW);                                     // fan is OFF   
       }
   
}
    
 void switch_button(void){
    static U8 switch_state=0;                                                                       // variable that holds next detection of interrupt of switch  (0->detect pushing) (1->detect releasing)
    if(switch_state==0){                                                                          // check if the next detection is pushing
    USART_send_no(200);                                                                        // send special code (200) to MCU2
    Ex_Int_set_level(Ex_Int_0,Ex_Int_Rising_edge);                                 // Make the interrupt detect rising edge
     switch_state=1;                                                                              // Make the next detection releasing
       }
     else if(switch_state==1){                                                                 // check if the next detection is releasing
     USART_send_no(300);                                                                     // send special code (300) to MCU2
	Ex_Int_set_level(Ex_Int_0,Ex_Int_Falling_edge);                              // Make the interrupt detect rising edge 
     switch_state=0;                                                                            // Make the next detection pushing
	  }
 }
 
