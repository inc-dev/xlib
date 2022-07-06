#pragma hdrstop
#include "xThreadTest.h"
#include "../../Utils\xxThread.h"
#include "../../base\xxDateTime.h"
using namespace XSPACE;
//------------------------------------------------------------------------------
class TxThreadTest:public TxThread
 {
  public:
   int i;
   TxThreadTest(){i=0;}
   virtual void Execute()
    {
      while(i<=5)
       {
        xSleep(100);
        i++;
       }
    }
 };
const char *ThreadTest()
 {
   const int ArraySize = 100;
   TxThreadTest t[ArraySize];
   for(int i=0;i<ArraySize;i++)
    {
      t[i].Start();
    }
   xSleep(400);
   for(int i=0;i<ArraySize;i++)
    {
      t[i].Break();
    }
   for(int i=0;i<ArraySize;i++)
    {
      t[i].Start();
    }
   xSleep(700);
   for(int i=0;i<ArraySize;i++)
    {
      t[i].Break();
    }
  return 0;
 }

#pragma package(smart_init)
