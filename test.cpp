#include <stdio.h>
#include "FIR.h"

using namespace std;

FIR as;

const float a=0.7,b=0.7;
float Hz=1000;

int main () 
{
    while (1)
    {
    
    float aspira = as.filt(a,b,Hz);

    printf("%f\n", aspira);

    }
}