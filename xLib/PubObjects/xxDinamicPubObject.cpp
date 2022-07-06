#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxDinamicPubObject.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
IxBaseObject * TxDinamicObject::GetNewItem(const Str& iName,bool isSimpleObject)
 {
  if(isSimpleObject)
   {
    TxDinamicObject*o = new TxDinamicObject(iName);
    Properties.AddItem(o);
    return (IxBaseObject*)o;
   }
   else
   {
    TxDinamicObject*o = new TxDinamicObject(iName);
    AddItem(o);
    return (IxBaseObject*)o;
   }
 }
}
//------------------------------------------------------------------------------
#ifndef __GNUC__
#pragma package(smart_init)
#endif
