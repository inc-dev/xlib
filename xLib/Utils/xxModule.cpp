#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxModule.h"
#include "xxLogger.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
void TxModuleContainer::SetAppVars(IxAppVariables*AV)
 {
  MainSetAppVars(AV);
  int i = Modules.First();
  while(i)
   {
    Modules.Get(i)->SetAppVars(AV);
    i = Modules.Next(i);
   }
 }
void TxModuleContainer::TranslateItems()
 {
  MainTranslateItems();
  int i = Modules.First();
  while(i)
   {
    Modules.Get(i)->TranslateItems();
    i = Modules.Next(i);
   }
 }
bool TxModuleContainer::Init()
 {
  int i = Modules.First();
  bool res = true;
  while(i)
   {
    if(!Modules.Get(i)->Init()){res = false;Error("Not Init"+Str(Modules.Get(i)->GetName()));}
    else Mess("Init "+Str(Modules.Get(i)->GetName()),lsDebug);
    i = Modules.Next(i);
   }
  if(!MainInit())return false;
  return res;
 }
bool TxModuleContainer::Done()
 {
  if(!MainDone())return false;
  int i = Modules.Last();
  bool res = true;
  while(i)
   {
    if(!Modules.Get(i)->Done()){res = false;Error("Not Done"+Str(Modules.Get(i)->GetName()));}
    else Mess("Done "+Str(Modules.Get(i)->GetName()),lsDebug);
    i = Modules.Prev(i);
   }
  return res;
 }
}
//------------------------------------------------------------------------------
#ifndef __GNUC__
#pragma package(smart_init)
#endif
