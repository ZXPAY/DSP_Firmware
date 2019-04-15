#include "ASA_Lib.h"
#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>

enum{
    A = 0,
    B = 1,
    ON = true,
    OFF = false
};
#define LED_DDR DDRA
#define LED_PORT PORTA
#define LED_PIN PA0
#define SW1_DDR DDRA
#define SW1_INPUT PINA
#define SW1_PIN PA1
#define SW2_DDR DDRA
#define SW2_INPUT PINA
#define SW2_PIN PA2

// define state
#define STATE_CLOSE_LOOP 1
#define STATE_OPEN_LOOP  0

typedef struct twoSwitchStr{
    uint8_t state;
    uint8_t sw1;
    uint8_t sw2;
}twoSwitchStr;
#define initSwitchStruct {.state=0, .sw1=0, .sw2=0}

// void initSwitchStruct(twoSwitchStr *str);
void setupMySW(void);
void updateSwitchState(twoSwitchStr *str);
void setupMyLED(void);
void setLED(bool ON_OR_OFF);

int main(){
    ASA_M128_set();
    printf("start main code\n");
    twoSwitchStr mySwitchStr = initSwitchStruct;
    setupMyLED();
    while(true){
        updateSwitchState(&mySwitchStr);
        switch (mySwitchStr.state){
            case STATE_CLOSE_LOOP:
                setLED(ON);
                break;
            case STATE_OPEN_LOOP:
                setLED(OFF);
                break;
            default:
                break;
        }    
    }

    return 0;
}
void setupMySW(void){
    SW1_DDR &= ~(1<<SW1_PIN);
    SW2_DDR &= ~(1<<SW2_PIN);
}
void updateSwitchState(twoSwitchStr *str){
    if(SW1_INPUT & (1<<SW1_PIN)){
        str->sw1 = A;
    }
    else{
        str->sw1 = B;
    }
    if(SW2_INPUT & (1<<SW2_PIN)){
        str->sw2 = A;
    }
    else{
        str->sw2 = B;
    }
    if(str->sw1 == str->sw2){
        str->state = STATE_CLOSE_LOOP;
    }
    else{
        str->state = STATE_OPEN_LOOP;
    }
}
void setupMyLED(void){
    LED_DDR |= (1<<LED_PIN);
}
void setLED(bool ON_OR_OFF){
    if(ON_OR_OFF){
        LED_PORT |= (1<<LED_PIN);
    }
    else{
        LED_PORT &= ~(1<<LED_PIN);
    }
}
