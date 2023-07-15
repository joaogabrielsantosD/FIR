#ifndef FIR_H
#define FIR_H

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 2

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

#endif