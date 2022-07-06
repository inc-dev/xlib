#ifndef xxAtomH
#define xxAtomH
//-------------------------------
#define FullAtomic

#ifdef FullAtomic
 #ifdef _WIN32
  #include "NATIVE/xxWindowsAtomicRoutines.h"
 #else
  #ifdef _LINUX
   #include "NATIVE/xxLinuxAtomicRoutines.h"
   //эта ветка не работает
  #else
   //#include "NATIVE/xxNoThreadAtomicRoutines.h"
   #include "NATIVE/xxLinuxAtomicRoutines.h"
  #endif
 #endif
#else
  #include "NATIVE/xxNoThreadAtomicRoutines.h"
#endif
//--------------
#ifdef _WIN32
#include <windows.h>
#endif
//-------------------------------
#include "xxTypes.h"
//-------------------------------
class TxAtom
 {
  public:
   long volatile Value;
   TxAtom(){Value=0;}
   TxAtom(long iValue){Value=iValue;}
   inline long LockedInc(){return atom_inc_and_fetch(&Value);}
   inline long LockedDec(){return atom_dec_and_fetch(&Value);}
   //inline long LockedCompareExchange(long Exchange,long Comperand)  {return atom_val_compare_and_swap(&Value,Exchange,Comperand);}
   inline long LockedExchange(long iValue)  {return atom_exchange(&Value,iValue);}
   inline long LockedExchangeAdd(long Increment)   {return atom_add_and_fetch(&Value,Increment);}
   inline long LockedExchangeSub(long Dicrement)   {return atom_sub_and_fetch(&Value,Dicrement);}
   inline long operator++(   ){return LockedInc()-1;}//prefix
   inline long operator++(int){return LockedInc();  }//postfix
   inline long operator--(   ){return LockedDec()+1;}
   inline long operator--(int){return LockedDec();  }
   inline TxAtom&operator=(long i){LockedExchange(i);return *this;}
   inline operator long(){return Value;}
 };
//---------------------------------------------------------------------------
#endif
