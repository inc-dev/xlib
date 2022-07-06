#ifndef xxSupportDLLH
#define xxSupportDLLH
#include "..\xLib\xxBase.h"
namespace XSPACE
{
#define DLL_FUN_Agreement __stdcall
//#define DLL_FUN_Agreement __cdecl
class IxSupportDLL
 {
  protected:
    public:
   HINSTANCE hDLL;
   TxAtom Locker;
   bool internalLoadLib();
   bool internalFreeLib();
   IxSupportDLL(){hDLL = 0; Locker = 0;}
   virtual ~IxSupportDLL(){if(hDLL!=0)internalFreeLib();}
    class TinternSynchronization
      {  public: int64 value;TinternSynchronization():value(0){} };
    TinternSynchronization Synchronization;
  public:
   Str LastError;
   inline bool LockDLL(){if(Locker.LockedInc()==1)return internalLoadLib(); return true;}
   inline bool UnLockDLL(){if(Locker.LockedDec()==0)return internalFreeLib(); return true;}
   virtual char* DDLName()=0;
 };
//   typedef int  ( DLL_FUN_Agreement  *TAddRecAdjust) (double Sum, char *Text );
//   регистраци€ функции без параметров и возращ€юща€ переменную типа указаного в первом параметре
//   пример  RegisterDLLProcedureParam0(Init); Init();
   #define RegisterDLLProcedureParam0(NeedFunction)                   \
   TinternSynchronization Synchronization_##NeedFunction;             \
   typedef  void (DLL_FUN_Agreement *Tfun_##NeedFunction)();          \
   Tfun_##NeedFunction fun_##NeedFunction;                            \
   void NeedFunction()                                                \
     {                                                                \
      if(Synchronization.value==0) throw "not load dll";              \
      if(Synchronization_##NeedFunction.value!=Synchronization.value) \
       {                                                              \
         fun_##NeedFunction = (Tfun_##NeedFunction)GetProcAddress (hDLL, #NeedFunction);  \
         if(fun_##NeedFunction==0) throw "not load fun "###NeedFunction;                  \
         Synchronization_##NeedFunction.value=Synchronization.value;  \
       }                                                              \
      fun_##NeedFunction();                                           \
     }
//   регистраци€ функции без параметров и возращ€юща€ переменную типа указаного в первом параметре
//   пример  RegisterDLLFunctionParam0(int,MyFun);  int i = MyFun();
   #define RegisterDLLFunctionParam0(TRetVal,NeedFunction)            \
   TinternSynchronization Synchronization_##NeedFunction;             \
   typedef  TRetVal (DLL_FUN_Agreement *Tfun_##NeedFunction)();       \
   Tfun_##NeedFunction fun_##NeedFunction;                            \
   TRetVal NeedFunction()                                             \
     {                                                                \
      if(Synchronization.value==0) throw "not load dll";              \
      if(Synchronization_##NeedFunction.value!=Synchronization.value) \
       {                                                              \
         fun_##NeedFunction = (Tfun_##NeedFunction)GetProcAddress (hDLL, #NeedFunction);  \
         if(fun_##NeedFunction==0) throw "not load fun "###NeedFunction;                  \
         Synchronization_##NeedFunction.value=Synchronization.value;  \
       }                                                              \
      return fun_##NeedFunction();                                    \
     }
//   регистраци€ функции с 1м параметром и возращ€юща€ переменную типа указаного в первом параметре
//   пример  RegisterDLLFunctionParam1(int,MyFun,int);  int i = MyFun(1);
   #define RegisterDLLFunctionParam1(TRetVal,NeedFunction,param1)     \
   TinternSynchronization Synchronization_##NeedFunction;             \
   typedef  TRetVal (DLL_FUN_Agreement *Tfun_##NeedFunction)(param1); \
   Tfun_##NeedFunction fun_##NeedFunction;                            \
   TRetVal NeedFunction(param1 vparam1)                               \
     {                                                                \
      if(Synchronization.value==0) throw "not load dll";              \
      if(Synchronization_##NeedFunction.value!=Synchronization.value) \
       {                                                              \
         fun_##NeedFunction = (Tfun_##NeedFunction)GetProcAddress (hDLL, #NeedFunction);  \
         if(fun_##NeedFunction==0) throw "not load fun "###NeedFunction;                  \
         Synchronization_##NeedFunction.value=Synchronization.value;  \
       }                                                              \
      return fun_##NeedFunction(vparam1);                             \
     }
//   регистраци€ функции с 2м€ параметрами и возращ€юща€ переменную типа указаного в первом параметре
//   пример  RegisterDLLFunctionParam2(int,MyFun,int,int);  int i = MyFun(1,2);
   #define RegisterDLLFunctionParam2(TRetVal,NeedFunction,param1,param2)\
   TinternSynchronization Synchronization_##NeedFunction;               \
   typedef  TRetVal (DLL_FUN_Agreement *Tfun_##NeedFunction)(param1,param2);  \
   Tfun_##NeedFunction fun_##NeedFunction;                            \
   TRetVal NeedFunction(param1 vparam1,param2 vparam2)                \
     {                                                                \
      if(Synchronization.value==0) throw "not load dll";              \
      if(Synchronization_##NeedFunction.value!=Synchronization.value) \
       {                                                              \
         fun_##NeedFunction = (Tfun_##NeedFunction)GetProcAddress (hDLL, #NeedFunction);  \
         if(fun_##NeedFunction==0) throw "not load fun "###NeedFunction;                  \
         Synchronization_##NeedFunction.value=Synchronization.value;  \
       }                                                              \
      return fun_##NeedFunction(vparam1,vparam2);                     \
     }
//   регистраци€ функции с 3м€ параметрами и возращ€юща€ переменную типа указаного в первом параметре
//   пример  RegisterDLLFunctionParam3(int,MyFun,int,int,int);  int i = MyFun(1,2,3);
   #define RegisterDLLFunctionParam3(TRetVal,NeedFunction,param1,param2,param3)\
   TinternSynchronization Synchronization_##NeedFunction;                      \
   typedef  TRetVal (DLL_FUN_Agreement *Tfun_##NeedFunction)(param1,param2,param3);\
   Tfun_##NeedFunction fun_##NeedFunction;                            \
   TRetVal NeedFunction(param1 vparam1,param2 vparam2,param3 vparam3) \
     {                                                                \
      if(Synchronization.value==0) throw "not load dll";              \
      if(Synchronization_##NeedFunction.value!=Synchronization.value) \
       {                                                              \
         fun_##NeedFunction = (Tfun_##NeedFunction)GetProcAddress (hDLL, #NeedFunction);  \
         if(fun_##NeedFunction==0) throw "not load fun "###NeedFunction;                  \
         Synchronization_##NeedFunction.value=Synchronization.value;  \
       }                                                              \
      return fun_##NeedFunction(vparam1,vparam2,vparam3);             \
     }
//   регистраци€ функции с 4м€ параметрами и возращ€юща€ переменную типа указаного в первом параметре
//   пример  RegisterDLLFunctionParam4(int,MyFun,int,int,int,int);  int i = MyFun(1,2,3,4);
   #define RegisterDLLFunctionParam4(TRetVal,NeedFunction,param1,param2,param3,param4)   \
   TinternSynchronization Synchronization_##NeedFunction;                                \
   typedef  TRetVal (DLL_FUN_Agreement Tfun_##NeedFunction)(param1,param2,param3,param4);\
   Tfun_##NeedFunction * fun_##NeedFunction;                                             \
   TRetVal NeedFunction(param1 vparam1,param2 vparam2,param3 vparam3,param4 vparam4)     \
     {                                                                 \
      if(Synchronization.value==0) throw "not load dll";               \
      if(Synchronization_##NeedFunction.value!=Synchronization.value)  \
       {                                                               \
         fun_##NeedFunction = (Tfun_##NeedFunction*)GetProcAddress (hDLL, #NeedFunction);  \
         if(fun_##NeedFunction==0) throw "not load fun "###NeedFunction;                   \
         Synchronization_##NeedFunction.value=Synchronization.value;   \
       }                                                               \
      return fun_##NeedFunction(vparam1,vparam2,vparam3,vparam4);      \
     }
//   регистраци€ функции с 5м€ параметрами и возращ€юща€ переменную типа указаного в первом параметре
//   пример  RegisterDLLFunctionParam5(int,MyFun,int,int,int,int,int);  int i = MyFun(1,2,3,4,5);
   #define RegisterDLLFunctionParam5(TRetVal,NeedFunction,param1,param2,param3,param4,param5)      \
   TinternSynchronization Synchronization_##NeedFunction;                                          \
   typedef  TRetVal (DLL_FUN_Agreement Tfun_##NeedFunction)(param1,param2,param3,param4,param5);   \
   Tfun_##NeedFunction * fun_##NeedFunction;                                                       \
   TRetVal NeedFunction(param1 vparam1,param2 vparam2,param3 vparam3,param4 vparam4,param5 vparam5)\
     {                                                                 \
      if(Synchronization.value==0) throw "not load dll";               \
      if(Synchronization_##NeedFunction.value!=Synchronization.value)  \
       {                                                               \
         fun_##NeedFunction = (Tfun_##NeedFunction*)GetProcAddress (hDLL, #NeedFunction);  \
         if(fun_##NeedFunction==0) throw "not load fun "###NeedFunction;                   \
         Synchronization_##NeedFunction.value=Synchronization.value;   \
       }                                                               \
      return fun_##NeedFunction(vparam1,vparam2,vparam3,vparam4,vparam5);      \
     }

/*
//todo
 #define RegisterDLLMetodByType(NeedFunction) \
  Method = (T##NeedFunction)GetProcAddress(hDLL,#NeedFunction);\
  if(Method==0){LastError = DDLName()+Str(" ")+Translate("don`t load method")+' '+#NeedFunction;return false;}

virtual bool RegisterDLLMetods()
 {
    RegisterDLLMetod(NeedFunction);//Need type TNeedFunction
 }
*/
}
#endif
