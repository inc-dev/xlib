#pragma hdrstop
#include "xxSupportDLL.h"
#include "xxLogger.h"
#include "xxLang.h"
namespace XSPACE
{
bool IxSupportDLL::internalFreeLib()
 {
  if(hDLL==0)return true;
  Synchronization.value = 0;
  bool res = FreeLibrary(hDLL);
  hDLL = 0;
  return res;
 }
bool IxSupportDLL::internalLoadLib()
 {
  if(hDLL!=0)internalFreeLib();
  hDLL = LoadLibrary(DDLName());
  if(hDLL==0){LastError = DDLName()+Str(" ")+Translate("don`t load");return false;}
  else Synchronization.value = xNow();
  return true;
 }
//-----------------------------------
}
#pragma package(smart_init)
