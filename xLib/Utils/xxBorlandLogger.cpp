#pragma hdrstop
#include "xxBorlandLogger.h"
#include "UtilsColor.hpp"
//------------------------------------------------------------------------------
namespace XSPACE
{
static const int clBlack   = 0x0;
static const int clMaroon  = 0x80;
static const int clGreen   = 0x8000;
static const int clOlive   = 0x8080;
static const int clNavy    = 0x800000;
static const int clPurple  = 0x800080;
static const int clTeal    = 0x808000;
static const int clGray    = 0x808080;
static const int clSilver  = 0xc0c0c0;
static const int clRed     = 0xff;
static const int clLime    = 0xff00;
static const int clYellow  = 0xffff;
static const int clBlue    = 0xff0000;
static const int clFuchsia = 0xff00ff;
static const int clAqua    = 0xffff00;
static const int clLtGray  = 0xc0c0c0;
static const int clDkGray  = 0x808080;
static const int clWhite   = 0xffffff;
static const int clSkyBlue = 0xf0caa6;

int C_Face     = clBlack;
int C_DataTime = clYellow;
int C_Message  = clLime;
int C_Query    = clSkyBlue;
int C_Warning  = clFuchsia;
int C_Error    = clRed;

TxBorlandLogger BorlandLogger;
TxQueryRes TxBorlandLogger::xMessageDlg(const Str & msg,TxMessageDlgType MDT,TxQueryRes )
 {
  TMsgDlgButtons b;
  TMsgDlgType DlgType = mtConfirmation;
  switch(MDT)
   {
   case mtxMessage:b<<mbOK;DlgType = mtInformation; break;
   case mtxWarning:b<<mbOK;DlgType = mtWarning; break;
   case mtxError  :b<<mbOK;DlgType = mtError; break;
//------------------------------------------------------------
   case mtxQueryOkCancel   :b<<mbOK<<mbCancel; break;
   case mtxQueryYesNo      :b<<mbYes<<mbNo; break;
   case mtxQueryYesNoCancel:b<<mbYes<<mbNo<<mbCancel; break;
   case mtxQueryAbortRetryIgnore:b<<mbAbort<<mbRetry<<mbIgnore; break;
   }
  return (TxQueryRes)MessageDlg(msg.c_str(),DlgType, b, 0);
 }
Str ColorToStr(int color)
 {
   char*a=(char*)&color;
   return Str("{c:")+BinToHexStr(a+3,1)+BinToHexStr(a+2,1)+BinToHexStr(a+1,1)+BinToHexStr(a,1)+'}';
 }
Str CorrectConsoleMessage(Str mess)
 {
  for(int i=1;i<=mess.Size();i++)
   if(mess[i]>=0&&mess[i]<32)mess[i]=32;
  return mess; 
 }
bool TxBorlandLogger::ToConsole(const Str & mess,const Str & date,const Str & time,TxMessType mt)
 {
  if(Console)
   {
    Str s=ColorToStr(C_DataTime);
    if(isPrintToConsoleDate)s=date+' ';
    s+=time+':';
    s+=' ';
    switch(mt)
     {
      case lmtMess: s+=ColorToStr(C_Message); break;
      case lmtWarning: s+=ColorToStr(C_Warning)+"WARNING:"; break;
      case lmtError: s+=ColorToStr(C_Error)+"ERROR:"; break;
      case lmtQuery: s+=ColorToStr(C_Query)+"QUERY:"; break;
     };
    s+=CorrectConsoleMessage(mess);
    AddLineToRichEdit(Console,s.c_str());
   }
  return true;
 }
void TxBorlandLogger::SetConsole(TRichEdit*iConsole)
 {
  Console = iConsole;
  if(Console)
   {
    Console->Color=(TColor)C_Face;
    Console->Lines->Clear();
    Console->WordWrap=false;
    Console->ScrollBars=ssVertical;
    Console->HideScrollBars=false;
    Console->ReadOnly = true;
    Console->TabStop = false;
   }
 }
}
//------------------------------------------------------------------------------
#pragma package(smart_init)
