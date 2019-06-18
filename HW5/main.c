#include "ASA_Lib.h"
#include "LIB/M128_Danny_Timer.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define PWM_NUMBERS 2
#define TIMER_RESOLUTION 0.0001   // 0.0001 ms

volatile uint8_t **PWM_PORT;
volatile uint8_t **PWM_DDR;
volatile uint8_t PWM_PIN_NUM[PWM_NUMBERS];

typedef struct PWM_Paramers{
    float period;              // period (s)
    uint16_t duty_cycle;       // 0~100
    uint16_t shift_angle;      // 度
    volatile uint8_t **port;    // Data output port
    volatile uint8_t **ddr;     // Data register
    volatile uint8_t *pin_num; // Pin number
    uint32_t one_period_CNT;
    uint32_t cntH;
    uint32_t cntL;
    uint32_t temp[3];
    uint16_t lag_cnt;
}PWM_TYPE;

typedef struct PWM{
    PWM_TYPE pwm_para[PWM_NUMBERS];
    float timer_resolution;
    uint8_t *nextTask;
}PWM;

void initMyPWM(PWM* pwm);
void updateMyPWM(PWM *pwm);
void setPWMParameters(PWM *pwm, uint16_t whichPWM, float period, uint16_t duty, uint16_t shift_angle);

PWM myPWM;

ISR(TIMER0_COMP_vect){
    updateMyPWM(&myPWM);
}

int main(void){
    ASA_M128_set();
    initMyPWM(&myPWM);
    setPWMParameters(&myPWM, 0, 0.02, 50, 0);
    setPWMParameters(&myPWM, 1, 0.015, 50, 0);
    setTimer0_CompareInterrupt(16, 64);
    openTimer0();
    
    uint16_t which_pwm = 0;
    uint16_t duty = 0;
    uint16_t shift_angle;
    float period = 0;
    
    while(true){
        printf("enter which PWM\n");
        scanf("%d", &which_pwm);
        printf("enter period (second)\n");
        scanf("%f", &period);
        printf("enter duty cycle\n");
        scanf("%d", &duty);
        printf("enter shift angle (degree)\n");
        scanf("%d", &shift_angle);
        
        if(which_pwm < PWM_NUMBERS){
            setPWMParameters(&myPWM, which_pwm, period, duty, shift_angle);
        }
        
        for(uint8_t i=0;i<PWM_NUMBERS;i++){
            printf("DDRA:%d\n", DDRA);
            printf("period[%d]:%f\n", i, myPWM.pwm_para[i].period);
            printf("duty_cycle[%d]:%d\n", i, myPWM.pwm_para[i].duty_cycle);
            printf("one_period_CNT[%d]:%ld\n", i, myPWM.pwm_para[i].one_period_CNT);
            printf("cntH[%d]:%ld\n", i, myPWM.pwm_para[i].cntH);
            printf("cntL[%d]:%ld\n", i, myPWM.pwm_para[i].cntL);
            printf("shift_angle[%d]:%d\n", i, myPWM.pwm_para[i].shift_angle);

            printf("=======================\n");
        }
    }

}

void initMyPWM(PWM* pwm){
    PWM_PORT = (volatile uint8_t **)malloc(PWM_NUMBERS);
    PWM_DDR = (volatile uint8_t **)malloc(PWM_NUMBERS);

    for(uint8_t i=0;i<PWM_NUMBERS;i++){
        PWM_PORT[i] = &PORTA;
        PWM_DDR[i] = &DDRA;
        PWM_PIN_NUM[i] = i;
        PWM_DDR[i][0] |= (1 << PWM_PIN_NUM[i]);
        PWM_PORT[i][0]  &= ~(1 << PWM_PORT[i][0]);

        pwm->timer_resolution = TIMER_RESOLUTION;
        pwm->pwm_para[i].period = 0.02;
        pwm->pwm_para[i].duty_cycle = 50;
        pwm->pwm_para[i].shift_angle = 0;
        pwm->pwm_para[i].ddr = PWM_DDR;
        pwm->pwm_para[i].pin_num = &(PWM_PIN_NUM[0]);
        pwm->pwm_para[i].port = PWM_PORT;
        pwm->pwm_para[i].one_period_CNT = (uint32_t)((float)pwm->pwm_para[i].period/TIMER_RESOLUTION);
        pwm->pwm_para[i].cntH = (uint32_t) ((float)pwm->pwm_para[i].one_period_CNT*pwm->pwm_para[i].duty_cycle/100);
        pwm->pwm_para[i].cntL = pwm->pwm_para[i].one_period_CNT - pwm->pwm_para[i].cntH;
        pwm->pwm_para[i].temp[0] = pwm->pwm_para[i].cntH;
        pwm->pwm_para[i].temp[1] = pwm->pwm_para[i].cntL;
        pwm->pwm_para[i].temp[2] = 0;
        pwm->pwm_para[i].lag_cnt = ((float)pwm->pwm_para[i].shift_angle/180.0*pwm->pwm_para[i].one_period_CNT/2);
    }
}

volatile uint32_t w = 0;

void updateMyPWM(PWM *pwm){
    for(uint8_t i=0;i<PWM_NUMBERS;i++){
        // High
        if(pwm->pwm_para[i].temp[0] != 0){
            if(pwm->pwm_para[i].shift_angle == 0){
                pwm->pwm_para[i].port[i][0] |= (1 << pwm->pwm_para[i].pin_num[i]);
                pwm->pwm_para[i].temp[0]--;
            }
            else{
                if(pwm->pwm_para[i].lag_cnt > pwm->pwm_para[i].temp[2]){
                    pwm->pwm_para[i].temp[2]++;
                }
                else{
                    pwm->pwm_para[i].port[i][0] |= (1 << pwm->pwm_para[i].pin_num[i]);
                    pwm->pwm_para[i].temp[0]--;
                }
            }
        }
        // Low
        else if(pwm->pwm_para[i].temp[1] != 0){
            pwm->pwm_para[i].port[i][0] &= ~(1 << pwm->pwm_para[i].pin_num[i]);
            pwm->pwm_para[i].temp[1]--;
        }
        else{
            pwm->pwm_para[i].temp[0] = pwm->pwm_para[i].cntH;
            pwm->pwm_para[i].temp[1] = pwm->pwm_para[i].cntL;
        }
    }
}

void setPWMParameters(PWM *pwm, uint16_t whichPWM, float period, uint16_t duty, uint16_t shift_angle){
    pwm->pwm_para[whichPWM].period = period;
    pwm->pwm_para[whichPWM].duty_cycle = duty;
    pwm->pwm_para[whichPWM].shift_angle = shift_angle;
    pwm->pwm_para[whichPWM].one_period_CNT = (uint32_t)((float)pwm->pwm_para[whichPWM].period/TIMER_RESOLUTION);
    pwm->pwm_para[whichPWM].cntH = (uint32_t) ((float)pwm->pwm_para[whichPWM].one_period_CNT*pwm->pwm_para[whichPWM].duty_cycle/100);
    pwm->pwm_para[whichPWM].cntL = (pwm->pwm_para[whichPWM].one_period_CNT - pwm->pwm_para[whichPWM].cntH);
    pwm->pwm_para[whichPWM].temp[0] = pwm->pwm_para[whichPWM].cntH;
    pwm->pwm_para[whichPWM].temp[1] = pwm->pwm_para[whichPWM].cntL;
    pwm->pwm_para[whichPWM].temp[2] = 0;
    pwm->pwm_para[whichPWM].lag_cnt = ((float)pwm->pwm_para[whichPWM].shift_angle/180.0*pwm->pwm_para[whichPWM].one_period_CNT/2);
}


