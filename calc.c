#include<stdio.h>
#include<stdlib.h>
#include "calc.h"

float fara_stagiu_ori_mai_mic_de_5_ani (float Knt,float Tt){
    float P;
    P = Pmin * (Tt/(2*Tmin)) * Knt;
    return P;
}

float stagiu_complet (float Tt,float Vav,float Knt){
    float P;
    P =0.0135 * Tt * Vav;
    if (P < Pmin){
        P = Pmin * (Tt/(2*Tmin)) * Knt;
        if (P < Pmin){return P;} 
        return P;
    }
    return P;
}

float diz_grad_1 (float Vav,float Tt){
    float P;
    P = 0.42 * Vav + (Tt/Tmax) * Vav * 0.1;
    if (P< Pmin){
        P = Pmin*0.75;
    }
    return P;
}

float diz_grad_2 (float Vav,float Tt){
    float P;
    P = 0.35 * Vav + (Tt/Tmax) * Vav * 0.1;
    if (P< Pmin){
        P = Pmin*0.70;
    }
    return P;
}

float diz_grad_3 (float Vav,float Tt){
    float P;
    P = 0.20 * Vav + (Tt/Tmax) * Vav * 0.1;
    if (P< Pmin){
        P = Pmin*0.5;
    }
    return P;
}

float urmas (float Vav,float Tt){
    float P;
    P = 0.42 * Vav + (Tt/Tmax) * Vav * 0.1;
    if (P < Pmin){
        P = Pmin * 0.75;
    }
    return P;
}