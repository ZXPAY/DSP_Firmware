#include "ASA_Lib.h"
#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include "ss.h"
#include "ss.config"

void ss0_net(TypeOfSS *str_p);
void ss1_net(TypeOfSS *str_p);
void ss2_net(TypeOfSS *str_p);
void ss3_net(TypeOfSS *str_p);
void ss_net(TypeOfSS *str_p);


int main(){
    ASA_M128_set();

    TypeOfSS ss = SS_Init;
    printf("start main code\n");
    while(true){
        ss_net(&ss);
        printf("output is %f\n", ss.y);
        printf("=========================\n");
        _delay_ms(1000);
    }

    return 0;
}

void ss0_net(TypeOfSS *str_p){
    static bool fg = true;
    // input
    if(fg){
        str_p->ss_n[0].InF_p[0] = str_p->u;
        str_p->x = str_p->ss_n[0].InF_p[0];
        fg = false;
    }
    str_p->x = str_p->x;
}

void ss1_net(TypeOfSS *str_p){
    // state1
    str_p->ss_n[0].OutF_p[0] = str_p->ss_n[0].InF_p[0];
    str_p->ss_n[1].InF_p[0] = str_p->ss_n[0].OutF_p[0];
    str_p->x = str_p->ss_n[0].OutF_p[0];
}

void ss2_net(TypeOfSS *str_p){
    // state2
    str_p->ss_n[1].OutF_p[0] = str_p->ss_n[1].InF_p[0];
    str_p->ss_n[2].InF_p[0] = str_p->ss_n[1].OutF_p[0];
    str_p->x = str_p->ss_n[1].OutF_p[1];
}

void ss3_net(TypeOfSS *str_p){
    // state3
    str_p->ss_n[2].OutF_p[0] = str_p->ss_n[2].InF_p[0];
    str_p->x = str_p->ss_n[2].OutF_p[0];
}

void ss_net(TypeOfSS *str_p){
    ss0_net(str_p);
    printf("state is %f\n", str_p->x);
    ss1_net(str_p);
    printf("state is %f\n", str_p->x);
    ss2_net(str_p);
    printf("state is %f\n", str_p->x);
    ss3_net(str_p);
    printf("state is %f\n", str_p->x);
    str_p->y = 1*str_p->ss_n[0].OutF_p[0] + 1*str_p->ss_n[1].OutF_p[0] + 1*str_p->ss_n[2].OutF_p[0] + 1*str_p->u;
}

