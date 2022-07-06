#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxSpinLock.h"
#include "xxDateTime.h"
//---------------------------------------------------------------------------
namespace XSPACE
{
// lock quickly if ms = 0, the infinite 
bool xSpinLock(TxAtom*Locker,int ms,int sleep_ms)
 {
  register long OldRes;
  int i=0;  double start=-1;
  do{
  OldRes = Locker->LockedExchange(SPINLOCK_BUSY);
  if(OldRes==SPINLOCK_FREE)return true;
  i++;
  if(i>10000)
   {
    if(start<0)start = xGetMilliSeconds()-sleep_ms;
    if(i>1000000)
     {
      i=0;
      xSleep(sleep_ms);
      if(ms!=0)
       {
        if(uint(xGetMilliSeconds()-start)>uint(ms))
         {
          xSpinUnLock(Locker);
          return false;
         }
       }
     }
   }
  }while(true);
 }

void xSpinUnLock(TxAtom*Locker)
 {
  Locker->LockedExchange(SPINLOCK_FREE);
 }
}
#ifndef __GNUC__
#pragma package(smart_init)
#endif


