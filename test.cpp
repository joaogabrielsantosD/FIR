#include <stdio.h>
#include <iostream>
#include "FIR.h"

using namespace std;

FIR bs;
const float a=0.6, b=0.6;

int nin = 0;
float r = 2500;

int main () 
{   
  while (1)
  {
  cout << (int)bs.filt(r,a,b) << endl;
  nin++;
  if(nin==10000)
    break;
  }
   
  return 0;
}