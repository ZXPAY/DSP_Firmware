#ifndef M128_DANNY_TIMER_H
#define M128_DANNY_TIMER_H

#define ChannelA 0
#define ChannelB 1
#define ChannelC 2

void setTimer0_CompareInterrupt(char OCR_Data, uint16_t prescalerLevel);
void openTimer0();
void closeTimer0();

void setTimer2_CompareInterrupt(char OCR_Data, uint16_t prescalerLevel);
void openTimer2();
void closeTimer2();

void setTimer1B_CompareInterrupt(uint16_t OCR_Data, uint16_t prescalerLevel);
void openTimer1B();
void closeTimer1B();

void openTimer3();
void closeTimer3();

uint8_t getTimer0PrescalerLevel(uint16_t prescalerLevel);
uint8_t getTimer123PrescalerLevel(uint16_t prescalerLevel);
void openWhichTimer(int whichTimer);
void closeWhichTimer(int whichTimer);

// PWM Function ********************************************** //
void setTimerPrescaler(char whichTimer, uint16_t prescalerLevel);
void setPWMTimer1Channel(char whichChannel);
void setTimer1Mode(char mode);
struct PeriodDutyCycleTransform{
	uint16_t Frequency;
	uint16_t ICRBuff;
	uint16_t Prescalar;
	float DutyCyclePercent;
}timerDutyCycle;
void setPWMFrequency(uint32_t freq);
void setPWMDutyCycle(char whichChannel, float dutyCycle);

#endif



