//---------------------------------------------------------------------------
#ifndef xxWindowsAtomicRoutinesH
#define xxWindowsAtomicRoutinesH
#include <windows.h>
inline long atom_inc_and_fetch(long volatile* a){return InterlockedIncrement(a);}
inline long atom_dec_and_fetch(long volatile* a){return InterlockedDecrement(a);}
inline long atom_exchange(long volatile* a,long b){return InterlockedExchange(a,b);}
inline long atom_add_and_fetch(long volatile* a,long b){return InterlockedExchangeAdd(a,b);}
inline long atom_sub_and_fetch(long volatile* a,long b){return InterlockedExchangeAdd(a,-b);}
//------------------------------------------------------------------------------
inline long atom_val_compare_and_swap(
    volatile long *Destination,	// pointer to the destination pointer
    volatile long Exchange,	// the exchange value
    volatile long Comperand	// the value to compare
      ) {return InterlockedCompareExchange(Destination,Exchange,Comperand);}
//»—œŒÀ‹«”ﬁ“—ﬂ ¬»ÕƒŒ¬€≈:
// LONG InterlockedIncrement(LONG* lpAddend);
// LONG InterlockedDecrement(LONG* lpAddend);
//---------------------------------------------
//PVOID InterlockedCompareExchange(
//    PVOID *Destination,	// pointer to the destination pointer
//    PVOID Exchange,	// the exchange value
//    PVOID Comperand	// the value to compare
//   );
//---------------------------------------------
//LONG InterlockedExchange(
//    LPLONG Target,	// address of 32-bit value to exchange
//    LONG Value 	// new value for the LONG value pointed to by Target
//   );
//---------------------------------------------
//LONG InterlockedExchangeAdd (
//    PLONG Addend,	// pointer to the addend
//    LONG Increment	// increment value
//   );
//---------------------------------------------------------------------------
#endif
