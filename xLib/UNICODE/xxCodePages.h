#ifndef xxCodePagesH
#define xxCodePagesH
#include "../xxBase.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
class IxBaseCodePage;
extern List<IxBaseCodePage*> CodePages;
IxBaseCodePage*FindCodePage(const Str & Name);
//------------------------------------------------------------------------------
typedef int UnicodeChar;
class IxBaseCodePage
 {
  public:
   Str Name;
   IxBaseCodePage();
   virtual UnicodeChar GetUnicodeChar(const Str & s,int& Pos)=0;
   virtual void AddUnicodeChar(Str&s,UnicodeChar code)=0;
   virtual Str UpperCase(const Str & str){return str;}
   virtual Str LowerCase(const Str & str){return str;}
 };
//------------------------------------------------------------------------------
extern IxBaseCodePage * CurrentCodePage;
//------------------------------------------------------------------------------
Str UnicodeDeCodeStr(const Str&,IxBaseCodePage*From,IxBaseCodePage*To);
Str DeleteCodeChars(const Str&,char changer='?');
}
#endif
