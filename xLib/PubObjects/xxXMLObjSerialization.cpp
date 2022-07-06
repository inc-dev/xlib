#ifndef __GNUC__
#pragma hdrstop
#endif

#include "xxXMLObjSerialization.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
bool TxXMLCoder::isValidName(const Str & s)
 {
   if(s.Size()==0){EventData="bad inditificator Size==0";return false;}
   //char first_char = s.Take(1);
   return true;
 }
//------------------------------------------------------------------------------
TxDataEvent TxXMLCoder::GetNextEvent()
 {
  char c;
  if(BodyFase==fbBegin||BodyFase==fbOUTCaption)
   {
    while(true) //<!, <?, </, <name
     {
      c = txtProvider->GetOther(" \n\r\t");
      if(BodyFase==fbOUTCaption&&(Names.Size()==0)&&c==0){EventData = ""; return deEnd;}//finished parsing
      if(c!='<')
       {
        if(BodyFase==fbBegin||Names.Size()==0){EventData="not found '<'";return deError;}
        //just data
        EventData = c;
        c = txtProvider->AddToStrTermChar(EventData,"<");//select all the TO split
        EventData = Trim(EventData);
        EventData = StrFromXMLStr(EventData);
        if(c!='<'){EventData="not found '<'";return deError;}
        txtProvider->UnGet(c);//return separator
        return deData;
       }
      c = txtProvider->Get();
      // !
      if(c==0){EventData="not found end";return deError;}
      if(c=='!'){ txtProvider->SkipTo("-->");continue; }//comments
      // ?
      if(c=='?')
       {
        Str s;
        txtProvider->AddToStrTermStr(s,"?>");
        int i = Find(s,"encoding");
        if(i>0)
         {
          i+=8; i = FindFirstOut(s," \n\r\t",i);
          c = s.Take(i);
          if(c!='='){EventData="not found encoding'='";return deError;}
          i++; i = FindFirstOut(s," \n\r\t",i);
          c = s.Take(i);
          if(c!='"'&&c!='\''){EventData="not found encoding=' \" '";return deError;}
          i++;
          int j = Find(s,c,i);
          if(j>i){encoding = SubString(s,i,j-i);i=j;}else encoding = "";
          if(encoding.Size()==0){EventData="bad encoding=' \" '";return deError;}
          CodePage = FindCodePage(encoding);
          if(CodePage==0){EventData="not support encoding=\""+encoding+'\"';return deError;}
         }
        continue;
       }
      // '/'
      if(c=='/')
       {
        if(Names.Size()==0){EventData="not found begin for '</'";return deError;}
        EventData="";
        if(txtProvider->AddToStrTermChar(EventData,">")!='>') {EventData="not found '>' for end block";return deError;}
        if(CodePage!=CurrentCodePage)EventData=UnicodeDeCodeStr(EventData,CodePage,CurrentCodePage);
        Str s = Names.Pop();
        if(EventData!=s) {EventData="Bad </"+EventData+"> , must be </"+s+">";return deError;}
        BodyFase = fbOUTCaption;
        return deClose;
       }
      // Name
      EventData = c;
      char cc = txtProvider->AddToStrTermChar(EventData," \n\r\t>/");//select all TO the split
      txtProvider->UnGet(cc);//return separator
      if(CodePage!=CurrentCodePage)EventData=UnicodeDeCodeStr(EventData,CodePage,CurrentCodePage);
      if(!isValidName(EventData))return deError;
      Names.Push(EventData);
      BodyFase = fbInCaption;
      isSimpleObject = false;
      return deOpen;
     }
   }
  if(BodyFase==fbInCaption)
   {
    c = txtProvider->GetOther(" \n\r\t");
    //'>'
    if(c=='>'){ BodyFase = fbOUTCaption; return GetNextEvent(); }
    //'/'
    if(c=='/')
     {
      c = txtProvider->Get();
      if(c!='>'){EventData="not found > after /";return deError;}
      if(Names.Size()==0){EventData="not open";return deError;}
      EventData = Names.Pop();
      BodyFase = fbOUTCaption;
      return deClose;
     }
    //property name
    if(c==0){EventData="not found end";return deError;}
    EventData = c;
    c = txtProvider->AddToStrTermChar(EventData,"= \n\r\t");//select all TO the split
    if(CodePage!=CurrentCodePage)EventData=UnicodeDeCodeStr(EventData,CodePage,CurrentCodePage);
    if(!isValidName(EventData))return deError;
    Names.Push(EventData);
    txtProvider->UnGet(c);//return separator
    BodyFase = fbSimplData;
    isSimpleObject = true;
    return deOpen;
   }
  if(BodyFase==fbSimplData)
   {
    c = txtProvider->GetOther(" \n\r\t");
    if(c!='='){EventData="not found '='";return deError;}
    c = txtProvider->GetOther(" \n\r\t");
    char TermChar[2];
    TermChar[0]=c;TermChar[1]=0;
    if(c!='"'&&c!='\''){EventData="not found \"";return deError;}
    EventData = "";
//    c = txtProvider->AddToStrTermChar(EventData,"\"\'");//select all TO the split
    c = txtProvider->AddToStrTermChar(EventData,TermChar);//select all TO the split
//    const char*sssss=EventData.c_str();
    if(c!='"'&&c!='\''){EventData="not found \"";return deError;}
    BodyFase = fbSimplEnd;
    EventData = StrFromXMLStr(EventData);
    return deData;
   }
  if(BodyFase==fbSimplEnd)
   {
    BodyFase = fbInCaption;
    EventData = Names.Pop();
    return deClose;
   }
  EventData = "out fase";
  return deError;
 }
//------------------------------------------------------------------------------
bool TxXMLCoder::WriteObjectBegin(const Str& Name)
 {
  if(BodyFase==fbBegin&&encoding.Size()>0)
   {
   if(!txtProvider->Write(Str("<?xml version=\"1.0\"  encoding = \"")+encoding+"\"?>\r\n"))
    {EventData="not Write:"+txtProvider->LastError;return false;}
    CodePage = FindCodePage(encoding);
   }
  Str iName=Name;
  if(CodePage!=CurrentCodePage)iName=UnicodeDeCodeStr(iName,CurrentCodePage,CodePage);
  if(!isValidName(iName))
   {EventData="invalid name:"+iName;return false;}
  Str s;
  if(BodyFase==fbInCaption) s=">\r\n";
  for(int i=0;i<Level;i++)s+=' ';
  s+='<'; s+=iName;
  if(!txtProvider->Write(s))
   {EventData="not Write:"+txtProvider->LastError;return false;}
  BodyFase = fbInCaption; isOneLine = true;
  Level++;
  Names.Push(iName);
  return true;
 }

//------------------------------------------------------------------------------
bool TxXMLCoder::isSimpleData(const Str& Value)
 {
  return Find(Value,'\n')==0&&Find(Value,'\r')==0;
 }
//------------------------------------------------------------------------------
bool TxXMLCoder::WriteValue(const Str& Value)
 {
  if(Value.Size()==0)return true;
  if(BodyFase == fbInCaption)
   {
    if(!txtProvider->Write(">"))
     {EventData="not Write:"+txtProvider->LastError;return false;}
    BodyFase = fbOUTCaption;
   }
  Str nValue = StrToXMLStr(Value);
  if(FindFirstIn(nValue,"\r\n")!=0)isOneLine = false;
  Str s;
  if(isOneLine)s = nValue; else s = "\r\n"+nValue+"\r\n";
  if(!txtProvider->Write(s))
   {EventData="not Write:"+txtProvider->LastError;return false;}
  return true;
 }
//------------------------------------------------------------------------------
bool TxXMLCoder::WriteObjectEnd()
 {
  if(Names.Size()<=0){EventData="Bad end";return false;}
  Level--;
  if(BodyFase == fbInCaption)
   {
    if(!txtProvider->Write("/>\r\n"))
     {EventData="not Write:"+txtProvider->LastError;return false;}
    Names.Pop();
   }else
   {
    Str s;
    if(!isOneLine) for(int i=0;i<Level;i++)s+=' ';
    s+="</"; s+=Names.Pop(); s+=">\r\n";
    if(!txtProvider->Write(s))
     {EventData="not Write:"+txtProvider->LastError;return false;}
   }
  BodyFase = fbOUTCaption; isOneLine = false;
  return true;
 }
//------------------------------------------------------------------------------
bool TxXMLCoder::WriteSimpleObject(const Str& Name,const Str& Value)
 {
  Str s;
  if(Value=="")return true;//do not write empty tags
  Str iName=Name;
  if(CodePage!=CurrentCodePage)iName=UnicodeDeCodeStr(iName,CurrentCodePage,CodePage);
  if(!isValidName(iName)){EventData="invalid name:"+iName;return false;}
  Str nValue = StrToXMLStr(Value);
  if(BodyFase == fbInCaption)
   s = ' '+iName+"=\""+nValue+'\"';
  else
   {                                                
    for(int i=0;i<Level;i++)s+=' ';
    s = s+'<'+iName+'>'+nValue+"</"+iName+">\r\n";
   }
  bool Res = txtProvider->Write(s);
  if(!Res)EventData = "don`t write :"+s;else EventData = "";
  return Res;
 }
//------------------------------------------------------------------------------
Str TxXMLCoder::StrToXMLStr(const Str& u)
 {
   Str s = u;
   if(CodePage!=CurrentCodePage)s=UnicodeDeCodeStr(s,CurrentCodePage,CodePage);
   Str ss; int i=1;
   while(i<=s.Size())
    {
     char c = s.Take(i);
     m:
     if(c=='&'){i++;c = s.Take(i);if(c!='#'){ss+="&amp;";goto m;}else ss+="&#";}
     else
     if(c=='<')ss+="&lt;";
     else
     if(c=='>')ss+="&gt;";
     else
     if(c=='\"')ss+="&quot;";
     else
     if(c=='\'')ss+="&apos;";
     else
     if(byte(c)<32){ss+="&#"+NumToStr(int(byte(c)))+';';if(c==10)ss+=10;}
     else
     ss+=c;
     i++;
    }
  return ss;
 }
//------------------------------------------------------------------------------
Str TxXMLCoder::StrFromXMLStr(const Str & u)
 {
  Str s = u;
  if(CodePage!=CurrentCodePage)
     s=UnicodeDeCodeStr(s,CodePage,CurrentCodePage);
  Str ss;
  char c; int pos = 1;
  do{
   c = s.Take(pos);pos++;
   if(c=='&')
    {
     c = s.Take(pos);pos++;
     switch(c)
      {
       case 'l':ss+='<';pos+=2; break;
       case 'g':ss+='>';pos+=2; break;
       case 'q':ss+='\"';pos+=4; break;
       case 'a':
        c = s.Take(pos);pos++;
        if(c=='m'){ss+='&';pos+=2;}else{ss+='\'';pos+=3;}
       break;
       case '#':
       { Str digi;
        do
        {
         c = s.Take(pos);pos++;
         if(c!=0&&c!=';')digi+=c;
        }
        while(c!=0&&c!=';');
        if(digi.Size())
         {
          int d;
          if(digi[1]=='x'||digi[1]=='X')
           {
           digi.Delete(1);
           d = HexStrToInt(digi);
           }
          else
           d = StrToInt(digi);
          if(d)
           {
            if(d<=32)ss+=char(d);
            else ss+="&#"+NumToStr(d)+';';
           }
         }
       break;}
       default: ss+='&'; if(c)ss+=c;
      }
    }else if(byte(c)>=32) ss+=c;
  }while(c);
  return ss;
 }
}
//------------------------------------------------------------------------------
#ifndef __GNUC__
#pragma package(smart_init)
#endif
