#ifndef xxBorlandLoggerH
#define xxBorlandLoggerH
#include "xxLogger.h"
#include <ComCtrls.hpp>
#include <vcl.h>
//------------------------------------------------------------------------------
namespace XSPACE
{
class TxBorlandLogger:public TxLogger
 {
  public:
   TxBorlandLogger():Console(0){}
   void SetConsole(TRichEdit* iConsole);
  protected:
   TRichEdit* Console;
   virtual TxQueryRes xMessageDlg(const Str & msg,TxMessageDlgType MDT,TxQueryRes def=qrNone);
   virtual bool ToConsole(const Str & mess,const Str & date,const Str & time,TxMessType mt);
 };
extern TxBorlandLogger BorlandLogger;

extern int C_Face;
extern int C_DataTime;
extern int C_Message;
extern int C_Query;
extern int C_Warning;
extern int C_Error;

}


//------------------------------------------------------------------------------
#endif
