//------------------------------------------------------------------------------
#ifndef xxArrayH
#define xxArrayH
//------------------------------------------------------------------------------
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <new>
#include "xxTypes.h"
#include "xxTypeInfo.h"
#include "xxAtom.h"
#include "xxDataAccess.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
#define ManyMemory
#ifdef ManyMemory  // x2 - fast
#define ReCalcCapacity(NewCap) (  ((NewCap+NewCap)&( (uint(-1))-(xMinCapacity/2-1) ))+xMinCapacity  )
#else              // x1.5 - ekonom
#define ReCalcCapacity(NewCap) (NewCap+(NewCap>>1)+xMinCapacity)
#endif
#define isSimple(T) (int(xGetTypeInfo<T>::Type)==int(xTypeSimple)||int(xGetTypeInfo<T>::Type)==int(xTypeStaticPtr)||int(xGetTypeInfo<T>::Type)==int(xTypeStaticClassPtr))
template<typename T>struct TxArrayData;
template<typename T>class  TxWrapArrayData;
//------------------------------------------------------------------------------
template<typename T>
class Array:public TxUpdateMonolithAccess
 {
  public:
   inline Array(){Data = TxArrayData<T>::GetSingleEmptyData();Data->Lock();};
   inline Array(const Array&a){a.Data->Lock(); Data = a.Data;};
   inline Array(const int&capacity){Data = TxArrayData<T>::CreateNewData(capacity);};
   inline Array(const T*Items,int Count) {Data = TxArrayData<T>::CreateNewData(Count);Data->Add(Items,Count);}
   inline ~Array(){Data->UnLock();};
   //---------------------------------------------------------------------------
   template<class U>
   inline Array(const U&a){TypeInit(a,(U*)0,this);}

   template<class U,size_t Count>
   inline Array(const U(&Items)[Count])
    {
     Data = TxArrayData<T>::CreateNewData(Count-xIsChar<T>::Yes);
     Data->Add(Items,(long)(Count));
    }
   #ifndef __BORLANDC__ 
   template<size_t Count>
   inline Array(const char(&Items)[Count])
    {
     Data = TxArrayData<T>::CreateNewData(Count);
     Data->Add(Items,strlen(Items));
    }
    #endif 
   //---------------------------------------------------------------------------
   inline void Assign(const Array&a){if(a.Data!=Data){Data->UnLock();a.Data->Lock();Data = a.Data;}};
   inline void Assign(const T*Items,int Count) {PrepareUpdate(Count,true);Data->Clear();Data->Add(Items,Count);}
   //---------------------------------------------------------------------------
   template<class U>
   inline void Assign(const U&a) {TypeAssign(a,(U*)0,this);}
   template<class U,size_t Count>
   inline void Assign(const U(&Items)[Count]){Assign(Items,(long)(Count-xIsChar<T>::Yes));}
   template<size_t Count>
   inline void Assign(const char(&Items)[Count]){Assign(Items,strlen(Items));}
   
   //---------------------------------------------------------------------------
   template<class U>
   inline const Array& operator=(const U&a){Assign(a);return *this;}
   inline const Array& operator=(const Array&a) {Assign(a);return *this;}
   //---------------------------------------------------------------------------
   inline void Clear(){Unique(true);Data->Clear();}
   inline int Delete(int pos){if((uint)(pos-1)>=(uint)(Data->Len))return pos;Unique();return Data->Delete(pos-1,pos-1)+1;}
   inline int Delete(int pos,int pos_end){if((uint)(pos-1)>=(uint)(Data->Len)||pos>pos_end)return pos;Unique();return Data->Delete(pos-1,pos_end-1)+1;}
   //---------------------------------------------------------------------------
   inline void Add(const T& obj){PrepareUpdate(Data->Len+1);Data->Add(obj);}
   inline void Add(const T*Items,int count){PrepareUpdate(Data->Len+count);Data->Add(Items,count);};
   inline void AddItems(int count){PrepareUpdate(Data->Len+count);Data->AddSimpleItems(count);};
   //---------------------------------------------------------------------------
   template<class U>
   inline void Add(const U& a){TypeAdd(a,(U*)0,this);}
   template<class U,size_t Count>
   inline void Add(const U(&Items)[Count]){TypeAddC(Items,Count,this); }
   inline void operator+=(const Array& a){ Add(a);}
   inline void operator+=(const char* cc){Add(cc);}
   inline void operator+=(const char c){Add(c);}
   //---------------------------------------------------------------------------
   inline void Insert(int pos,const T&obj)
     {
      if((uint)(pos-1)>(uint)(Data->Len))return;
      PrepareUpdate(Data->Len+1);
      Data->Insert(pos-1,obj);
     }
   inline void Insert(int pos,const T*obj,int count)
     {
      if((uint)(pos-1)>(uint)(Data->Len))return;
      PrepareUpdate(Data->Len+count);
      Data->Insert(pos-1,obj,count);
     }
   inline void InsertItems(int pos,int count)
     {
      if((uint)(pos-1)>(uint)(Data->Len))return;
      PrepareUpdate(Data->Len+count);
      Data->InsertSimpleItems(pos-1,count);
     }
   //---------------------------------------------------------------------------
   template<class U>
   inline void Insert(int pos,const U&a) {TypeInsert(pos,a,(U*)0,this);}
   template<class U,size_t Count>
   inline void Insert(int pos,const U(&Items)[Count]) {TypeInsertC(pos,Items,Count,this);}
   //---------------------------------------------------------------------------
   inline       T & operator[](int i) {if(dword(i-1)>=(dword)Data->Len)assert(0);Unique();return Data->Data[i-1];}
   inline const T & operator[](int i)const {if(dword(i-1)>=dword(Data->Len))assert(0);return Data->Data[i-1];}
   //получить полюбому, безопасное получение символов
   inline T Take(int i)const{if(dword(i-1)>=dword(Data->Len)){static T Er(0);return Er;}return Data->Data[i-1];}
   //для последовательного доступа
   inline T       & Get(int i)     {if(dword(i-1)>=dword(Data->Len))assert(0);Unique();return Data->Data[i-1];}
   inline T const & Get(int i)const{if(dword(i-1)>=dword(Data->Len))assert(0);return Data->Data[i-1];}
   inline void Set(int i,const T&obj){if(dword(i-1)>=dword(Data->Len))return;Unique();Data->Data[i-1]=obj;}
   #ifdef _DEBUG
    //slowly, safely
   inline T       & QGET(int i)     {if(dword(i-1)>=dword(Data->Len)||Data->RefCount.Value>1)assert(0);return Data->Data[i-1];}
   inline T const & QGET(int i)const{if(dword(i-1)>=dword(Data->Len))assert(0);return Data->Data[i-1];}
   #define QSET Set
   #else
    //fast and dangerous operation for QSET cause Unique ();
    inline T       & QGET(int i)     {return Data->Data[i-1];}
    inline T const & QGET(int i)const{return Data->Data[i-1];}
    inline void QSET(int i,const T&obj){Data->Data[i-1]=obj;}
   #endif
   //--- sequential access -----------------------------------------------
   inline int First()const{if(Size()>0)return 1;else return 0;}
   inline int Next(int i)const{i++;if(i>Size())return 0;else return i;}
   inline int Prev(int i)const{i--;if(i<0)return 0;else return i;}
   inline int Last()const{return Size();}
   inline bool isValidIndex(int i){return i>0&&i<=Size();}
   //---------------------------------------------------------------------------
   inline T*GetItems()const{return Data->Data;}
   inline int Size()const{return Data->Len;}
   inline bool isEmpty()const{return Data->Len==0;}
   inline int Capacity()const{return Data->Capacity;}
   inline int RefCount()const{return Data->RefCount.Value;}
   inline const T* c_str()const
     { 
      STATIC_CHECK(xIsStringItem<T>::Yes);
      register int i = Data->Len;
      if(i>0)
       {Data->Data[i]=0;return Data->Data;}
      else
       {static T end; end=0; return &end;}
     }
   //---------------------------------------------------------------------------
   inline void SetSize(int NewSize){PrepareUpdate(NewSize);Data->SetSize(NewSize);}
   void Reserve(int NewCapacity,bool MayClear=false);
   inline void PrepareUpdate(int NewCapacity=0,bool MayClear=false)
    {
     if(Data->RefCount.Value>1)
      {
       if(NewCapacity==0) NewCapacity = ReCalcCapacity(Data->Len);
       else  NewCapacity = ReCalcCapacity(NewCapacity);
       Reserve(NewCapacity,MayClear);
      }
     else
      if(Data->Capacity<NewCapacity)
        Reserve(ReCalcCapacity(NewCapacity),MayClear);
    }
   inline void Unique(bool MayClear=false){if(Data->RefCount.Value>1)Reserve(Data->Capacity,MayClear);}
   inline void Pack(){Array<T> a(*this);PrepareUpdate();}
//   #ifndef _DEBUG                       
//    TxWrapArrayData<T> Data;  //for debug
//   #else
//  protected:
    TxArrayData<T> *Data;     //to relise
//   #endif
  protected:
   //---------------------------------------------------------------------------
   inline void TypeInit(char*a,char**,Array<char>*){int len=strlen(a); Data = TxArrayData<T>::CreateNewData(len); Data->Add(a,len);}
   inline void TypeInit(const char*a,const char**,Array<char>*){int len=strlen(a); Data = TxArrayData<T>::CreateNewData(len); Data->Add(a,len);}
   //--- containers ---
   template<class U>
   inline void TypeInit(const U&a,TxMonolithAccess*,Array<char>*)
     {Data = TxArrayData<T>::CreateNewData(a.Size());Data->Add(a.GetItems(),a.Size());}
   //---------------------------------------------------------------------------
   inline void TypeAssign(const T&obj,char*,Array<char>*){PrepareUpdate(1,true);Data->Clear();Data->Add(T(obj));}//this operation is only for arrays of characters
   inline void TypeAssign(char*a,char**,Array<char>*){Assign(a,strlen(a));}
   inline void TypeAssign(const char*a,const char**,Array<char>*){Assign(a,strlen(a));}
   //--- containers ---
   template<class U,class O>
   inline void TypeAssign(const U&a,TxMonolithAccess*,O*)
     {U b(a);  PrepareUpdate(b.Size(),true);Data->Clear();Data->Add(b.GetItems(),b.Size());}
   //---------------------------------------------------------------------------
   inline void TypeAdd(const int&obj,int*,Array<T>*) {Add((T)obj);}
   template<class U,class O>
   inline void TypeAdd(const U &obj,char**,O*){Add(T(obj));}
   inline void TypeAdd(char*a, char**,Array<char>*) {Add(a,strlen(a));}
   inline void TypeAdd(const char*a,const char**,Array<char>*){Add(a,strlen(a));}
    //the same type of elements
   inline void TypeAddC(const T*Items,size_t Count,Array<T>*){Add(Items,(long)(Count-xIsChar<T>::Yes));}
    // wrong type of elements
   template<class U>
   inline void TypeAddC(const U*Items,size_t Count,Array<T>*){Add(T(Items,Count-xIsChar<U>::Yes));}
   //--- containers ---
   template<class U,class O>
   inline void TypeAdd(const U&a,const TxMonolithAccess*,O*)
     {PrepareUpdate(Data->Len+a.Size());Data->Add(a.GetItems(),a.Size());}
   //---------------------------------------------------------------------------
   inline void TypeInsert(int pos,const T&obj,int*,Array<T>*){Insert(pos,(T)obj);}
   template<class U,class O>
   inline void TypeInsert(int pos,const U &obj,char**,O*){Insert(pos,T(obj));}
   inline void TypeInsert(int pos,char*a, char**,Array<char>*) {Insert(pos,a,strlen(a));}
   inline void TypeInsert(int pos,const char*a,const char**,Array<char>*) {Insert(pos,a,strlen(a));}
    //the same type of elements
   inline void TypeInsertC(int pos,const T*Items,size_t Count,Array<T>*){Insert(pos,Items,(long)(Count-xIsChar<T>::Yes));}
    // wrong type of elements
   template<class U>
   inline void TypeInsertC(int pos,const U*Items,size_t Count,Array<T>*){Insert(T(pos,Items,Count-xIsChar<U>::Yes));}
   //---  ---
   template<class U,class O>
    inline void TypeInsert(int pos,const U&a,TxMonolithAccess*,O*)
     {
      if(pos>Data->Len+1||pos<1)return;
      U b(a);
      PrepareUpdate(Data->Len+b.Size());
      Data->Insert(pos-1,b.GetItems(),b.Size());
     }
 };
//------------------------------------------------------------------------------
template<typename T>
class TxWrapArrayData
 {
   public:
   inline operator TxArrayData<T>*()const{return ((TxArrayData<T>*)(long(Items)-sizeof(TxArrayData<T>)));}
   inline TxArrayData<T>* operator->()const{return ((TxArrayData<T>*)(long(Items)-sizeof(TxArrayData<T>)));}
   inline void operator = (TxArrayData<T>*PArrayData){Items = (T*)(long(PArrayData)+sizeof(TxArrayData<T>));}
   inline void operator = (const TxWrapArrayData&a){Items = a.Items;}
   T* Items;
 };
template<typename T> inline bool operator != (const TxWrapArrayData<T>&a,const TxWrapArrayData<T>&b){return a.Items != b.Items;}
template<typename T> inline bool operator == (const TxWrapArrayData<T>&a,const TxWrapArrayData<T>&b){return a.Items == b.Items;}
//------------------------------------------------------------------------------
template<typename T>
struct TxArrayData
  {
     #ifndef _DEBUG
    protected:
     #endif
     //-------------------------------------------------------------------------
     TxAtom RefCount;
     int Capacity;
     int Len;
     T Data[0];
     //-------------------------------------------------------------------------
    protected:
     friend class Array<T>;
     //-------------------------------------------------------------------------
     inline void Lock()
      {
       RefCount.LockedInc();
      }
     //-------------------------------------------------------------------------
     inline void UnLock()
       {
        if(RefCount.LockedDec()<1)
        {
         if(this!=GetSingleEmptyData())
          {
           if(!isSimple(T))
            DeleteObjects(0,Len-1);
           free(this);
          }
          else assert(0);
        }
       }
     //-------------------------------------------------------------------------
     static TxArrayData*CreateNewData(int NewCapacity);
     //-------------------------------------------------------------------------
     TxArrayData()
      {
       RefCount.Value=1; Capacity=0; Len=0;
      }
     //-------------------------------------------------------------------------
     inline static TxArrayData<T>*GetSingleEmptyData()
      {
       static TxArrayData<T> SingleEmptyData; //blank plug
       return &SingleEmptyData;
      }
     //-------------------------------------------------------------------------
     void DeleteObjects(int from,int to)
      {
       for(int i=from;i<=to;i++)
        Data[i].~T();
      }
     //-------------------------------------------------------------------------
     void InstallSimpleItems(int from,int to)
      {
       for(int i=from;i<=to;i++)new(&Data[i])T();
      }
     //-------------------------------------------------------------------------
     void Install(int pos,const T* items,int iLen)
       {
         if(isSimple(T))
          memcpy(Data+pos,items,iLen*sizeof(T));
         else
          for(int i=0;i<iLen;i++)
           new(&Data[i+pos])T(items[i]);
       }
     //-------------------------------------------------------------------------
     inline void Clear()
      {
       if(!isSimple(T))
        DeleteObjects(0,Len-1);
       Len=0;
      }
     //-------------------------------------------------------------------------
     inline void Add(const T&item)
       {
        if(!isSimple(T))
          new(&Data[Len])T(item);
        else
         Data[Len]=item;
        Len++;
       }
     //-------------------------------------------------------------------------
     void Add(const T*items,const int AddLen)
      {
       if(items&&AddLen)
        {
         if(!isSimple(T))
          for(int i=0;i<AddLen;i++)
           new(&Data[Len+i])T(items[i]);
         else
          memcpy(&Data[Len],items,AddLen*sizeof(T));
         Len+=AddLen;
        }
      }
     //-------------------------------------------------------------------------
     void AddSimpleItems(const int AddLen)
      {
         if(!isSimple(T))
           for(int i=0;i<AddLen;i++)
             new(&Data[Len+i])T();
         Len+=AddLen;
      }
     //-------------------------------------------------------------------------
     inline void Move(int from,int to,int count)
      {
       memmove(&Data[to],&Data[from],count*sizeof(T));
      }
     //-------------------------------------------------------------------------
     int Delete(int pos,int pos_end)
       {
        if(pos_end+1>=Len)
         {
          if(!isSimple(T))
            DeleteObjects(pos,Len-1);
          Len=pos;
          return -1;
         }
        else
         {
          if(!isSimple(T))
            DeleteObjects(pos,pos_end);
          Move(pos_end+1,pos,Len-pos-1);
          Len=Len-pos_end+pos-1;
          return pos;
         }
       }
     //-------------------------------------------------------------------------
     inline void Insert(int pos,const T&item)
       {
        Move(pos,pos+1,Len-pos);
        new(&Data[pos])T(item);
        Len++;
       }
     //-------------------------------------------------------------------------
     inline void Insert(int pos,const T* items,int count)
       {
        Move(pos,pos+count,Len-pos);
        Install(pos,items,count);
        Len+=count;
       }
     //-------------------------------------------------------------------------
     void InsertSimpleItems(int pos,int count)
       {
        Move(pos,pos+count,Len-pos);
        if(!isSimple(T))
          for(int i=0;i<count;i++)
            new(&Data[pos+i])T();
        Len+=count;
       }
     //-------------------------------------------------------------------------
     inline void SetSize(int NewSize)
      {
       if(isSimple(T))
        Len=NewSize;
       else
        {
         if(Len>NewSize)DeleteObjects(NewSize,Len-1);
         else
         if(Len<NewSize) InstallSimpleItems(Len,NewSize-1);
         Len=NewSize;
        }
      }
  };
//------------------------------------------------------------------------------
template<typename T>
void Array<T>::Reserve(int NewCapacity,bool MayClear)
 {
  if(Data->RefCount.Value>1)
   {
    if(NewCapacity<xMinCapacity)NewCapacity = xMinCapacity;
    TxArrayData<T>*NewData = TxArrayData<T>::CreateNewData(NewCapacity);
    if(MayClear)NewData->Len = 0;else NewData->Len = Data->Len;
    if(NewCapacity<NewData->Len) NewData->Len = NewCapacity;
    if(NewData->Len)NewData->Install(0,Data->Data,NewData->Len);
    TxArrayData<T>*OldData = Data;
    Data = NewData;
    OldData->UnLock();
   }else
   if(Data->Capacity<NewCapacity)
    {
     if(MayClear)
      {
       TxArrayData<T>*NewData = TxArrayData<T>::CreateNewData(NewCapacity);
       TxArrayData<T>*OldData = Data;
       Data = NewData;
       OldData->UnLock();
      }else
      {
       Data = (TxArrayData<T>*)realloc(Data,(NewCapacity+1)*sizeof(T)+sizeof(TxArrayData<T>));
       assert(Data);
       Data->Capacity = NewCapacity;
      }
    }
 }
//------------------------------------------------------------------------------
template<typename T>
TxArrayData<T>*TxArrayData<T>::CreateNewData(int NewCapacity)
 {
  if(NewCapacity<xMinCapacity)NewCapacity=xMinCapacity;
  TxArrayData<T> * NewData = (TxArrayData<T>*)malloc((NewCapacity+1)*sizeof(T)+sizeof(TxArrayData<T>));
  assert(NewData);
  NewData->RefCount.Value = 1;
  NewData->Capacity = NewCapacity;
  NewData->Len = 0;
  return NewData;
 }
//------------------------------------------------------------------------------
typedef Array<char> Str;
#undef isSimple
#undef ReCalcCapacity
}

#endif

