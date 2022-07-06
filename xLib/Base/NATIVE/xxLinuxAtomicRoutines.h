//---------------------------------------------------------------------------
#ifndef xxLinuxAtomicRoutinesH
#define xxLinuxAtomicRoutinesH
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
#include <linux/unistd.h>
#include <sys/syscall.h>
inline long atom_inc_and_fetch(long volatile* a){return __sync_add_and_fetch (a,1);}
inline long atom_dec_and_fetch(long volatile* a){return __sync_sub_and_fetch(a, 1);}
inline long atom_exchange(long volatile* a,long b){return __sync_val_compare_and_swap(a, *a, b);}
inline long atom_add_and_fetch(long volatile* a,long b){return __sync_add_and_fetch (a,b);}
inline long atom_sub_and_fetch(long volatile* a,long b){return __sync_sub_and_fetch (a,b);}
//------------------------------------------------------------------------------
/*inline long atom_val_compare_and_swap(
    volatile long *Destination,	// pointer to the destination pointer
    volatile long Exchange,	// the exchange value
    volatile long Comperand	// the value to compare
      ) {return __sync_val_compare_and_swap(Destination, *Destination, Exchange);}
*/
//-------------------------------------------
#endif
