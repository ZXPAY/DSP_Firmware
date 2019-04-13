#ifndef SS_H
#define SS_H

typedef struct TypeOfSS_unit{
    float InF_p[1];
    float OutF_p[1];
}TypeOfSS_unit;

typedef struct TypeOfSS{
    TypeOfSS_unit ss_n[3];
    float A, B, C, D, x, y;
    float u;
    float OutF_p[1];
}TypeOfSS;



#endif
