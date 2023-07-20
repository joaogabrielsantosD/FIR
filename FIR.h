#ifndef FIR_H
#define FIR_H

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*You can change the size of the vetor if you needed*/
#define SIZE 2

class FIR {
    public:
    /*
        * "a" and "b" are the filter coefficients
        * Works as a linear combination between the values
    */
        float filt(float a, float b, float x);
    private:
        /*
            * Update the vetor
        */
        void move_vec(float *vetorAddr, int size, float value); 
};

float FIR::filt(float a, float b, float x)
{
    static float y_pass[SIZE] = {0,0}, x_pass[SIZE] = {0,0};

    float y = (a+b)*y_pass[0] - a*b*y_pass[1] + (1-a-b + a*b)*x_pass[1];
    
    move_vec(y_pass, SIZE, y);
    move_vec(x_pass, SIZE, x);

    return y;
};

void FIR::move_vec(float *vetorAddr, int size, float value)
{
    for (int k=size-1; k>0; k--)
    {
        *(vetorAddr+k) = *(vetorAddr+k-1);
    }

    *vetorAddr = value;
}

/*#define SIZE 2

const float a=0.8;
const float b=0.8;

float FIR(float x);
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
}
*/
#endif
