#ifndef xxSpinLockH
#define xxSpinLockH
#include"xxAtom.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
#define SPINLOCK_FREE 0
#define SPINLOCK_BUSY 1
// lock quickly if ms = 0, the infinite
bool xSpinLock(TxAtom*,int ms=1000,int sleep_ms=10);
void xSpinUnLock(TxAtom*);
}
//------------------------------------------------------------------------------
#endif
