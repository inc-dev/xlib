#ifndef xxConsoleLoggerH
#define xxConsoleLoggerH
#include "xxLogger.h"
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#endif
//------------------------------------------------------------------------------
namespace XSPACE
{
class TxConsoleLogger:public TxLogger
 {
  protected:
   virtual TxQueryRes xMessageDlg(const Str & msg,TxMessageDlgType MDT,TxQueryRes def=qrNone);
   virtual bool ToConsole(const Str & mess,const Str & date,const Str & time,TxMessType mt);
 };
extern TxConsoleLogger ConsoleLogger;
}
//------------------------------------------------------------------------------
#endif
