#ifndef __GNUC__
#pragma hdrstop
#endif

//---------------------------------------------------------------------------
#include "xxPortion.h"
namespace XSPACE
{
Str Trim(const Str &s)
 {
  int From = 1,To = s.Size();
  while(To)if(byte(s.QGET(To))<=32)To--;else break;
  if(To)
   {
    while(From<To)if(byte(s.QGET(From))<=32)From++;else break;
    return Str(s.GetItems()+From-1,To-From+1);
   }
  return "";
 }
Str TrimLeft(const Str &s)
 {
  for(int From=1;From<=s.Size();From++)
   if(byte(s.QGET(From))>32)return Str(s.GetItems()+From-1,s.Size()-From+1);
  return "";
 }
Str TrimRight(const Str &s)
 {
  int To = s.Size();
  while(To)if(byte(s.QGET(To))<=32)To--;else break;
  if(To)return Str(s.GetItems(),To);
  return "";
 }
}
//---------------------------------------------------------------------------
#ifndef __GNUC__
#pragma package(smart_init)
#endif
