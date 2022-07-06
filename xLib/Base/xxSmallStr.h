#ifndef xxSmallStrH
#define xxSmallStrH
#include "xxTypes.h"
#include <string.h>
#include <assert.h>
#include "xxDataAccess.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
class SmallStr:public TxMonolithAccess
 {
  public:
   //---------------------------------
   inline byte Size()const{return Len;}
   inline void Clear(){Data[0]=0;Len=0;Shift=0;}
   inline void Assign(const char c){Shift=0;Data[0]=c;Data[1]=0;Len = 1;}
   void Assign(const char*s);
   inline void Assign(const SmallStr& ss)
    {
     memcpy(Data,ss.Data,MaxSize+1);

    /*((dword*)Data)[0]=((dword*)ss.Data)[0];
    ((dword*)Data)[1]=((dword*)ss.Data)[1];
    ((dword*)Data)[2]=((dword*)ss.Data)[2];
    ((dword*)Data)[3]=((dword*)ss.Data)[3];
    ((dword*)Data)[4]=((dword*)ss.Data)[4];
    ((dword*)Data)[5]=((dword*)ss.Data)[5];
    ((dword*)Data)[6]=((dword*)ss.Data)[6];
    ((dword*)Data)[7]=((dword*)ss.Data)[7];*/
     Len = ss.Len; Shift=ss.Shift;
    }
   inline char Get(byte i){if(byte(i-1)>=MaxSize-Shift)return 0;return Data[i-1+Shift];}
   inline void Set(byte i,char c){if(byte(i-1)>=MaxSize-Shift)assert(0);Data[i-1+Shift]=c;}
   //---------------------------------------------------------------------------
   inline SmallStr& operator=(const char c){Assign(c);return *this;}
   inline SmallStr& operator=(const char*s){Assign(s);return *this;}
   inline SmallStr& operator=(const SmallStr& ss){Assign(ss); return *this;}
   inline char& operator[](int i){if(byte(i-1)>=MaxSize-Shift)assert(0);return Data[i-1+Shift];}
   //---------------------------------------------------------------------------
   inline SmallStr(){Clear();}
   inline SmallStr(const char c){Assign(c);}
   inline SmallStr(const char*s){Assign(s);}
   inline SmallStr(const SmallStr& ss){Assign(ss);}
   //---------------------------------------------------------------------------
   inline int First(){return 1+Shift;}
   inline int Next(int i){;if(i+Shift>=Len)return 0;return i+1;}
   inline int Previos(int i){return i-1;}
   inline int Last(){return Len+Shift;}
   inline const char*GetItems()const{return Data+Shift;}
  protected:
   enum{MaxSize=31};
   char Data[MaxSize+1];
   byte Shift;
   byte Len;
 };
} 
//------------------------------------------------------------------------------
#endif
