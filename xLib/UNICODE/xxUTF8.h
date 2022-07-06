#ifndef xxUTF8H
#define xxUTF8H
#include "xxCodePages.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
class TxCodePageUTF8:public IxBaseCodePage
 {
  public:
   TxCodePageUTF8(){Name="UTF-8";}
   virtual UnicodeChar GetUnicodeChar(const Str & s,int& Pos);
   virtual void AddUnicodeChar(Str&s,UnicodeChar code);
 };
 }
//------------------------------------------------------------------------------
#endif
