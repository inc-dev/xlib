#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxObjSerialization.h"
#include <stdio.h>
//------------------------------------------------------------------------------
namespace XSPACE
{
bool IxObjectCoder::EventsBegin() 
 {
  if(!(txtProvider))return false;//||(!ClassSpace)
  return txtProvider->OpenForRead();
 };
bool IxObjectCoder::EventsEnd()   
 {
  if(!(txtProvider))return false;//||(!ClassSpace)
  return txtProvider->Close();
 };
bool IxObjectCoder::WriteBegin()
 {
  Level = 0;
  if(!(txtProvider))return false;
  return txtProvider->OpenForWrite();
 };
bool IxObjectCoder::WriteEnd()
 {
  if(!(txtProvider))return false;
  return txtProvider->Close();
 };
//------------------------------------------------------------------------------
Str IxObjectCoder::DecodeDataEvent(TxDataEvent e)
 {
  switch(e)
   {
    case deOpen:  return "Open";
    case deClose: return "Close";
    case deData:  return "Data";
    case deEnd:   return "End";
    case deError: return "Error";
   };
  return "???";
 }
//------------------------------------------------------------------------------
IxBaseObject*IxObjectCoder::GetFullObject(IxBaseObject*ExistObject)
 {
  if(ClassSpace==0&&ExistObject==0){EventData = "Must be defined ClassSpace";return 0;}
  IxBaseObject* CurrentObject = 0,*temp;
  Stack<IxBaseObject*> ObjStack;
  TxDataEvent e = GetNextEvent();
  if(e==deError)return 0;
  if(e!=deOpen){EventData = Str("Must be 'Open' for Object instead of '")+DecodeDataEvent(e)+'\'';return 0;}
  IxBaseObject* RootObj = 0;
  if(ExistObject==0)RootObj = ClassSpace->CreateObject(EventData);//first is taken from the domain
  else if(EventData==ExistObject->GetName())RootObj = ExistObject;
  if(RootObj==0){EventData = Str("Name '")+EventData+"' not create";return 0;}
  CurrentObject = RootObj;
  do{
   e = GetNextEvent();
   if(e==deOpen)
    {
     temp = CurrentObject->GetNewItem(EventData,isSimpleObject);
     if(temp==0){e = deError;EventData = "Can`t create "+EventData+" for "+CurrentObject->GetName();}
     ObjStack.Push(CurrentObject);
     CurrentObject = temp;
    }else
   if(e==deClose)
    {
     if(!ObjStack.isEmpty()) CurrentObject = ObjStack.Pop();
     else e = deEnd;
    }else
   if(e==deData)
    {
     CurrentObject->SetValueFromStr(EventData);
    }
  }while((e!=deEnd)&&(e!=deError)); 
  if(e==deError){if(ExistObject==0)delete RootObj; RootObj = 0;}
  return RootObj;
 }
//------------------------------------------------------------------------------
bool IxObjectCoder::WriteObject(IxBaseObject*o)
 {
  if(o==0){EventData="Object==0";return false;}
  Str Name = o->GetName();
  Str Value = o->GetValueToStr();
  if(!WriteObjectBegin(Name))return false;
  IxBaseObject*temp; int i;
  //first simple objects
  IxListOfObjects*lst = o->GetProperties();
  if(lst)
   {
    i = lst->First();
    while(i)
     {
      temp = lst->GetObject(i);
      bool isSimpl = isSimpleData(temp->GetValueToStr());
      if(temp->GetItems())isSimpl = isSimpl && temp->GetItems()->First()==0;
      if(temp->GetProperties())isSimpl = isSimpl && temp->GetProperties()->First()==0;
      if(isSimpl)if(!WriteSimpleObject(temp->GetName(),temp->GetValueToStr()))return false;;
      i = lst->Next(i);
     }
   }
  if(Value!="") if(!WriteValue(Value))return false;
  //now complicated
  if(lst)
   {
    i = lst->First();
    while(i)
     {
      temp = lst->GetObject(i);
      bool isSimpl = isSimpleData(temp->GetValueToStr());
      if(temp->GetItems())isSimpl = isSimpl && temp->GetItems()->First()==0;
      if(temp->GetProperties())isSimpl = isSimpl && temp->GetProperties()->First()==0;
      if(!isSimpl)if(!WriteObject(temp))return false;;
      i = lst->Next(i);
     }
   }
  // now list
  lst = o->GetItems();
  if(lst)
   {
    i = lst->First();
    while(i)
     {
      temp = lst->GetObject(i);
      if(!WriteObject(temp))return false;
      i = lst->Next(i);
     }
   }
  if(!WriteObjectEnd())return false;
  return true;
 }
//------------------------------------------------------------------------------
bool IxObjectCoder::SaveObjectToFile(const Str& FileName,IxBaseObject* o)
 {
  TxFileTxtProvider FileTxtProvider;
  FileTxtProvider.FileName = FileName;
  txtProvider = &FileTxtProvider;
  if(!WriteBegin())return false;
  if(!WriteObject(o))return false;
  if(!WriteEnd())return false;
  return true;
 }
//------------------------------------------------------------------------------
IxBaseObject*IxObjectCoder::LoadObjectFromFile(const Str& FileName,IxClassSpace*CS)
 {
  TxFileTxtProvider FileTxtProvider;
  FileTxtProvider.FileName = FileName;
  txtProvider = &FileTxtProvider;
  ClassSpace = CS;
  if(!EventsBegin())return 0;
  IxBaseObject* o = GetFullObject();
  StrPosition = Str("Стр.")+NumToStr(FileTxtProvider.GetLine())+Str(" кол.")+NumToStr(FileTxtProvider.GetCol());  
  if(!EventsEnd()){if(o!=0)delete o;return 0;}
  return o;
 }
bool IxObjectCoder::LoadObjectFromFile(const Str& FileName,IxBaseObject*ExistObject,IxClassSpace*CS)
 {
  TxFileTxtProvider FileTxtProvider;
  FileTxtProvider.FileName = FileName;
  txtProvider = &FileTxtProvider;
  ClassSpace = CS;
  if(!EventsBegin()){EventData=FileTxtProvider.LastError; return 0;}
  IxBaseObject* o = GetFullObject(ExistObject);
  if(o==0)StrPosition = Str("str.")+NumToStr(FileTxtProvider.GetLine())+Str(" col.")+NumToStr(FileTxtProvider.GetCol());
  if(!EventsEnd()){return false;}
  return o!=0;
 }
}
//------------------------------------------------------------------------------
#ifndef __GNUC__
#pragma package(smart_init)
#endif
