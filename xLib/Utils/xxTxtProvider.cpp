#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxTxtProvider.h"
#include <stdio.h>
#include <fcntl.h>
#define O_BINARY    0x8000
#ifdef _WIN32
 #include <io.h>
#else
 #include <unistd.h>
#endif
//------------------------------------------------------------------------------
namespace XSPACE
{
char IxBaseTxtProvider::Get()
 {
  char c;
  if(!Undo.isEmpty())
   return Undo.Pop();
  else
   {
    c = InternalGet();
    if(c=='\n'){Line++;Col=0;}
    Col++;
   }
  return c;
 }
//------------------------------------------------------------------------------
int IxBaseTxtProvider::GetLine()
 {
   int Count = 0;
   for(int i=1;i<=Undo.Size();i++)
    if(Undo.Get(i)=='\n')Count++;
   return Line-Count;
 }
int IxBaseTxtProvider::GetCol()
 {
  if(Find(Undo,'\n')>0||Col<=Undo.Size()) return 1;//not calculated value
  return Col-Undo.Size();
 }
//------------------------------------------------------------------------------
char IxBaseTxtProvider::AddToStrTermChar(Str&s,const char *term)
 {
  char c;
  do{
    c = Get();
    if(strchr(term,c)||c==0)return c;
    s+=c;
  }while(true);
 }
void IxBaseTxtProvider::AddToStrTermStr(Str&s,const char *term)
 {
  char c;
  int fase = 0;
  do{
    c = Get();
    if(c==0){if(fase)s.Add(term,fase); return;}
    if(term[fase]==c)fase++;
    else
     {
      if(fase!=0){s.Add(term,fase);fase = 0;}
      s+=c;
     }
    if(term[fase]==0)return;
  }while(true);
 }
//------------------------------------------------------------------------------
char IxBaseTxtProvider::GetOther(const char*s)
 {
  char c;
  do{
   c = Get();
  }while(strchr(s,c)&&c);
  return c;
 }
//------------------------------------------------------------------------------
void IxBaseTxtProvider::SkipTo(const char*s)
 {
  int fase = 0;
  if(s==0)return;
  while(true)
   {
    char c = Get();
    if(s[fase]==c&&s[fase])fase++;else fase = 0;
    if(s[fase]==0||c==0)return;
   }
 }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool TxStrTxtProvider::Write(Str s)
 {
  if(Pos==1)str="";
  str+=s;Pos+=s.Size();
  return true;
 }
//------------------------------------------------------------------------------
char TxStrTxtProvider::InternalGet()
 {
  char c=str.Take(Pos);
  Pos++;
  return c;
 };
//------------------------------------------------------------------------------
bool TxStrTxtProvider::Seek(int i,int FromWhere)
 {
  switch(FromWhere)
   {
    case SEEK_SET:Pos = i+1;break;
    case SEEK_CUR:Pos += i; break;
    case SEEK_END:Pos = str.Size()+i; break;// or - ?
   }
  return true;
 }
//------------------------------------------------------------------------------
const int FileTxtProviderBufferSize = 100000;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool TxFileTxtProvider::OpenForRead()
 {
  if(!IxBaseTxtProvider::OpenForRead())return false;
  int Acces = O_BINARY|O_RDONLY;
  File = open(FileName.c_str(),Acces,-1);
  if(File==-1){LastError = "File "+FileName+" not open"; return false;}
  isToWrite = false;
  ReadTobuff();
  return true;
 }
//------------------------------------------------------------------------------
bool TxFileTxtProvider::OpenForWrite()
 {
  if(!IxBaseTxtProvider::OpenForWrite())return false;
  int Acces = O_CREAT|O_BINARY|O_RDWR|O_TRUNC;
  File = open(FileName.c_str(),Acces,-1);
  if(File==-1){LastError = "File "+FileName+" not open"; return false;}
  isToWrite = true;
  Buff="";
  return true;
 }
//------------------------------------------------------------------------------
char TxFileTxtProvider::InternalGet()
 {
  if(Buff.Size()==0)return 0;
  if(BufPos>Buff.Size())ReadTobuff();
  if(BufPos>Buff.Size())return 0;
  char c = Buff.Take(BufPos);
  BufPos++;
  return c;
 }
//------------------------------------------------------------------------------
bool TxFileTxtProvider::ReadTobuff()
 {
  Buff="";
  Buff.Reserve(FileTxtProviderBufferSize,true);
  char*c=Buff.GetItems();
  int i=read(File,c,FileTxtProviderBufferSize);
  Buff.AddItems(i);
  //  Buff.AddItems(read(File,Buff.GetItems(),FileTxtProviderBufferSize));
  BufPos = 1;
  return true;
 }
//------------------------------------------------------------------------------
bool TxFileTxtProvider::Write(Str s)
 {
  Buff+=s;
  if(Buff.Size()>FileTxtProviderBufferSize)return WriteBuffer();
  return true;
 }
//------------------------------------------------------------------------------
bool TxFileTxtProvider::WriteBuffer()
 {
   if(Buff.Size()==0)return true;
   bool res=write(File, Buff.c_str(), Buff.Size())==(int)Buff.Size();
   Buff = "";
   return res;
 }
//------------------------------------------------------------------------------
bool TxFileTxtProvider::Close()
 {
  if(isToWrite)WriteBuffer();
  int i = close(File);
  return i==0;
 }
//------------------------------------------------------------------------------
bool TxFileTxtProvider::Seek(int i,int FromWhere)
 {
  return lseek(File,i,FromWhere)>=0;
 }
int  TxFileTxtProvider::Position()
 {
  return lseek(File,0,SEEK_CUR)-Undo.Size();
 }
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------

#ifndef __GNUC__
#pragma package(smart_init)
#endif
