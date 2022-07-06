#ifndef xxPtrH
#define xxPtrH
#include "xxTypes.h"
#include "xxTypeInfo.h"
#include "xxAtom.h"
#include <assert.h>
#include <stddef.h>
//------------------------------------------------------------------------------
namespace XSPACE
{
template<typename T>struct TxInternalTicketMem;
template<typename T>class RefPTR;
template<typename T>
class PTR
 {
  public:
   inline PTR(){Data = TxInternalTicketMem<T>::NullTicketMem();Data->Lock(); }
   inline PTR(T*obj){Data = new TxInternalTicketMem<T>(obj,1,0);}
   inline PTR(const PTR&P){Data = P.Data;Data->Lock(); }
          PTR(const RefPTR<T>&P)
           {
            if(P.Data->Lock()>1)Data = P.Data;
             else
              {
               P.Data->UnLock();Data = TxInternalTicketMem<T>::NullTicketMem();Data->Lock();
              }
           }
   inline ~PTR(){Data->UnLock();}

   inline const PTR& operator=(const int&i) {if(i==0){Data->UnLock();Data = TxInternalTicketMem<T>::NullTicketMem();Data->Lock();}return *this;}
   inline const PTR& operator=(T*obj) {Data->UnLock();Data = new TxInternalTicketMem<T>(obj,1,0); return *this;}
   inline const PTR& operator=(const PTR&P) {P.Data->Lock();Data->UnLock();Data = P.Data;return *this;}
   inline const PTR& operator=(const RefPTR<T>&P)
    {
     Data->UnLock();
     if(P.Data->Lock()>1)Data = P.Data;
      else
       {
        P.Data->UnLock();Data = TxInternalTicketMem<T>::NullTicketMem();Data->Lock();
       }
     return *this;
    }
   inline operator T*()const{return Data->PTR;}
   inline T*ToPoint()const {return Data->PTR;}
   inline operator long()const  {return (long)Data->PTR;}
//   inline int ToInt()const  {return (int)Data->PTR;}
   inline long ToLong()const  {return (long)Data->PTR;}
   inline T* operator->()const{return Data->PTR;}
   inline bool isEmpty()const{return Data->PTR==0;}
   friend class RefPTR<T>;
  protected:
   TxInternalTicketMem<T> * Data;
 };
//------------------------------------------------------------------------------
template<typename T>
class RefPTR
 {
  public:
   inline RefPTR(){Data = TxInternalTicketMem<T>::NullTicketMem();Data->RefLock(); }
   inline RefPTR(const PTR<T>&P){Data = P.Data;Data->RefLock(); }
   inline RefPTR(const RefPTR<T>&P){Data = P.Data;Data->RefLock(); }
   inline ~RefPTR(){Data->RefUnLock();}
   inline const RefPTR& operator=(const PTR<T>&P) {Data->RefUnLock();Data = P.Data;Data->RefLock();return *this;}
   inline const RefPTR& operator=(const RefPTR<T>&P) {P.Data->RefLock();Data->RefUnLock();Data = P.Data;return *this;}
//   inline int ToInt()const  {return (int)Data->PTR;}
   inline long ToLong()const  {return (long)Data->PTR;}

   friend class PTR<T>;
  protected:
   TxInternalTicketMem<T> * Data;
 };
//------------------------------------------------------------------------------
template<typename T>
 struct TxInternalTicketMem
  {
   TxAtom RefCount;    //the number of links of strong pointers
   TxAtom RefRefCount; //the number of links weak pointers (link)
   T* PTR;             //real pointer
   inline TxInternalTicketMem(T*iPTR=0,int iRefCount=0,int iRefRefCount=0)
    :RefCount(iRefCount),RefRefCount(iRefRefCount),PTR(iPTR)
     {
      #ifdef _DEBUG
      Count()++;
      #endif
     }
   #ifdef _DEBUG
   static TxAtom& Count()
   {
    static TxAtom C=0;
    return C;
   }
   ~TxInternalTicketMem(){Count()--;}
   #endif
   inline static TxInternalTicketMem* NullTicketMem()
    {
     static TxInternalTicketMem TicketMem(0,1,1);
     return &TicketMem;
    }
   inline int Lock() { return RefCount.LockedInc(); }
   void UnLock()
    {
     if(RefCount.LockedDec()<1)
      {
       if(this!=NullTicketMem())
        {
         delete PTR; PTR=0;
         if(RefRefCount.Value<1)
            delete this;
        }
       else assert(0);
      }
    }
   inline int RefLock() { return RefRefCount.LockedInc(); }
   void RefUnLock()
    {
     if(RefRefCount.LockedDec()<1)
      {
       if(this!=NullTicketMem())
        {
         if(RefCount.Value<1)
          delete this;
        }
       else assert(0);
      }
    }
  };
}
template<typename T>
  inline bool operator==(const XSPACE::PTR<T> &p1,const XSPACE::PTR<T> &p2){return p1.ToPoint()==p2.ToPoint();}
template<typename T>
  inline bool operator!=(const XSPACE::PTR<T> &p1,const XSPACE::PTR<T> &p2){return p1.ToPoint()!=p2.ToPoint();}
template<typename T>
  inline bool operator==(const XSPACE::RefPTR<T> &p1,const XSPACE::RefPTR<T> &p2){return p1.ToLong()==p2.ToLong();}
template<typename T>
  inline bool operator!=(const XSPACE::RefPTR<T> &p1,const XSPACE::RefPTR<T> &p2){return p1.ToLong()!=p2.ToLong();}
//------------------------------------------------------------------------------
#endif
