#include <stdio.h>
#include "FIR.h"

using namespace std;

FIR as;
FIR bs;

#define aa 0.6
#define bb 0.65
//const float a=0.7,b=0.7;
//float Hz=1000;
float r = 2500;

int main () 
{
    int s = bs.order(2);
    if (s)
    {
        printf("ok");
    } else {
        return -1;
    }
    
    while (1)
    {
    
    float test = bs.filt(aa,bb,r);
    printf("%d\n", (int)test);

    }
}