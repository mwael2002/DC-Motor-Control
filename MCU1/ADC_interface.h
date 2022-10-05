/*
 * ADC_interface.h
 *
 *  Created on: Oct 9, 2021
 *      Author: mwael
 */

#ifndef ADC_INTERFACE_H_


#define ADC_CH_0 0
#define ADC_CH_1 1
#define ADC_CH_2 2
#define ADC_CH_3 3
#define ADC_CH_4 4
#define ADC_CH_5 5
#define ADC_CH_6 6
#define ADC_CH_7 7

#define TIMEOUT_STATE 3

typedef struct{
	U8   *Chain_Channel;
	U16 *Chain_Result;
	U8  Chain_Size;
	void (*Chain_Notification_Func)(void);
}ADC_Chain;

void ADC_init(void);
U8 ADC_Start_Conversion_Synch(U8 Channel,U16* post_result);
U8 ADC_Start_Conversion_Asynch(U8 Channel,U16* Post_Result,void (*ptr)(void));
U8 ADC_Start_Chain_Conversion_Asynch(ADC_Chain* Copy_Chain);
#endif /* ADC_INTERFACE_H_ */
