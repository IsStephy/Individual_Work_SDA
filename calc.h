#ifndef CALC_H
#define CALC_H

#include<stdio.h>
#include<stdlib.h>
const float Tmax = 40;
const float Tmin = 15;
const float Pmin = 2778;


float fara_stagiu_ori_mai_mic_de_5_ani (float Knt,float Tt);
float stagiu_complet (float Tt,float Vav,float Knt);
float diz_grad_1 (float Vav,float Tt);
float diz_grad_2 (float Vav,float Tt);
float diz_grad_3 (float Vav,float Tt);
float urmas (float Vav,float Tt);
#endif