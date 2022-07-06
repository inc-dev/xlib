#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxLogger.h"
#include "xxFileDirWork.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
Str TxLogger::GetDate(int64 d)
 {
  tm dd = xDecodeDateTime(d);
  Str day(NumToStr(dd.tm_mday));  if(day.Size()==1)day='0'+day;
  //Str m = NumToStr(dd.tm_mon+1); if(m.Size()==1)m='0'+m;
  //return day+'.'+m+'.'+NumToStr(dd.tm_year+1900-2000);
  return day+' '+Months_Names[dd.tm_mon];
 }
Str TxLogger::GetTime(int64 d)
 {
  tm dd = xDecodeDateTime(d);
  Str h = NumToStr(dd.tm_hour); if(h.Size()==1)h='0'+h;
  Str m = NumToStr(dd.tm_min); if(m.Size()==1)m='0'+m;
  Str s = NumToStr(dd.tm_sec); if(s.Size()==1)s='0'+s;
  return h+':'+m+':'+s;
 }
Str DecodeMessType(TxLogger::TxMessType r)
 {
   switch(r)
   {
    case TxLogger::lmtMess    :return "";
    case TxLogger::lmtWarning :return "WARNING";
    case TxLogger::lmtError   :return "ERROR";
    case TxLogger::lmtQuery   :return "QUERY";
    default        :return "???";
   }
 }
bool TxLogger::ToLog(const Str & mess,const Str & date,const Str & time,TxMessType mt)
 {
  Str sDecodeMessType(DecodeMessType(mt));if(sDecodeMessType.Size()>0)sDecodeMessType='"'+sDecodeMessType+"\" ";
  return AddStringToFile(LogFile,'['+date+' '+time+"] "+sDecodeMessType+mess+"\n");
 }
void TxLogger::RecentActions(const Str& msg)
 {
  int64 dt = xNow();
  AddStringToFile("RecentActions.txt",Str("[")+GetDate(dt)+' '+GetTime(dt)+"] "+msg+"\n");
 }
void TxLogger::Mess(const Str& msg,int TypeWork)
 {
  LastMessage = msg;
  if(!(TypeWork&State))return;
  int64 dt = xNow();
  Str Date = GetDate(dt),Time = GetTime(dt);
  ToLog(msg,Date,Time,lmtMess);
  ToConsole(msg,Date,Time,lmtMess);
 }
void TxLogger::Warning(const Str& msg,int TypeWork)
 {
  LastWarning = msg;
  if(!(TypeWork&State))return;
  int64 dt = xNow();
  Str Date = GetDate(dt),Time = GetTime(dt);
  ToLog(msg,Date,Time,lmtWarning);
  ToConsole(msg,Date,Time,lmtWarning);
 }
void TxLogger::Error(const Str& msg,int TypeWork)
 {
  LastError = msg;
  if(!(TypeWork&State))return;
  int64 dt = xNow();
  Str Date = GetDate(dt),Time = GetTime(dt);
  ToLog(msg,Date,Time,lmtError);
  ToConsole(msg,Date,Time,lmtError);
 }

void TxLogger::MessDialog(const Str& msg,bool DisableLog,int TypeWork)
 {
  if(!(TypeWork&State))return;
  if(!DisableLog)Mess(msg,TypeWork);
  if(isAutonom)return;
  xMessageDlg(msg,mtxMessage);
 }
void TxLogger::WarningDialog(const Str& msg,bool DisableLog,int TypeWork)
 {
  if(!(TypeWork&State))return;
  if(!DisableLog)Warning(msg,TypeWork);
  if(isAutonom)return;
  xMessageDlg(msg,mtxWarning);
 }
void TxLogger::ErrorDialog(const Str& msg,bool DisableLog,int TypeWork)
 {
  if(!(TypeWork&State))return;
  if(!DisableLog)Error(msg,TypeWork);
  if(isAutonom)return;
  xMessageDlg(msg,mtxError);
 }
Str DecodeQueryRes(TxQueryRes r)
 {
   switch(r)
   {
    case qrNone    :return "None";
    case qrOk      :return "Ok";
    case qrCancel  :return "Cancel";
    case qrAbort   :return "Abort";
    case qrRetry   :return "Retry";
    case qrIgnore  :return "Ignore";
    case qrYes     :return "Yes";
    case qrNo      :return "No";
    case qrAll     :return "All";
    case qrNoToAll :return "NoToAll";
    case qrYesToAll:return "YesToAll";
    default        :return "???";
   }
 }
void TxLogger::QueryFix(const Str& msg,TxQueryRes R)
 {
  int64 dt = xNow();
  Str Date = GetDate(dt),Time = GetTime(dt);
  Str Res = DecodeQueryRes(R);
  ToLog(msg+">"+Res,Date,Time,lmtQuery);
  ToConsole(msg+">"+Res,Date,Time,lmtQuery);
 }
TxQueryRes TxLogger::QueryOkCancel(const Str& msg,TxQueryRes def)
 {
  TxQueryRes R = def;
  if(!(isAutonom))R = xMessageDlg(msg,mtxQueryOkCancel);
  QueryFix(msg,R);
  return R;
 }
TxQueryRes TxLogger::QueryYesNo(const Str& msg,TxQueryRes def)
 {
  TxQueryRes R = def;
  if(!(isAutonom))R = xMessageDlg(msg,mtxQueryYesNo);
  QueryFix(msg,R);
  return R;
 }
TxQueryRes TxLogger::QueryYesNoCancel(const Str& msg,TxQueryRes def)
 {
  TxQueryRes R = def;
  if(!(isAutonom))R = xMessageDlg(msg,mtxQueryYesNoCancel);
  QueryFix(msg,R);
  return R;
 }
TxQueryRes TxLogger::QueryAbortRetryIgnore(const Str& msg,TxQueryRes def)
 {
  TxQueryRes R = def;
  if(!(isAutonom))R = xMessageDlg(msg,mtxQueryAbortRetryIgnore);
  QueryFix(msg,R);
  return R;
 }
//------------------------------------------------------------------------------
TxLogger*DefaultLogger=0;
TxLogger* GetDefaultLogger()
 {
  if(DefaultLogger==0)
   {
    static TxLogger CrashLogger;
    DefaultLogger = &CrashLogger;
   }
   return DefaultLogger;
 }
void SetDefaultLogger(TxLogger*i){DefaultLogger = i;}
}
//------------------------------------------------------------------------------
#ifndef __GNUC__
#pragma package(smart_init)
#endif
