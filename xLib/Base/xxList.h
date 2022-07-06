#ifndef xxListH
#define xxListH
#include <new>
#include <assert.h>
#include <stdlib.h>
#include "xxTypes.h"
#include "xxTypeInfo.h"
#include "xxAtom.h"
#include "xxDataAccess.h"
namespace XSPACE
{
#define ManyMemory
#ifdef ManyMemory  // x2
#define xMinCapacity 2
#define ReCalcCapacity(NewCap) (  ((NewCap+NewCap)&( (uint(-1))-(xMinCapacity/2-1) ))+xMinCapacity  )
#else              // x1.5 
#define ReCalcCapacity(NewCap) (NewCap+(NewCap>>1)+xMinCapacity)
#endif
//#define isSimple(T) (xGetTypeInfo<T>::Type==xTypeSimple||xGetTypeInfo<T>::Type==xTypeStaticPtr||xGetTypeInfo<T>::Type==xTypeStaticClassPtr)
#define isSimple(T) (int(xGetTypeInfo<T>::Type)==int(xTypeSimple)||int(xGetTypeInfo<T>::Type)==int(xTypeStaticPtr)||int(xGetTypeInfo<T>::Type)==int(xTypeStaticClassPtr))
//------------------------------------------------------------------------------
template<typename T>struct TxListData;
//------------------------------------------------------------------------------
template<typename T>
class List :public TxUpdateBidirectionalAccess
 {
  public:
   inline List(){Data = TxListData<T>::GetSingleEmptyData();Data->Lock();}
   inline List(const List&a){a.Data->Lock(); Data = a.Data;};
   inline List(const int&capacity){Data = TxListData<T>::CreateNewData(capacity);};
   inline~List(){Data->UnLock();};
   //---------------------------------------------------------------------------
   inline void Add(const T& item){PrepareUpdate(Data->TopIndex+1);Data->Add(item);}
   inline void Insert(int pos,const T& item){PrepareUpdate(Data->TopIndex+1); Data->Insert(pos,item);}
   int Delete(int from,int to){Unique();return Data->Delete(from,to);}
   int Delete(int index){Unique();return Data->Delete(index,index);}
   inline void Clear(){if(First())Delete(First(),Last());}
   //---------------------------------------------------------------------------
   //--- sequential access -----------------------------------------------
   inline bool isValidIndex(int i)const{return i>0&&i<=Data->TopIndex&&Data->Items[i-1].next>=0;}
   inline int First()const{return Data->FirstIndex;}
   inline int Next(int i)const
    {
     #ifdef _DEBUG
     if(!isValidIndex(i))abort();
     #endif
     return Data->Items[i-1].next;
    }
   inline int Prev(int i)const
    {
     #ifdef _DEBUG
     if(!isValidIndex(i))abort();
     #endif
     return Data->Items[i-1].prev;
    }
   inline int Last()const{return Data->LastIndex;}
   inline T & Get(int i){if(dword(i-1)>=dword(Data->Capacity)||Data->Items[i-1].next==-1)assert(0);Unique();return Data->Items[i-1].Value;}

   inline int Size(){return Data->TopIndex - Data->HolesCount;}
   inline bool isEmpty()const{return Size()==0;}
   void Reserve(int NewCapacity,bool MayClear=false);
   inline void PrepareUpdate(int NewCapacity=0,bool MayClear=false)
    {
     if(Data->RefCount.Value>1)
      {
       if(NewCapacity==0) NewCapacity = ReCalcCapacity(Size());
       else  NewCapacity = ReCalcCapacity(NewCapacity);
       Reserve(NewCapacity,MayClear);
      }
     else
      if(Data->Capacity<NewCapacity)
        Reserve(ReCalcCapacity(NewCapacity),MayClear);
    }
   inline void Unique(bool MayClear=false){if(Data->RefCount.Value>1)Reserve(Data->Capacity,MayClear);}
   #ifndef isValidTest
   protected:
   #endif
   TxListData<T> *Data;
 };
template<typename T>
struct TxListData
 {
   //---------------------------------------------------------------------------

   TxAtom RefCount;   //reference count
   int Capacity;      //all cells
   int TopIndex;      //top free cell
   int HolesCount;    //number of holes
   int FirstFreeIndex;//first free cell
   int FirstIndex;    //the index of the first element
   int LastIndex;     //the index of the last element
   struct TDataItem{T Value; int prev,next;} Items[0];
   //TxListDataItem<T> Items[];
   TxListData()
    {RefCount.Value=1; Capacity=0; TopIndex=0; HolesCount=0; FirstFreeIndex=0; FirstIndex=0; LastIndex=0;}
   //~TxListData(){}
   //---------------------------------------------------------------------------
   friend class List<T>;
   //---------------------------------------------------------------------------
   inline void Lock()
    {
     RefCount.LockedInc();
    }
   //---------------------------------------------------------------------------
   void DeleteObjects(int from,int to)
    {
     while(from)
      {
       Items[from-1].Value.~T();
       if(from==to)break;
       from = Items[from-1].next;
      }
    }
   //---------------------------------------------------------------------------
   inline void UnLock()
     {
      if(RefCount.LockedDec()<1)
      {
       if(this!=GetSingleEmptyData())
        {
         if(!isSimple(T))
          DeleteObjects(FirstIndex,LastIndex);
         free(this);
        }
        else assert(0);
      }
     }
   //---------------------------------------------------------------------------
   inline static TxListData<T>*GetSingleEmptyData()
    {
     static TxListData<T> SingleEmptyData; //
     return &SingleEmptyData;
    }
   //---------------------------------------------------------------------------
   static TxListData*CreateNewData(int NewCapacity);
   //---------------------------------------------------------------------------
   inline int GetNewSpace()
    {
     int Res = FirstFreeIndex;
     int NextFirstFreeIndex = Items[FirstFreeIndex].prev;
     if(FirstFreeIndex!=TopIndex){FirstFreeIndex = NextFirstFreeIndex;HolesCount--;}
      else{TopIndex++; FirstFreeIndex = TopIndex; }
     return Res;
    }
   inline void DeleteSpace(int i)
    {
       HolesCount++;
       Items[i].prev = FirstFreeIndex;
       FirstFreeIndex = i;
       Items[i].next = -1;//sign a blank cell
    }
   void Add(const T & item)
    {
     if(LastIndex==0) //still empty
      {
        TopIndex = FirstFreeIndex = 1;
        new(&Items[0].Value)T(item);
        FirstIndex = LastIndex = 1;
        Items[0].prev = Items[0].next = 0;
        HolesCount = 0;
      }else  //not an empty list
      {
       int NewItem = GetNewSpace();
       new(&Items[NewItem].Value)T(item);
       Items[NewItem].prev = LastIndex;
       Items[NewItem].next = 0;
       Items[LastIndex-1].next = NewItem+1;
       LastIndex = NewItem+1;
      }
    }
   void Insert(int pos,const T& item)
    {
     if(LastIndex==0) //still empty
      {
        TopIndex = FirstFreeIndex = 1;
        new(&Items[0].Value)T(item);
        FirstIndex = LastIndex = 1;
        Items[0].prev = Items[0].next = 0;
        HolesCount = 0;
      }else
      {
       int NewItem = GetNewSpace();
       new(&Items[NewItem].Value)T(item);
       if(pos==FirstIndex)FirstIndex = NewItem+1;
       Items[NewItem].prev = Items[pos-1].prev;
       Items[NewItem].next = pos;
       if(Items[pos-1].prev)Items[Items[pos-1].prev-1].next = NewItem+1;
       Items[pos-1].prev = NewItem+1;
      }
    }
   //---------------------------------------------------------------------------
   int Delete(int from,int to)
    {
     if(to==0||from==0)return 0;
//     #ifdef _DEBUG
     if(from>TopIndex||to>TopIndex)return 0;
     if(Items[from-1].next<0||Items[to-1].next<0)return 0;//unused blocks
//     #endif
     //excluded from the list of fragment
     if(from==FirstIndex)FirstIndex = Items[to-1].next;
     if(to==LastIndex) LastIndex = Items[from-1].prev;
     if(Items[from-1].prev)Items[Items[from-1].prev-1].next = Items[to-1].next;
     if(Items[to-1].next)Items[Items[to-1].next-1].prev = Items[from-1].prev;
     int res = Items[to-1].next;
     while(to)
      {
       // free the object
       Items[to-1].Value.~T();
       // remember the holes
       int prev = Items[to-1].prev;
       DeleteSpace(to-1);
       //----------------------
       if(from==to)break;
       to = prev;
      }
     return res;
    }
   //---------------------------------------------------------------------------
   void Add(TxListData*ListData) //so far, then it is necessary to optimize
    {
      int index = ListData->FirstIndex;
      while(index)
       {
        Add(ListData->Items[index-1].Value);
        index = ListData->Items[index-1].next;
       }
    }
 };
//------------------------------------------------------------------------------
template<typename T>
void List<T>::Reserve(int NewCapacity,bool MayClear)
 {
  if(Data->RefCount.Value>1)
   {
    int len = Size();
    if(NewCapacity<xMinCapacity)NewCapacity = xMinCapacity;
    if(!MayClear&&NewCapacity<len)NewCapacity = len;
    TxListData<T>*NewData = TxListData<T>::CreateNewData(NewCapacity);
    if(!MayClear)NewData->Add(Data);
    TxListData<T>*OldData = Data;
    Data = NewData;
    OldData->UnLock();
   }else
   if(Data->Capacity<NewCapacity)
    {
     if(MayClear)
      {
       TxListData<T>*NewData = TxListData<T>::CreateNewData(NewCapacity);
       TxListData<T>*OldData = Data;
       Data = NewData;
       OldData->UnLock();                   
      }else
      {
       Data = (TxListData<T>*)realloc(Data,(NewCapacity+1)*sizeof(typename TxListData<T>::TDataItem)+sizeof(TxListData<T>));
       assert(Data);
       Data->Capacity = NewCapacity;
      }
    }
 }
//------------------------------------------------------------------------------
template<typename T>
TxListData<T>*TxListData<T>::CreateNewData(int NewCapacity)
 {
  if(NewCapacity<xMinCapacity)NewCapacity=xMinCapacity;
  TxListData<T> * NewData = (TxListData<T>*)malloc((NewCapacity+1)*sizeof(typename TxListData<T>::TDataItem)+sizeof(TxListData<T>));
  assert(NewData);
  new(NewData)TxListData<T>();
  NewData->Capacity = NewCapacity;
  return NewData;
 }
#undef isSimple
#undef ReCalcCapacity
}
//------------------------------------------------------------------------------
#endif
