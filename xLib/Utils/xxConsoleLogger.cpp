
#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxConsoleLogger.h"
#ifdef _WIN32
#include<conio.h>
#else
#endif
//------------------------------------------------------------------------------
namespace XSPACE
{
TxConsoleLogger ConsoleLogger;
bool TxConsoleLogger::ToConsole(const Str & mess,const Str & date,const Str & time,TxMessType mt)
 {
   Str m=mess;
  #ifdef _WIN32
  m.Unique();
  char*c=(char*)m.c_str();
  CharToOemA(c,c);
  #endif

   Str Res("[");
   if(isPrintToConsoleDate)Res+= date+' ';
   Res+=time+"] ";
   Res+=DecodeMessType(mt);
   if(mt!=lmtMess)Res+=' ';
   Res+=m;
   printf("%s\n",Res.c_str());
   return true;
 };
TxQueryRes TxConsoleLogger::xMessageDlg(const Str & msg,TxMessageDlgType MDT,TxQueryRes def)
 {
  Str s,m=msg;
  #ifdef _WIN32
  m.Unique();  
  char*c=(char*)m.c_str();
  CharToOemA(c,c);
  #endif
  if(MDT==mtxMessage)s="MESSAGE:";
   else
  if(MDT==mtxWarning)s="WARNING:";
   else
  if(MDT==mtxError)s="ERROR:";
   else s="QUERY:";
  s+=m+'\n';
  switch(MDT)
   {
    case mtxQueryOkCancel:s+="1:OK  2:CANCEL \n"; break;
    case mtxQueryYesNo:s+="1:YES  2:NO \n"; break;
    case mtxQueryYesNoCancel:s+="1:YES  2:NO  3:CANCEL\n"; break;
    case mtxQueryAbortRetryIgnore:s+="1:ABORT  2:RETRY  3:IGNORE\n"; break;
    default:s+="PRESS ANY KEY\n"; break;
   };
  printf("%s",s.c_str());
#ifdef _WIN32
  int key = getch();
  switch(MDT)
   {
    case mtxQueryOkCancel:if(key=='1')def = qrOk;else def = qrCancel; break;
    case mtxQueryYesNo:if(key=='1')def = qrYes;else def = qrNo; break;
    case mtxQueryYesNoCancel:if(key=='1')def = qrYes;else if(key=='2')def = qrNo; else def = qrCancel; break;
    case mtxQueryAbortRetryIgnore:if(key=='1')def = qrAbort;else if(key=='2')def = qrRetry; else def = qrIgnore; break;
   };
#else
#endif
  return def;
 };
}

//------------------------------------------------------------------------------
#ifndef __GNUC__
#pragma package(smart_init)
#endif
 
