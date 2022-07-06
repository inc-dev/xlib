#ifndef xxLangH
#define xxLangH
#include "../xxBase.h"
#include "../Utils/xxModule.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
class TxLangModule:public IxModule
 {
   Str Error;
  public:
   Str FileName,AltFileName;
   TxLangModule(){}
   virtual bool Init();
   virtual bool Done();
   virtual const char * GetName(){return "LangModule";}
   virtual Str GetLastError(){return Error;};
   inline IxModule*ModuleInterface(){return this;}
   virtual void SetAppVars(IxAppVariables*AV);
 };
Str Translate(const char*s);
inline Str Translate(const Str&s){return Translate(s.c_str());};
}
//------------------------------------------------------------------------------
#endif
