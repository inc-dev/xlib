#ifndef xxModuleH
#define xxModuleH
#include"../xxBase.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
class IxAppVariables
 {
  public:
   virtual Str GetConfigDir()=0;
   virtual Str GetAppDir()=0;
   virtual Str GetCurrentDir()=0;
 };
class IxModule
 {
  public:
   Str LastError;
   virtual ~IxModule(){}
   virtual void SetAppVars(IxAppVariables*){};
   virtual bool Init(){return true;};
   virtual bool Done(){return true;};
   virtual const char * GetName()=0;
   virtual Str GetLastError(){return LastError;};
   inline IxModule*ModuleInterface(){return this;}
   virtual void TranslateItems(){};
 };
class TxModuleContainer:public IxModule
 {
  protected:
   List< IxModule* > Modules;
  public:
   virtual void SetAppVars(IxAppVariables*);
   virtual void MainSetAppVars(IxAppVariables*){};
   virtual bool Init();
   virtual bool Done();
   virtual bool MainInit(){return true;};
   virtual bool MainDone(){return true;};
   virtual void MainTranslateItems(){}
   virtual void TranslateItems();
 };

}
//------------------------------------------------------------------------------
#endif
