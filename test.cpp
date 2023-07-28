#include <stdio.h>
#include "FIR.h"

using namespace std;

FIR bs;

#define a 0.6
#define b 0.65

float r = 2500;

int main () 
{   
    while (1)
    {
        float test = bs.filt(a,b,r);
        printf("%d\n", (int)test);
    }
}