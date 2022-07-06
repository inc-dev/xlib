#ifndef xxLoggerH
#define xxLoggerH
#include "../xxBase.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
const int lsUser=-1,lsPerfomance=2,lsHardWare=4,lsProtocol=8,lsFunctional=16, lsDebug=lsProtocol|lsFunctional|lsPerfomance;
enum TxQueryRes {qrNone = 0x0,qrOk = 0x1,qrCancel = 0x2,qrAbort = 0x3,
                 qrRetry = 0x4,qrIgnore = 0x5,qrYes = 0x6,qrNo = 0x7,
                 qrAll = 0x8,qrNoToAll = 0x9,qrYesToAll = 0xa};
enum TxMessageDlgType {mtxMessage,mtxWarning,mtxError
            ,mtxQueryOkCancel,mtxQueryYesNo,mtxQueryYesNoCancel
            ,mtxQueryAbortRetryIgnore};
Str DecodeQueryRes(TxQueryRes r);
class TxLogger
 {
  public:
   bool isAutonom;
   bool isAppStoped;
   bool isPrintToConsoleDate;
   int State;//ls
   Str LastMessage,LastWarning,LastError,LogFile;
   List<Str> RecentActionsList;
   TxLogger():isAutonom(false),isAppStoped(false),isPrintToConsoleDate(false),State(1),LogFile("program.log")
   { }
   void Mess(const Str& msg,int TypeWork=1);
   void Warning(const Str& msg,int TypeWork=1);
   void Error(const Str& msg,int TypeWork=1);
   void MessDialog(const Str& msg,bool DisableLog=false,int TypeWork=1);
   void WarningDialog(const Str& msg,bool DisableLog=false,int TypeWork=1);
   void ErrorDialog(const Str& msg,bool DisableLog=false,int TypeWork=1);

   TxQueryRes QueryOkCancel(const Str& msg,TxQueryRes def = qrOk);
   TxQueryRes QueryYesNo(const Str& msg,TxQueryRes def = qrYes);
   TxQueryRes QueryYesNoCancel(const Str& msg,TxQueryRes def = qrYes);
   TxQueryRes QueryAbortRetryIgnore(const Str& msg,TxQueryRes def = qrIgnore);


   enum TxMessType{lmtMess,lmtWarning,lmtError,lmtQuery};

   void RecentActions(const Str& msg);
  protected:
   void QueryFix(const Str& msg,TxQueryRes r);
   virtual bool ToLog(const Str & mess,const Str & date,const Str & time,TxMessType);
   virtual Str GetDate(int64);
   virtual Str GetTime(int64);
   //need override
   virtual TxQueryRes xMessageDlg(const Str & msg,TxMessageDlgType MDT,TxQueryRes def=qrNone)
    {UNUSED(msg);UNUSED(MDT);return def;};
   virtual bool ToConsole(const Str & mess,const Str & date,const Str & time,TxMessType)
    {UNUSED(mess);UNUSED(date);UNUSED(time);return false;};
 };
//---------------------------------------
TxLogger* GetDefaultLogger();
void  SetDefaultLogger(TxLogger*);
//---------------------------------------
inline void Mess(const Str& msg,int TypeWork=lsUser){GetDefaultLogger()->Mess(msg,TypeWork);}
inline void Warning(const Str& msg,int TypeWork=lsUser){GetDefaultLogger()->Warning(msg,TypeWork);}
inline void Error(const Str& msg,int TypeWork=lsUser){GetDefaultLogger()->Error(msg,TypeWork);}
inline void MessDialog(const Str& msg,bool DisableLog=false,int TypeWork=lsUser){GetDefaultLogger()->MessDialog(msg,DisableLog,TypeWork);}
inline void WarningDialog(const Str& msg,bool DisableLog=false,int TypeWork=lsUser){GetDefaultLogger()->WarningDialog(msg,DisableLog,TypeWork);}
inline void ErrorDialog(const Str& msg,bool DisableLog=false,int TypeWork=lsUser){GetDefaultLogger()->ErrorDialog(msg,DisableLog,TypeWork);}

inline TxQueryRes QueryOkCancel(const Str& msg,TxQueryRes def = qrOk){return GetDefaultLogger()->QueryOkCancel(msg,def);}
inline TxQueryRes QueryYesNo(const Str& msg,TxQueryRes def = qrYes){return GetDefaultLogger()->QueryYesNo(msg,def);}
inline TxQueryRes QueryYesNoCancel(const Str& msg,TxQueryRes def = qrYes){return GetDefaultLogger()->QueryYesNoCancel(msg,def);}
inline TxQueryRes QueryAbortRetryIgnore(const Str& msg,TxQueryRes def = qrIgnore){return GetDefaultLogger()->QueryAbortRetryIgnore(msg,def);}
inline void RecentActions(const Str& msg)
 {
  UNUSED(msg);//GetDefaultLogger()->RecentActions(msg);
 }

Str DecodeMessType(TxLogger::TxMessType r);
Str DecodeQueryRes(TxQueryRes r);
}    

//------------------------------------------------------------------------------
#endif
