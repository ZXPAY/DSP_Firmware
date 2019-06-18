#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include "M128_Danny_Timer.h"

// ########################################## //
// Timer0 8 bits
void setTimer0_CompareInterrupt(char OCR_Data, uint16_t prescalerLevel){
    TCCR0 |= 1<<WGM01;    // CTC Mode
    TCCR0 |= getTimer0PrescalerLevel(prescalerLevel);
    TCNT0 = 0;
    OCR0 = OCR_Data;
    TIMSK |= (1<<OCIE0);
}
void openTimer0(){
    TIMSK |= (1<<OCIE0);
    sei();
}
void closeTimer0(){
    TIMSK &= ~(1<<OCIE0);
    cli();
}

// Timer2 8 bits
void setTimer2_CompareInterrupt(char OCR_Data, uint16_t prescalerLevel){
    TCCR2 |= 1<<WGM21;    // CTC Mode
    TCCR2 |= getTimer123PrescalerLevel(prescalerLevel);
    TCNT2 = 0;
    OCR2 = OCR_Data;
}
void openTimer2(){
    TIMSK = 1<<OCIE2;
    sei();
}
void closeTimer2(){
    TIMSK &= ~(1<<OCIE2);
    cli();
}
// ########################################## //

// ########################################## //
// Timer1 16 bits
void setTimer1B_CompareInterrupt(uint16_t OCR_Data, uint16_t prescalerLavel){ 
    TCCR1B |= 1 << WGM12;   // CTC mode
    TCCR1B |= getTimer123PrescalerLevel(prescalerLavel);
    TCNT1 = 0; 
    OCR1A = OCR_Data; 
    TIMSK |= (1<<OCIE1B);
} 
void openTimer1B(){
    TIMSK |= (1<<OCIE1B);
    sei();
}
void closeTimer1B(){
    TIMSK &= ~(1<<OCIE1B);
    cli();
}

// Timer3 16 bits
void setTimer3B_CompareInterrupt(uint16_t OCR_Data, uint16_t prescalerLevel){ 
    TCCR3B |= 1 << WGM32;   // CTC mode
    TCCR3B |= getTimer123PrescalerLevel(prescalerLevel);
    TCNT3 = 0; 
    OCR3A = OCR_Data; 
} 
void openTimer3B(){
    TIMSK |= (1<<OCIE3B);
    sei();
}
void closeTimer3B(){
    TIMSK &= ~(1<<OCIE3B);
    cli();
}
// ########################################## //

uint8_t getTimer0PrescalerLevel(uint16_t prescalerLevel){
    switch(prescalerLevel){
        case 1:
            return 1;
        break;
        case 8:
            return 2;
        break;
        case 32:
            return 3;
        break;
        case 64:
            return 4;
        break;
        case 128:
            return 5;
        break;
        case 256:
            return 6;
        break;
        case 1024:
            return 7;
        break;
        default:
            printf("Warning !!! No prescaler lavel found !!! => return 4\n");
            return 4;
        break;
    }
}

uint8_t getTimer123PrescalerLevel(uint16_t prescalerLevel){
    switch(prescalerLevel){
        case 1:
            return 1;
        break;
        case 8:
            return 2;
        break;
        case 64:
            return 3;
        break;
        case 256:
            return 4;
        break;
        case 1024:
            return 5;
        break;
        default:
            printf("Warning !!! No prescalerLevel found !!! => return 4\n");
            return 4;
        break;
    }
}

void openWhichTimer(int whichTimer){
    switch(whichTimer){
        case 0:
            openTimer0();
        break;
        case 1:
            openTimer1B();
        break;
        case 2:
            openTimer2();
        break;
        case 3:
            openTimer3B();
        break;
        default:
            printf("No timer found ...\n");
        break;
    }
}
void closeWhichTimer(int whichTimer){
    switch(whichTimer){
        case 0:
            closeTimer0();
        break;
        case 1:
            closeTimer1B();
        break;
        case 2:
            closeTimer2();
        break;
        case 3:
            closeTimer3B();
        break;
        default:
            printf("No timer found ...\n");
        break;
    }
}

void setTimerPrescaler(char whichTimer, uint16_t prescalerLevel){
	switch(whichTimer){
		case 0:
			TCCR0 &= ~(0b00000111);
			TCCR0 |= getTimer0PrescalerLevel(prescalerLevel);
		break;
		case 1:
			TCCR1B &= ~(0b00000111);
			TCCR1B |= getTimer123PrescalerLevel(prescalerLevel);
			timerDutyCycle.Prescalar = prescalerLevel; 
		break;
		case 2:
			TCCR2 &= ~(0b00000111);
			TCCR2 |= getTimer123PrescalerLevel(prescalerLevel);
		break;
		case 3:
			TCCR3B &= ~(0b00000111);
			TCCR3B |= getTimer123PrescalerLevel(prescalerLevel);
		break;
	}
}
void setPWMTimer1Channel(char whichChannel){
	switch(whichChannel){
		case ChannelA:
			TCCR1A &= ~(1<<COM1A0);
			TCCR1A |= (1<<COM1A1);
			DDRB |= (1<<PB5);
		break;
		case ChannelB:
			TCCR1A &= ~(1<<COM1B0);
			TCCR1A |= (1<<COM1B1);
			DDRB |= (1<<PB6);
		break;
		case ChannelC:
			TCCR1A &= ~(1<<COM1C0);
			TCCR1A |= (1<<COM1C1);
			DDRB |= (1<<PB7);
		break;
	}
}
void setTimer1Mode(char mode){
	switch(mode){
		case 0:
			TCCR1A &= ~(1<<WGM10) & ~(1<<WGM11);
			TCCR1B &= ~(1<<WGM12) & ~(1<<WGM13);
		break;
		case 14: // fast PWM
			TCCR1A &= ~(1<<WGM10);
			TCCR1A |= (1<<WGM11);
			TCCR1B |= (1<<WGM12) | (1<<WGM13);
		break;
		case 15: // fast PWM
			TCCR1A |= (1<<WGM10) | (1<<WGM11);
			TCCR1B |= (1<<WGM12) | (1<<WGM13);
		break;
	}
}

void setPWMFrequency(uint32_t freq){
	timerDutyCycle.Frequency = freq;
	timerDutyCycle.ICRBuff = (11059200)/(timerDutyCycle.Prescalar*freq) - 1;
	ICR1 = timerDutyCycle.ICRBuff;
}
void setPWMDutyCycle(char whichChannel, float dutyCycle){
	timerDutyCycle.DutyCyclePercent = dutyCycle;
	switch(whichChannel){
		case ChannelA:
			OCR1A = ((float)timerDutyCycle.ICRBuff * dutyCycle / 100);
		break;
		case ChannelB:
			OCR1B = ((float)timerDutyCycle.ICRBuff * dutyCycle / 100);
		break;
		case ChannelC:
			OCR1C = ((float)timerDutyCycle.ICRBuff * dutyCycle / 100);
		break;
	}
}


