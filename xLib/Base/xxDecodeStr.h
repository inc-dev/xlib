#ifndef xxDecodeStrH
#define xxDecodeStrH
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include "xxArray.h"
#include "xxSmallStr.h"
#include "xxDateTime.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
template<typename T> inline long Trunc(const T& i){return long(i);}
template<typename T> inline long Round(const T& i){return (i)>0?Trunc(i+0.5):Trunc(i-0.5);}
template<typename T> inline T    Abs(const T& i){return i>0?i:-i;}
template<typename T> inline T    Max(const T& a,const T& b){return a>b?a:b;}
                     inline double Max(const double& a,const int& b){return a>(double)b?a:(double)b;}
                     inline double Max(const int& a,const double& b){return (double)a>b?(double)a:b;}
template<typename T> inline T   Min(const T& a,const T& b){return a>b?b:a;}
                     inline double Min(const double& a,const int& b){return a>(double)b?(double)b:a;}
                     inline double Min(const int& a,const double& b){return (double)a>b?b:(double)a;}

       int    StrToInt(const char*ch);
inline int    StrToInt(const Str s){return StrToInt(s.c_str());};
       int64  StrToInt64(const char*ch);
inline int64  StrToInt64(const Str s){return StrToInt64(s.c_str());};
       double StrToDouble(const char*ch);
inline double StrToDouble(const Str s){return StrToDouble(s.c_str());};

class NumToStr:public SmallStr
 {
  public:
  NumToStr(int  i);
  NumToStr(unsigned int  i);
  NumToStr(double i,int CountAfterPoint=5);
  NumToStr(int64 i);
  NumToStr(uint64 i);
 };

int IntToChars(char*d,int i); //itoa
int UIntToChars(char*d,unsigned int i);
int Int64ToChars(char*d,int64 i);
int UInt64ToChars(char*d,uint64 i);
int DoubleToChars(char*d,double i,int CountAfterPoint=5);

int   BitsToChars(char*d,int64 i);
Str  BinToHexStr(void *Buffer,int BufSize);
bool HexStrToBin(void *Buffer,const Str&s,int BufSize);
int  HexStrToInt(const Str&s);
Str  OnlyDigit(const Str&s);
Str  BinByteToStr(byte b);
bool isOnlyDigit(const Str&s);
inline bool isDigit(const char& c){return c>='0'&&c<='9';}

Str SPrintf(const char* format, ...);

Str   xDateToStr(int64 Date);   //dd.mm.yyyy
int64 xStrToDate(const Str& s); //dd.mm.yyyy
Str   xDateTimeToStr(int64 Date);   //dd.mm.yyyy hh:nn:ss
int64 xStrToDateTime(const Str& s); //dd.mm.yyyy hh:nn:ss
Str   xDateTimeToFileNameStr(int64 Date);//yymmdd_hhnnss
}
//------------------------------------------------------------------------------
#endif
