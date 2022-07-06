#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxCodePages.h"
#include "xxUTF8.h"
#include "xxCP1251.h"
//-------------------------------------------
namespace XSPACE
{
List<IxBaseCodePage*> CodePages;
//-------------------------------------------
TxCodePageUTF8 CodePageUTF8;
TxCodePageCP1251 CodePageCP1251;
IxBaseCodePage * CurrentCodePage=&CodePageCP1251;
//------------------------------------------------------------------------------
IxBaseCodePage::IxBaseCodePage()
 {
  CodePages.Add(this);
 }
//------------------------------------------------------------------------------
IxBaseCodePage*FindCodePage(const Str & iName)
 {
  int i = CodePages.First();
  while(i)
   {
    IxBaseCodePage*item = CodePages.Get(i);
    if(StrCmpICLat(iName.c_str(),item->Name.c_str())==0)return item;
    i = CodePages.Next(i);
   }
  return 0;
 }
//------------------------------------------------------------------------------
Str UnicodeDeCodeStr(const Str& s,IxBaseCodePage*From,IxBaseCodePage*To)
 {
  if(From==0||To==0)
       return s;
  int Pos=1;
  Str ss;
  UnicodeChar UniC;
  do{
   UniC = From->GetUnicodeChar(s,Pos);
   if(UniC)To->AddUnicodeChar(ss,UniC);
  }while(UniC);
  return ss;
 }

//------------------------------------------------------------------------------
Str DeleteCodeChars(const Str&s,char changer)
 {
  unsigned int Pos=1;
  Str ss = s;
  do{
   Pos = Find(ss,"&#",Pos);
   if(Pos)
    {
     unsigned int Pos2=Find(ss,';',Pos);
     ss.Set(Pos,changer);
     Pos++;
     if(Pos2) ss.Delete(Pos,Pos2-Pos+1);
    }
  }while(Pos);
  return ss;
 }
}
#ifndef __GNUC__
#pragma package(smart_init)
#endif
