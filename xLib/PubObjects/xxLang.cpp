#ifndef __GNUC__
#pragma hdrstop
#endif

#include "xxLang.h"
#include "xxStaticPubObject.h"
#include "../xxObjects.h"
#include "../Utils/xxFileDirWork.h"
#include "../Utils/xxLogger.h"
#include "../Utils/xxTxtProvider.h"
#include "xxXMLObjSerialization.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
//------------------------------------------------------------------------------
void TxLangModule::SetAppVars(IxAppVariables*AV)
 {
  AltFileName = AV->GetAppDir() + "/Lang.xml";
  FileName = AV->GetConfigDir() + "/Lang.xml";
 }
class TxDictionaryItem:public TxStaticObject<TxDictionaryItem>
 {
  public:
   ObjProperty(ObjStr,Original);
   ObjProperty(ObjStr,Translate);
   static const char* GetClassName(){return "DI";}
   class Class:public TxStaticClass<ObjType,Class>
    {
     public:
      Class()
       {
        PublishedProperty(Original);
        PublishedProperty(Translate);
       }
    };
 };
//------------------------------------------------------------------------------
class TxDictionary;
static TxDictionary *Dictionary = 0;
class TxDictionary:public TxStaticItemsListObject<TxDictionary,TxDictionaryItem>
 {
  public:
   static const char* GetClassName(){return "Dictionary";}
   typedef TxStaticClass<ObjType> Class;
   TxDictionaryItem* FindItemByName(const char*s)
    {
     int i = Items.First();
     while(i)
      {
       TxDictionaryItem* it=Items.Get(i);
       if(it->Original.GetValue()==s)return it;
       i = Items.Next(i);
      }
     return 0;
    }
 };
class TxLangClassSpace: public IxStaticClassSpace
 {
   public:
    TxLangClassSpace()
     {
      RegisterClass(&TxDictionary::Class::Instance());
     }
    virtual const char* GetName()const{return "TradeWaresClassSpace";}
    static TxLangClassSpace &Instance(){static TxLangClassSpace t;return t;}
 };
//------------------------------------------------------------------------------
Str Translate(const char*s)
 {
  if(s==0||s[0]==0)return "";
  if(byte(s[0])<65||s[1]==0)return s;
  if(Dictionary==0)return s;
  TxDictionaryItem*DI = Dictionary->FindItemByName(s);
  if(DI)return DI->Translate.GetValue();
  if(s[0]==0)return "";
  DI = new TxDictionaryItem();
  DI->Original = s;
  DI->Translate = s;
  Dictionary->Items.Add(DI);
  return s;
 }
bool LoadDictionary(const Str&iFileName,const Str&iAltFileName)
 {
  Str FileName = iFileName;
  if(!FileExist(FileName.c_str()))FileName = iAltFileName;
  if(!FileExist(FileName.c_str()))
   {
    Warning("File "+FileName+" not found");
    Dictionary = new TxDictionary();
    return true;
   }
  TxFileTxtProvider FileTxtProvider;
  FileTxtProvider.FileName = FileName;
  TxXMLCoder XMLCoder;
  XMLCoder.txtProvider = &FileTxtProvider;
  XMLCoder.ClassSpace  = &TxLangClassSpace::Instance();
  if(XMLCoder.EventsBegin())
   {
    if(Dictionary)delete Dictionary;
    Dictionary = (TxDictionary*)XMLCoder.GetFullObject();
    if(!XMLCoder.EventsEnd())return false;
    if(Dictionary==0)
     {
      Warning("File "+FileName+" is bad");
      Dictionary = new TxDictionary();
     }
    return true;
   }else return false;
 }

bool SaveDictionary(const Str&FileName)
 {
  if(Dictionary==0)return false;
  TxFileTxtProvider FileTxtProvider;
  FileTxtProvider.FileName = FileName;
  TxXMLCoder XMLCoder;
  XMLCoder.txtProvider = &FileTxtProvider;
  XMLCoder.ClassSpace  = &TxLangClassSpace::Instance();
  if(XMLCoder.WriteBegin())
   {
    if(!XMLCoder.WriteObject(Dictionary))return false;
    if(!XMLCoder.WriteEnd())return false;
    return true;
   }else return false;
 }
bool TxLangModule::Init()
 {
  return LoadDictionary(FileName,AltFileName);
 }
bool TxLangModule::Done()
 {
  bool Res = SaveDictionary(FileName);
  if(Dictionary)delete Dictionary;
  Dictionary = 0;
  return Res;
 }
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
#ifndef __GNUC__
#pragma package(smart_init)
#endif

