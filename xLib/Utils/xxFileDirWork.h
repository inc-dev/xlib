#ifndef xxFileDirWorkH
#define xxFileDirWorkH
#include "../xxBase.h"
 #ifdef _WIN32
  //ToDo
  #include<stdio.h>
  #include<windows.h>
  #include <io.h>
   #else
  #include <sys/types.h>
  #include <dirent.h>
  #include<iostream>
  #include<stdio.h>
 #endif
//------------------------------------------------------------------------------
namespace XSPACE
{
 bool WriteStringToFile(const Str& FileName,Str str);
 bool ReadStringFromFile(const Str& FileName,Str&str);
 bool AddStringToFile(const Str& FileName,Str str);
 bool ReadBytesFromFile(const Str& FileName,byte*buf,int*len);
 bool WriteBytesToFile(const Str& FileName,byte*buf,int len);
 bool MakeDir(const Str& DirName);
 bool DelDir(const Str& DirName);
 bool DelFile(const Str& FileName);
 bool FileExist(const Str& FileName);
 bool DirExist(const Str& FileName); 
 int  ReName(const Str& OldName,const Str& NewName);
 bool IsFreeFile(const Str& FileName);
 Str  GetOnlyFileName(const Str& FileName);
 struct TxFileInfo
  {
   Str Name;
  };
 #ifdef _WIN32
  //ToDo test
 /*
 void getFileList(AnsiString path, FVector* fileList)
 {
    WIN32_FIND_DATA findData;
    HANDLE hFind = FindFirstFile(path.c_str(), &findData);


    if(hFind != INVALID_HANDLE_VALUE)
    {
       BOOL moreFiles = TRUE;
       cFile *File = new cFile();

       while(moreFiles)
       {
          if((findData.cFileName[0] == '.') && (findData.cFileName[1] == 0))
             moreFiles = FindNextFile(hFind, &findData);
          else
          {
             File->SetProperties(&findData);
             File->SetPath(path);

             fileList->push_back(*File);
             moreFiles = FindNextFile(hFind, &findData);
          }

       }
       FindClose(hFind);
       delete File;
    }
 }
 */
class TxScanDir:public TxSerialAccess
  {
    WIN32_FIND_DATAA findData;
    HANDLE hFind;
    Str str_dir;
    TxFileInfo CurrInfo;
   public:
    TxScanDir():str_dir("."){}
    ~TxScanDir(){EndWork();}
    void SetDir(const Str&idir){str_dir=idir;}
     int First()
      {
        hFind = FindFirstFileA(str_dir.c_str(), &findData);
        return hFind!=INVALID_HANDLE_VALUE;
      };
     TxFileInfo &Get(int i)
      {
       if(i)
        {
         CurrInfo.Name = findData.cFileName;
         return CurrInfo;
        }
       static TxFileInfo t;
       return t;
      }
   int Next(int i)
    {
      if(i)return FindNextFileA(hFind, &findData);
      return 0;
    }
   void EndWork()
    {
       if(hFind!=0)
        {
          FindClose(hFind);
          hFind = 0;
        }
    }
  };
 #else
class TxScanDir:public TxSerialAccess
  {
    DIR *dir;
    dirent *ent;
    Str str_dir;
    TxFileInfo CurrInfo;
   public:
    TxScanDir():dir(0),ent(0),str_dir("."){}
    ~TxScanDir(){EndWork();}
    void SetDir(const Str&idir){str_dir=idir;}
     int First()
      {
       dir = opendir(str_dir.c_str());
       return Next(1);
      };
     TxFileInfo &Get(int i)
      {
       if(i&&ent!=0)
        {
         CurrInfo.Name = ent->d_name;
         return CurrInfo;
        }
       static TxFileInfo t;
       return t;
      }
   int Next(int i)
    {
       if(i&&dir!=0)
        {
         ent = readdir(dir);
         return ent!=0;
        }
       return 0;
    }
   void EndWork()
    {
     if(dir!=0){closedir(dir); dir=0;}
    }
  };
 #endif
}
//------------------------------------------------------------------------------
#endif
