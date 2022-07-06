#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxFileDirWork.h"

#define O_BINARY    0x8000
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
//
#ifdef _WIN32
#include <io.h>
#include <direct.h>
 #ifdef __BORLANDC__
  #include <SysUtils.hpp>
   #include <dir.h>
 #endif
#else
 #include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif
namespace XSPACE
{
//------------------------------------------------------------------------------
bool WriteStringToFile(const Str& FileName,Str str)
 {
  const char *c =str.c_str();
  int Size=str.Size();
  int File=open(FileName.c_str(),O_CREAT|O_BINARY|O_RDWR|O_TRUNC,-1);
  if(File==-1)return 0;
  bool res=write(File, c, Size)==Size;
  close(File);
  return res;
 }
bool AddStringToFile(const Str& FileName,Str str)
 {
  const char *c =str.c_str();
  int Size=str.Size();
  int File=open(FileName.c_str(),O_CREAT|O_BINARY|O_RDWR|O_APPEND,-1);
  if(File==-1)return 0;
  bool res=write(File, c, Size)==Size;
  close(File);
  return res;
 }
bool IsFreeFile(const Str& FileName)
 {
 int File=open(FileName.c_str(),O_BINARY|O_RDONLY,-1);
 if(File==-1)return 0;
 close(File);
 return true;
 }
bool ReadStringFromFile(const Str& FileName,Str&str)
 { //lseek
  str="";
  int File=open(FileName.c_str(),O_BINARY|O_RDONLY,-1);
  if(File==-1)
    return 0;
  int BufferSize=256*256;
  int ReadLen;
  char * b;
  do{
   str.PrepareUpdate(str.Size()+BufferSize);
   b = (char*)(str.c_str()+str.Size());
   ReadLen = read(File,b,BufferSize);
   str.AddItems(ReadLen);
  }while(ReadLen>0);
  close(File);
  return true;
 }
bool ReadBytesFromFile(const Str& FileName,byte*buf,int*len)
 {
  int File=open(FileName.c_str(),O_BINARY|O_RDONLY,-1);
  if(File==-1)return 0;
  *len = read(File,buf,*len);
  close(File);
  return  *len;
 }
bool WriteBytesToFile(const Str& FileName,byte*buf,int len)
 {
  int File=open(FileName.c_str(),O_CREAT|O_BINARY|O_RDWR|O_TRUNC,-1);
  if(File==-1)return 0;
  bool res=write(File, buf, len)==len;
  close(File);
  return res;
 }
#ifdef _WIN32
bool MakeDir(const Str& DirName) { return !mkdir(DirName.c_str());}
#else
bool MakeDir(const Str& DirName) {return !mkdir(DirName.c_str(),7);}
#endif

bool DelDir(const Str& DirName) {return !rmdir(DirName.c_str());}
bool DelFile(const Str& FileName){return !remove(FileName.c_str());}
#ifdef __BORLANDC__
//http://cppworld.h16.ru/stdc/files2.htm
//bool FileExist(const Str& FileName){return FileExists(FileName.c_str());}
//bool DirExist(const Str& FileName){return DirectoryExists(FileName.c_str());}
#endif
bool DirExist(const Str& FileName)
 {
    DIR* dir = opendir(FileName.c_str());
    if (dir)
    {
        closedir(dir);
        return 1;
    }
    return 0;
 }
bool FileExist(const Str& FileName)
{
    int File=open(FileName.c_str(),O_BINARY|O_RDONLY,-1);
    if(File==-1)return 0;
    close(File);
    return 1;
}
int ReName(const Str& OldName,const Str& NewName)
 {
   return rename(OldName.c_str(),NewName.c_str());
 }
Str GetOnlyFileName(const Str& FileName)
 {
   for(int i=FileName.Size();i>0;i--)
    if(FileName[i]=='/'||FileName[i]=='\\')return SubString(FileName,i+1);
   return FileName;
 }
//------------------------------------------------------------------------------
}

#ifndef __GNUC__
#pragma package(smart_init)
#endif
