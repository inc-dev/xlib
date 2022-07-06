#ifndef xxDinamicPubObjectH
#define xxDinamicPubObjectH
#include "xxPubObjects.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
typedef PTR<IxBaseObject> PTRxBaseObject;
class TxListOfObjects:public IxListOfObjects
 {
  List<PTRxBaseObject> Items;
  public:
  virtual int First(){return Items.First();};
  virtual int Next(int i){return Items.Next(i);}
  virtual int Count(){return Items.Size();}
  virtual IxBaseObject* GetObject(int i){return Items.Get(i);};
  //---------------------------------------
  virtual void AddItem(IxBaseObject*o){Items.Add(o);}
  virtual void InsertItem(int pos,IxBaseObject*o){Items.Insert(pos,o);}
  virtual int  DeleteItem(int pos){return Items.Delete(pos);};
  virtual int  DeleteItems(int from,int to){return Items.Delete(from,to);};
  virtual void Clear(){Items.Clear();}
 };
class TxDinamicObject:public IxBaseObject
 {
  public:
   Str Name,Val;
   TxListOfObjects Items;
   TxListOfObjects Properties;
   TxDinamicObject(){}
   TxDinamicObject(Str iName){Name = iName;}
   TxDinamicObject(Str iName,Str iVal){ Name = iName; Val = iVal;}
   virtual ~TxDinamicObject(){};
   inline void AddItem(TxDinamicObject*o){Items.AddItem(o);}
   virtual const char* GetName()const{return Name.c_str();}
   virtual void  SetName(const Str& iName){Name = iName;}
   virtual Str GetValueToStr(){return Val;}
   virtual void  SetValueFromStr(const Str&iVal){Val = iVal;}
   virtual IxBaseObject * GetNewItem(const Str& iName,bool isSimpleObject=false);
   virtual IxListOfObjects*GetProperties(){return &Properties;};
   virtual IxListOfObjects*GetItems(){return &Items;};
   //-- Class --
   class Class:public IxBaseClass
    {
     public:
       virtual IxBaseObject*CreateObject(){return (IxBaseObject*)new TxDinamicObject();}
       virtual const char* GetName()const{return "DinamicClass";}
       static Class & Instance(){static Class thisClass;return thisClass;}
    };
   virtual IxBaseClass*GetClass(){return &Class::Instance();};
 };

class TxDinamicClassSpace: public IxClassSpace
 {
   public:
    TxDinamicClassSpace(){RegisterClass(&TxDinamicObject::Class::Instance());}
    virtual const char* GetName()const{return "DinamicClassSpace";}
    virtual IxBaseClass*FindClass(const Str& ClassName){UNUSED(ClassName);return &TxDinamicObject::Class::Instance();}
    virtual IxBaseObject* CreateObject(const Str& ClassName){return (IxBaseObject*)new TxDinamicObject(ClassName);}
    virtual bool RegisterClass(IxBaseClass *Class){Class->ClassSpace = this; return true;};
    static TxDinamicClassSpace & Instance(){static TxDinamicClassSpace t;return t;}    
 };

}
//------------------------------------------------------------------------------
#endif
