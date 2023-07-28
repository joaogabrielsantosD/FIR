#include <stdio.h>
#include "FIR.h"

using namespace std;

FIR bs;

#define a 0.2
#define b 0.25

int nin = 0;
float r = 2500;

int main () 
{   
    while (1)
    {
        float test = bs.filt(a,b,r);
        printf("%d\n", (int)test);
        nin++; 

        if (nin==100)
        {
            break;
        }
    }
}