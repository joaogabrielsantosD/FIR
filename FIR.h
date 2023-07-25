/* Implemented in 2023 by João Gabriel, electronics coordinator of Mangue Baja 2023/24 */
#ifndef FIR_H
#define FIR_H

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
        bool order(int ord);
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

bool FIR::order(int ord)
{
    if (ord==1)
    {
        return true;
    } 

    else if (ord==2)
    {
        flag=true;
        return true;
    }

    else if (ord>2 || ord<1)
    {
        return false;
    }
}

float FIR::filt(float a, float b, float x)
{
    static float y_pass[SIZE] = {0,0}, x_pass[SIZE] = {0,0};

    float y = (a+b)*y_pass[0] - a*b*y_pass[1] + (1-a-b + a*b)*x_pass[1];
    
    move_vec(y_pass, SIZE, y);
    move_vec(x_pass, SIZE, x);

    (flag) ?  double_y = filtfilt(a,b,y) : double_y = y; 

    return double_y;
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

#endif
