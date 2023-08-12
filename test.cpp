#include <stdio.h>
#include "FIR.h"

using namespace std;

FIR bs;

int nin = 0;
float r = 2500;

int main () 
{   
    while (1)
    {
        float test = bs.filt(r);
        printf("%d\n", (int)test);
        nin++; 

        if (nin==100)
        {
            break;
        }
    }
    return 0;
}