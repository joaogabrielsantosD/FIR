/* Implemented in 2023 by João Gabriel, electronics coordinator of Mangue Baja 2023/24 */
#ifndef FIR_H
#define FIR_H

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* If you needed apply the filter two times */
#define double_filter

/*You can change the size of the vetor if you needed*/
#define SIZE 2


/* Can use only in one variable. Using the second variable the value of the static float has change */
class FIR {
    public:
    /*=======================================================================================================
        * "a" and "b" are the filter coefficients
        * The higher the value of the coefficient, the slower its update rate, but the stronger its filter.
        * Filter based on convolution between previous inputs.
        * Can suport only for order equal 2
    ========================================================================================================*/
        float filt(float a, float b, float x);
    private:
    /*=========================
        * Update the vetor
        * Second filter
    =========================*/
        void move_vec(float *vetorAddr, int size, float value); 
        float filtfilt(float A, float B, float x2);
        float double_y;
        bool flag=false;
};


float FIR::filt(float a, float b, float x)
{
    #ifdef double_filter
        flag = true;
    #endif

    static float y_pass[SIZE] = {0,0}, x_pass[SIZE] = {0,0};

    float y = (a+b)*y_pass[0] - a*b*y_pass[1] + (1-a-b + a*b)*x_pass[1];
    
    move_vec(y_pass, SIZE, y);
    move_vec(x_pass, SIZE, x);

    (flag) ? double_y = filtfilt(a,b,y) : double_y = y; 

    return double_y;
    //return y;
};

void FIR::move_vec(float *vetorAddr, int size, float value)
{
    for (int k=size-1; k>0; k--)
    {
        *(vetorAddr+k) = *(vetorAddr+k-1);
    }

    *vetorAddr = value;
};

float FIR::filtfilt(float A, float B, float x2)
{
    static float y2_pass[SIZE] = {0,0}, x2_pass[SIZE] = {0,0};

    float y2 = (A+B)*y2_pass[0] - A*B*y2_pass[1] + (1-A-B + A*B)*x2_pass[1];
    
    move_vec(y2_pass, SIZE, y2);
    move_vec(x2_pass, SIZE, x2);

    return y2;
}

/*
#ifndef FIR_H
#define FIR_H

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//You can change the size of the vetor if you needed
#define SIZE 2

const float a = 0.5; 
const float b = 0.55;

float FIR(float x);
float FIR2(float xx);
void desloca_vetor(float *vetorAddr, int tam, float valor);

float FIR(float x)
{
    static float y_pass[SIZE] = {0,0}, x_pass[SIZE] = {0,0};
    float y = (a+b)*y_pass[0] - a*b*y_pass[1] + (1-a-b + a*b)*x_pass[1];
    desloca_vetor(y_pass, SIZE, y);
    desloca_vetor(x_pass, SIZE, x);
    return y;
}

void desloca_vetor(float *vetorAddr, int tam, float valor)
{
    for (int k=tam-1; k>0; k--)
    {
        *(vetorAddr+k) = *(vetorAddr+k-1);
    }

    *vetorAddr = valor;
};

float FIR2(float xx)
{
    static float yy_pass[SIZE] = {0,0}, xx_pass[SIZE] = {0,0};
    float yy = (a+b)*yy_pass[0] - a*b*yy_pass[1] + (1-a-b + a*b)*xx_pass[1];
    desloca_vetor(yy_pass, SIZE, yy);
    desloca_vetor(xx_pass, SIZE, xx);
    return yy;
};

float FIR3(float xxx)
{
    static float yyy_pass[SIZE] = {0,0}, xxx_pass[SIZE] = {0,0};
    float yyy = (a+b)*yyy_pass[0] - a*b*yyy_pass[1] + (1-a-b + a*b)*xxx_pass[1];
    desloca_vetor(yyy_pass, SIZE, yyy);
    desloca_vetor(xxx_pass, SIZE, xxx);
    return yyy;
};
#endif
*/
#endif
