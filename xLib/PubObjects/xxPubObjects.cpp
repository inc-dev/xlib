#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxPubObjects.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
bool IxBaseClass::ExistParent(IxBaseClass*p)
 {
   IxBaseClass * CurP = Parent;
   while(CurP)
    {
     if(CurP==p)return true;
     CurP = CurP->Parent;
    }
   return false; 
 }
int IxListOfObjects::Find(const Str& Name)
 {
  int i = First();
  while(i)
   {
    if(GetObject(i)->GetName()==Name)return i;
    i = Next(i);
   }
  return 0;
 }
//------------------------------------------------------------------------------
IxBaseObject* IxClassSpace::CreateObject(const Str &  ClassName)
 {
  IxBaseClass*Class = FindClass(ClassName);
  if(Class)return Class->CreateObject();
  return 0;
 }
IxBaseObject *IxBaseObject::CreateClone()
 {
  if(GetClass()==0)return 0;
  IxBaseObject* clon = GetClass()->CreateObject();
  if(clon==0)return 0;
  clon->AssignFromObject(this);
  return clon;
 }
bool IxBaseObject::AssignFromObject( IxBaseObject*o)//пока медленно
 {
  if(o->GetClass()==0)return false;
  if(GetClass()!=o->GetClass())return false;
  SetValueFromStr(o->GetValueToStr());        //это сильно медленно
  IxListOfObjects*Props = o->GetProperties();
  if(Props)
   {
    int i = Props->First();
    while(i)
     {
      IxBaseObject * Prop = Props->GetObject(i);
      if(Prop==0)return false;
      IxBaseObject * MyProp = GetNewItem(Prop->GetName(),true); //true это подсказка только для динамических структур
      if(MyProp==0)return false;
      MyProp->AssignFromObject(Prop);
      i = Props->Next(i);
     }
   }
  IxListOfObjects*Items = o->GetItems();
  if(Items)
   {
    int i = Items->First();
    while(i)
     {
      IxBaseObject * Item = Items->GetObject(i);
      if(Item==0)return false;
      IxBaseObject * MyItem = GetNewItem(Item->GetName(),false); //false это подсказка только для динамических структур
      if(MyItem==0)return false;
      MyItem->AssignFromObject(Item);
      i = Items->Next(i);
     }
   }
  return true;
 }
}
//------------------------------------------------------------------------------
#ifndef __GNUC__
#pragma package(smart_init)
#endif
