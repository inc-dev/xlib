#ifndef xxOperatorsH
#define xxOperatorsH
#include "xxArray.h"
#include "Algorithms/xxCompare.h"
namespace XSPACE
{
#define X XSPACE
////////////////////////////////////////////////////////////////////////////////
//operators for the usual lines for the other containers do not know whether
////////////////////////////////////////////////////////////////////////////////
//--- compare ----------------------------------------------------------------
inline bool operator==(const X::Str &c1, const X::Str &c2){return X::Equally(c1,c2);}

inline bool operator==(const X::Str &c1, const char* c2){return X::Equally(c1,c2);}
inline bool operator==(const char* c1, const X::Str &c2){return X::Equally(c1,c2);}

inline bool operator!=(const X::Str &c1, const X::Str &c2){return !X::Equally(c1,c2);}
inline bool operator!=(const X::Str &c1, const char* c2){return !X::Equally(c1,c2);}
inline bool operator!=(const char* c1, const X::Str &c2){return !X::Equally(c1,c2);}

inline bool operator< (const X::Str &c1, const X::Str &c2){return X::Compare(c1,c2)<0;}
inline bool operator> (const X::Str &c1, const X::Str &c2){return X::Compare(c1,c2)>0;}
inline bool operator<=(const X::Str &c1, const X::Str &c2){return X::Compare(c1,c2)<=0;}
inline bool operator>=(const X::Str &c1, const X::Str &c2){return X::Compare(c1,c2)>=0;}
//add
 class TxStrContainerSummer: public X::Str
 {
  public:                  //second action
   TxStrContainerSummer(const X::Str&c):X::Str(c){}
   TxStrContainerSummer(const char*c):X::Str(c){}
   TxStrContainerSummer(const int&capacity):X::Str(capacity){}
   inline TxStrContainerSummer&operator+(const X::Str&c){Add(c);return *this;}
   inline TxStrContainerSummer&operator+(const char*c){Add(c);return *this;}
   inline TxStrContainerSummer&operator+(const char c){Add(c);return *this;}
 };
inline TxStrContainerSummer operator+(const X::Str& s1, const X::Str&s2)
 {
  TxStrContainerSummer Temp(s1);
  Temp.Add(s2);
  return Temp;
 }
inline TxStrContainerSummer operator+(const char * ch, const X::Str&s2)
 {
  TxStrContainerSummer Temp(ch);
  Temp.Add(s2);
  return Temp;
 }
inline TxStrContainerSummer operator+(const X::Str& s1,const char *ch)
 {
  TxStrContainerSummer Temp(s1);
  Temp.Add(ch);
  return Temp;
 }
inline TxStrContainerSummer operator+(const char  c, const X::Str&s2)
 {
  TxStrContainerSummer Temp(s2.Size()+1);
  Temp.Add(c);
  Temp.Add(s2);
  return Temp;
 }
inline TxStrContainerSummer operator+(const X::Str& s1,const char c)
 {
  TxStrContainerSummer Temp(s1);
  Temp.Add(c);
  return Temp;
 }
#undef X
}
#endif
//------------------------------------------------------------------------------

