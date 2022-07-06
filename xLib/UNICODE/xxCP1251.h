#ifndef xxCP1251H
#define xxCP1251H
#include "xxCodePages.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
class TxCodePageCP1251:public IxBaseCodePage
 {
  public:
   TxCodePageCP1251(){Name="WINDOWS-1251";}
   virtual UnicodeChar GetUnicodeChar(const Str & s,int& Pos);
   virtual void AddUnicodeChar(Str&s,UnicodeChar code);
 };
}
//------------------------------------------------------------------------------
#endif
