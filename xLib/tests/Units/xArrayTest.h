#ifndef xArrayTestH
#define xArrayTestH
#include "../../Base/xxArray.h"
#include "../../Base/xxSmallStr.h"
#include "../../Base/xxOperators.h"
#include "../../Base/xxDecodeStr.h"
#include "../../Base/Algorithms/xxPortion.h"
#include <stdio.h>

const char *ArrayTest();


class TestDones
 {
   static TxAtom DoneCount;
   static int Count;
   int Num;
   static int Dones[10000000];
   int Value;
  public:
   int Get(){return Num;}
   TestDones()
    {
     Count++;Init();
    }
   TestDones(const TestDones&t){Count++;Init();Value=t.Value;}
   TestDones(const int iValue){Count++;Init();Value=iValue;}
   int operator=(int i)
    {Value=i;return Value;}
   TestDones& operator=(const TestDones&i)
    {Value=i.Value;return *this;}
       operator int(){return Value;}
   ~TestDones()
     {
      Count--;
      Dones[Num]++;
     }
   static bool isBad()
    {
     if(Count)return true;
     for(int i=0;i<DoneCount.Value;i++)
      if(Dones[i]!=2)
       return true;
     return false;
    }
  protected:
   void Init()
    {
     Num=DoneCount.LockedInc()-1;
     if(Num>=10000000)
      printf("over\n");
     Dones[Num]=1;
    }

 };
#endif
