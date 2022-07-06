//---------------------------------------------------------------------------
#ifndef xxNoThreadAtomicRoutinesH
#define xxNoThreadAtomicRoutinesH
//---------------------------------------------
inline long atom_inc_and_fetch(long volatile* a){return ++(*a);}
inline long atom_dec_and_fetch(long volatile* a){return --(*a);}
inline long atom_exchange(long volatile* a,long b){return *a = b;}
inline long atom_add_and_fetch(long volatile* a,long b){return *a+=b;}
inline long atom_sub_and_fetch(long volatile* a,long b){return *a-=b;}
//------------------------------------------------------------------------------
inline long atom_val_compare_and_swap(
    volatile long *Destination,	// pointer to the destination pointer
    volatile long Exchange,	// the exchange value
    volatile long Comperand	// the value to compare
      ) {if(*Destination==Comperand)*Destination=Exchange;return *Destination;}
#endif
