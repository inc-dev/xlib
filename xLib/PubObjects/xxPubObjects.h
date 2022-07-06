#ifndef xxPubObjectsH
#define xxPubObjectsH
#include "../xxBase.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
class IxBaseObject;
class IxBaseClass;
// abstract domain is
class IxClassSpace
 {
   public:
    virtual const char* GetName()const=0;
    virtual IxBaseObject* CreateObject(const Str & ClassName);
    virtual ~IxClassSpace(){};
    virtual IxBaseClass*FindClass(const Str& ClassName){UNUSED(ClassName);return 0;};
   protected:
    virtual bool RegisterClass(IxBaseClass *)=0;
    friend class IxBaseClass;
 };
//abstract object class
class IxBaseClass
 {
  public:
    IxBaseClass * Parent;
    IxClassSpace *ClassSpace;
    IxBaseClass():Parent(0),ClassSpace(0){}
    virtual~IxBaseClass(){}
    virtual IxBaseObject*CreateObject()=0;
    virtual const char* GetName()const{return "";}
    bool ExistParent(IxBaseClass*);
 };
//abstract list of objects
class IxListOfObjects
 {
  public:
  virtual int First()=0;
  inline bool IsEmpty(){return First()==0;} 
  virtual int Next(int)=0;
  virtual int Find(const Str&);
  virtual IxBaseObject* GetObject(int)=0;
  //---------------------------------------
  virtual void AddItem(IxBaseObject*){}
  virtual void InsertItem(int pos,IxBaseObject*){UNUSED(pos);}
  virtual int  DeleteItem(int pos){UNUSED(pos);return 0;};
  virtual int  DeleteItems(int from,int to){UNUSED(from);UNUSED(to);return 0;};
 };
// abstract object domain
class IxBaseObject
 {
  public:
   virtual const char* GetName()const=0;
   virtual void  SetName(const Str&){};
   virtual Str GetValueToStr()=0;
   virtual void  SetValueFromStr(const Str&)=0;
   virtual IxBaseObject * GetNewItem(const Str&,bool isSimpleObject=false){UNUSED(isSimpleObject);return 0;};
   virtual ~IxBaseObject(){};
   virtual IxBaseClass*GetClass(){return 0;};
   //----------------------------------------
   virtual IxListOfObjects*GetProperties(){return 0;};
   virtual IxListOfObjects*GetItems(){return 0;};
   virtual IxBaseObject*GetOwner(){return 0;}
   virtual IxBaseObject*GetEnum(){return 0;}//Items with id[,Name]
   //-----------------
   bool AssignFromObject(IxBaseObject*);
   IxBaseObject * CreateClone();
 };

}
//------------------------------------------------------------------------------
#endif
