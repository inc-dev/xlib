//v1.3
/*
//used
class TTestClass
 {
  int I;
  int getI() {return I;}
  void setI( int a ) {I = a;}
  public:
  PROPERTY(TTestClass,int,J,getI,setI);
 };
class TTestClass2
 {
  int I;
  int getI() {return I;}
  void setI( int a ) {I = a;}
  public:
  PROPERTY(TTestClass2,int,J,getI,setI);
 };

void test()
 {
  TTestClass a,b;
  TTestClass2 c;
  a.J = 5;                            
  b.J = a.J;
  c.J = a.J;
  a.J = a.J+55;
 }
*/
#ifndef xxPropertyH
#define xxPropertyH
//------------------------------------------------------------------------------
#define PROPERTY(iOwnClass,iClass,Name,Get,Set)                                       \
friend class P_##Name;                                                                \
template<class OwnClass,class ThisClass                                               \
  ,ThisClass (OwnClass::*getter)(),void (OwnClass::*setter)(ThisClass) >              \
class P_##Name                                                                        \
 {                                                                                    \
  public:                                                                             \
   inline ThisClass GetValue(){return (Owner()->*getter)();}                          \
   inline void SetValue(ThisClass const& value){(Owner()->*setter)( value );}         \
   inline OwnClass*Owner()                                                            \
     {return(OwnClass*)(((long)this)-((long)&((OwnClass*)8)->Name)+8);}                 \
   inline operator ThisClass(){return GetValue();}                                    \
   inline ThisClass operator=(const ThisClass & value){SetValue(value);return *this;} \
   P_##Name& operator = (P_##Name & prt){SetValue(prt.GetValue());return *this;}      \
 }; P_##Name<iOwnClass,iClass,&iOwnClass::Get,&iOwnClass::Set> Name
//------------------------------------------------------------------------------
#endif
