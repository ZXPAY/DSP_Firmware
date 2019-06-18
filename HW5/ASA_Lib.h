/*===============ASA Series Library===============*/

/*****ReleaseDate*****/
//----/--/--

/*****Feature*****/

/*===Supported Module===*/
//ASA M128

/*================================================*/

#ifndef __ASA_H__
#define __ASA_H__

#include <avr\io.h>
#include <avr\interrupt.h>
#include <stdio.h>
#include <util\delay.h>

/**M128**/

char ASA_M128_set(void);

char M128_AComp_set(char LSByte, char Mask, char Shift, char Data);
char M128_AComp_fpt(char LSByte, char Mask, char Shift, char Data);
char M128_AComp_fgt(char LSByte, char Mask, char Shift, void *Data_p);
char M128_Acomp_isr(char Number, void (*function)(void));

char M128_DIO_set(char LSByte, char Mask, char Shift, char Data);
char M128_DIO_put(char LSByte, char Bytes, void *Data_p);
char M128_DIO_get(char LSByte, char Bytes, void *Data_p);
char M128_DIO_fpt(char LSByte, char Mask, char Shift, char Data);
char M128_DIO_fgt(char LSByte, char Mask, char Shift, void *Data_p);

char M128_EXT_set(char LSByte, char Mask, char Shift, char Data);
char M128_EXT_fpt(char LSByte, char Mask, char Shift, char Data);
char M128_EXT_fgt(char LSByte, char Mask, char Shift, void *Data_p);
char M128_EXT_isr(char Number, void (*function)(void));

char M128_TIM_set(char Lsbyte, char Mask, char Shift, char Data);
char M128_TIM_put(char LSbyte, char Bytes, void *Data_p);
char M128_TIM_get(char LSByte, char Bytes, void *Data_p);
char M128_TIM_fpt(char Lsbyte, char Mask, char Shift, char Data);
char M128_TIM_isr(char Number,char Cycle,char Phase, void (*function)(void));
char M128_TIM_isr_remove(char Number,  void (*function)(void));

char M128_TWI_set(char LSByte, char Mask,  char shift,char Data);
char M128_TWI_put(char LSByte, char Bytes, char *Data_p);
char M128_TWI_get(char LSByte, char Bytes, char *Data_p);
char M128_TWI_fpt( char LSByte, char Mask,  char shift, char Data);
char M128_TWI_fgt( char LSByte, char Mask,  char shift,  char *Data_p);
char M128_TWIM_trm(char OneReg, char TWIID, char RegAdd, char Bytes, void *Data_p);
char M128_TWIM_rec(char OneReg, char TWIID, char RegAdd, char Bytes, void *Data_p);
char M128_TWIM_ftm(char SLA,char OneReg, char RegAdd, char Mask, char shift, void *Data_p);
char M128_TWIM_frc(char SLA,char OneReg, char RegAdd, char Mask, char shift, char *Data_p);

char M128_UART_set( char LSbyte, char Mask, char Shift, void* Data_p);
char M128_UART_put( char LSbyte, char Bytes, void *Data_p);
char M128_UART_get( char LSbyte, char Bytes, void *Data_p);
char M128_UARTM_trm(char OneSLA, char OneReg, char UARTID, char RegAdd, char Bytes, void *Data_p);
char M128_UARTM_rec(char OneSLA, char OneReg, char UARTID, char RegAdd, char Bytes, void *Data_p);
char M128_UARTM_ftm(char OneSLA, char OneReg, char UARTID, char RegAdd, char Mask,  char shift, char* Data_p);
char M128_UARTM_frc(char OneSLA, char OneReg, char UARTID, char RegAdd, char Mask,  char shift, char* Data_p);

char M128_PWM_set(char LSByte, char Mask, char Shift, char Data);
char M128_PWM_fpt( char LSByte, char Mask,  char Shift, char Data);
char M128_PWM_put(char LSByte, char Bytes, void *Data_p);
char M128_PWM_fgt( char LSByte, char Mask,  char Shift, void *Data_p);
char M128_PWM_isr(char number,char cycle,char phase, void (*function)(void));

char M128_ADC_set(char LSByte, char Mask, char Shift, char Data);
char M128_ADC_get(char LSByte, char Bytes, void *Data_p);
char M128_ADC_fpt(char LSByte,char Mask,char Shift,char Data);
char M128_ADC_fgt(char LSByte,char Mask,char Shift,char *Data_p);
char M128_ADC_isr(char Number, void (*function)(void));

char M128_HMI_set(char LSBytes, char Mask, char shift, char Data);
char M128_HMI_put(int Bytes, char Type, void *Data_p);
char M128_HMI_get(int Bytes, void *Data_p);
char M128_HMI_Form_put(char *FormatString, int Bytes, void *Data_p);
char M128_HMI_Form_get(char *FormatString, int Bytes, void *Data_p);

char M128_SPI_set(char LSByte,char Mask,char Shift,char Data);
char M128_SPI_put(char LSByte,char Bytes,char *Data_p);
char M128_SPI_get(char LSByte,char Bytes,char *Data_p);
char M128_SPI_fpt(char LSByte,char Mask,char Shift,char Data);
char M128_SPI_fgt(char LSByte,char Mask,char Shift,char *Data_p);
char M128_SPI_swap(char Data);
char M128_SPI_trm(char OneReg,char RegAdd,char Bytes,void *Data_p);
char M128_SPI_rec(char OneReg,char RegAdd,char Bytes,void *Data_p);
char M128_SPI_frc(char OneReg,char RegAdd,char Mask,char Shift,char *Data_p);
char M128_SPI_ftm(char OneReg,char RegAdd,char Mask,char Shift,char *Data_p);

#endif
