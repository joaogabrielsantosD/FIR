#include <stdio.h>
#include <iostream>
#include "FIR.h"

using namespace std;

FIR bs;

int nin = 0;
float r = 2500;

int main () 
{   

   while (1)
   {
        int w = (int)bs.filt(r,0.6,0.6);
        cout << w << endl;
        nin++;
        if(nin==10000)
          break;
   }
   
    return 0;
}