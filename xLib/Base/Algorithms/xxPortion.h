#ifndef xxPortionH
#define xxPortionH
#include "../xxDataAccess.h"
#include "../xxArray.h"
namespace XSPACE
{
//- SubString Portion --------------------------------------------------------
template<typename TContainer>
inline TContainer Portion(const TContainer& c,int from)
 {
  return internalPortion(c,&c,from);
 }
//------------------------------------------------------------------------------
template<typename TContainer>
inline TContainer Portion(const TContainer& c,int from,int to)
 {
   return internalPortion(c,&c,from,to);
 }
//------------------------------------------------------------------------------
template<typename TContainer>
TContainer internalPortion(const TContainer& c,const TxSerialAccess*a,int from)
 {
  TContainer Res;
  int Current = from;
  while(Current)
   {
    Res.Add(c.Get(Current));
    Current = c.Next(Current);
   }
   return Res;
 }
//------------------------------------------------------------------------------
template<typename TContainer>
TContainer internalPortion(const TContainer& c,const TxSerialAccess*a,int from,int to)
 {
  TContainer Res;
  int Current = from;
  while(Current)
   {
    Res.Add(c.Get(Current));
    if(Current==to)break;
    Current = c.Next(Current);
   }
   return Res;
 }
//------------------------------------------------------------------------------
template<typename TContainer>
inline TContainer internalPortion(const TContainer& c,const TxMonolithAccess*a,int from)
 {
  if(from>c.Size()||from<1)return TContainer();
  return TContainer(&c[from],c.Size()-from+1);
 }
//------------------------------------------------------------------------------
template<typename TContainer>
inline TContainer internalPortion(const TContainer& c,const TxMonolithAccess*a,int from,int to)
 {
  if(from>c.Size()||from<1||to>c.Size()||to<1)return TContainer();
  return TContainer(&c[from],to-from+1);
 }

//------------------------------------------------------------------------------
inline Str SubString(const Str&s,int from, int count = 10000000)
 {
  if(from>s.Size()||from<1||count<1){Str s;return s;};
  if(count>s.Size()-from+1) count = s.Size()-from+1;
  return Str(s.GetItems()+from-1,count);
 }
Str Trim(const Str &s);
Str TrimLeft(const Str &s);
Str TrimRight(const Str &s);
};
#endif
