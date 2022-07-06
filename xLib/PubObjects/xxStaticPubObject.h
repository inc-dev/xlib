#ifndef xxStaticPubObjectH
#define xxStaticPubObjectH
#include "xxPubObjects.h"
namespace XSPACE
{
//------------------------------------------------------------------------------
class IxStaticClassSpace: public IxClassSpace
 {
   public:
    List<IxBaseClass*>    ClassList;
    List<IxClassSpace*>   IncludingClassSpacesList;
    virtual const char* GetName()const{return "StaticClassSpace";}
    virtual IxBaseClass*FindClass(const Str& ClassName);
    virtual bool RegisterClass(IxBaseClass *);
 };
//------------------------------------------------------------------------------
typedef IxBaseObject (IxBaseObject::*PStaticObjProperty);
#define PublishedProperty(Name) RegStaticProperty((PStaticObjProperty)&ObjType::Name)
class IxBaseStaticClass: public IxBaseClass
 {
  public:
    List<PStaticObjProperty> RefProperties;
    void RegStaticProperty(PStaticObjProperty PProperty){RefProperties.Add(PProperty);}
 };
//--
template<class BaseObject,class TypeParent = IxBaseStaticClass >
class I2xBaseStaticClass: public TypeParent
 {
  public:
    virtual IxBaseObject*CreateObject(){return new BaseObject();};
    virtual const char* GetName()const{return BaseObject::GetClassName();}
 };
template<class BaseObject,class TypeParent = IxBaseStaticClass >
class I2xAbstractBaseStaticClass: public TypeParent
 {
  public:
    virtual IxBaseObject*CreateObject(){return 0;};
    virtual const char* GetName()const{return BaseObject::GetClassName();}
 };
//--
template<class BaseObject,class Class = I2xBaseStaticClass< BaseObject> >
class TxStaticClass: public I2xBaseStaticClass<BaseObject>
 {
   public:
    static Class & Instance(){static Class thisClass;return thisClass;}
 };
template<class BaseObject,class Class = I2xAbstractBaseStaticClass< BaseObject > >
class TxAbstractStaticClass: public I2xAbstractBaseStaticClass<BaseObject>
 {
   public:
    static Class & Instance(){static Class thisClass;return thisClass;}
 };
template<class TypeParent, class BaseObject,class Class = I2xBaseStaticClass< BaseObject,TypeParent> >
class TxInheritableStaticClass: public I2xBaseStaticClass<BaseObject,TypeParent>
 {
   public:
    TxInheritableStaticClass(){I2xBaseStaticClass<BaseObject,TypeParent>::Parent = &TypeParent::Instance();}
    static Class & Instance(){static Class thisClass;return thisClass;}
 };
template<class TypeParent, class BaseObject,class Class = I2xAbstractBaseStaticClass< BaseObject,TypeParent > >
class TxInheritableAbstractStaticClass: public I2xAbstractBaseStaticClass<BaseObject,TypeParent>
 {
   public:
    TxInheritableAbstractStaticClass(){I2xAbstractBaseStaticClass<BaseObject,TypeParent>::Parent = &TypeParent::Instance();}
    static Class & Instance(){static Class thisClass;return thisClass;}
 };
//------------------------------------------------------------------------------
class IxStaticObject:public IxBaseObject
 {
  public:
   typedef IxStaticObject ObjType;
   typedef TxAbstractStaticClass<ObjType> Class;
   typedef Str ValueType;
   virtual Str GetValueToStr(){return "";};
   virtual void  SetValueFromStr(const Str&){};
 };
template<class TxFinalObject,class Parent = IxStaticObject>
class TxStaticObject: public Parent
 {
  public:
   typedef TxFinalObject ObjType;
   typedef Parent ParentObjType;
   //--------------------------------
   virtual const char* GetName()const{return TxFinalObject::GetClassName();}
   virtual IxBaseClass*GetClass(){return &TxFinalObject::Class::Instance();};
   //--------------------------------
   class TxStaticPropertyListOfObjects:public IxListOfObjects
    {
     public:
     inline TxStaticObject*Owner(){return(TxStaticObject<TxFinalObject,Parent>*)(((long)this)-((long)&((TxStaticObject<TxFinalObject,Parent>*)8)->SupportProperties)+8);}
     inline IxBaseStaticClass*OWN_CLS(){return (IxBaseStaticClass*)Owner()->GetClass();}
     virtual int First(){return OWN_CLS()->RefProperties.First();};
     virtual int Next(int i){return OWN_CLS()->RefProperties.Next(i);};
     virtual IxBaseObject* GetObject(int i){return &(Owner()->*(OWN_CLS()->RefProperties.Get(i)));};
    } SupportProperties;
   virtual IxListOfObjects*GetProperties(){return &SupportProperties;};
   virtual IxBaseObject * GetNewItem(const Str& Name,bool isSimpleObject=false)
    {
     UNUSED(isSimpleObject);
     int index = SupportProperties.Find(Name);
     if(index)return SupportProperties.GetObject(index);
     return 0;
    };
 };
//------------------------------------------------------------------------------
#define ObjProperty(ObjectType,Name) ObjPropertyEx(ObjectType,Name,#Name)
#define ObjPropertyEx(ObjectType,Name,CharName)                                \
template<class iObjType,class OwnerType>                                       \
class ObjProperty_##Name:public iObjType                                       \
  {                                                                            \
   public:                                                                     \
    typedef ObjProperty_##Name<iObjType,OwnerType> ObjType;                    \
    typedef typename iObjType::ValueType ValueType;                            \
  inline OwnerType*Owner()                                                     \
     {return(OwnerType*)(((long)this)-((long)&((OwnerType*)8)->Name)+8);}      \
   virtual const char* GetName()const{return CharName;}                        \
   virtual IxBaseObject*GetOwner(){return (IxBaseObject*)Owner();}             \
   operator ValueType(){return iObjType::GetValue();}                          \
   ObjType& operator=(ValueType i){iObjType::SetValue(i);return *this;}        \
   friend bool operator==(ObjType o,ValueType i){return o.GetValue()==i;}      \
   friend bool operator==(ValueType i,ObjType o){return o.GetValue()==i;}      \
   friend bool operator!=(ObjType o,ValueType i){return o.GetValue()!=i;}      \
   friend bool operator!=(ValueType i,ObjType o){return o.GetValue()!=i;}      \
   friend bool operator>(ObjType o,ValueType i){return o.GetValue()>i;}        \
   friend bool operator>(ValueType i,ObjType o){return o.GetValue()<i;}        \
   friend bool operator<(ObjType o,ValueType i){return o.GetValue()<i;}        \
   friend bool operator<(ValueType i,ObjType o){return o.GetValue()>i;}        \
   friend bool operator>=(ObjType o,ValueType i){return o.GetValue()>=i;}      \
   friend bool operator>=(ValueType i,ObjType o){return o.GetValue()<=i;}      \
   friend bool operator<=(ObjType o,ValueType i){return o.GetValue()<=i;}      \
   friend bool operator<=(ValueType i,ObjType o){return o.GetValue()>=i;}      \
  }; ObjProperty_##Name< ObjectType , ObjType > Name
#define ObjPropertyHookSet(ObjectType,Name,OwnProcSet) ObjPropertyHookSetEx(ObjectType,Name,OwnProcSet,#Name)
#define ObjPropertyHookSetEx(ObjectType,Name,OwnProcSet,CharName)              \
template<class iObjType,class OwnerType>                                       \
class ObjProperty_##Name:public iObjType                                       \
  {                                                                            \
   public:                                                                     \
    typedef ObjProperty_##Name<iObjType,OwnerType> ObjType;                    \
    typedef typename iObjType::ValueType ValueType;                            \
  inline OwnerType*Owner()                                                     \
     {return(OwnerType*)(((long)this)-((long)&((OwnerType*)8)->Name)+8);}      \
   virtual const char* GetName()const{return CharName;}                        \
   virtual IxBaseObject*GetOwner(){return (IxBaseObject*)Owner();}             \
   operator ValueType(){return iObjType::GetValue();}                          \
   ObjType& operator=(ValueType i){SetValue(i);return *this;}                  \
   virtual void SetValue(const ValueType& newValue)                            \
    {ValueType i=newValue;if(Owner()->OwnProcSet(i))ObjectType::SetValue(i); } \
   friend bool operator==(ObjType o,ValueType i){return o.GetValue()==i;}      \
   friend bool operator==(ValueType i,ObjType o){return o.GetValue()==i;}      \
   friend bool operator!=(ObjType o,ValueType i){return o.GetValue()!=i;}      \
   friend bool operator!=(ValueType i,ObjType o){return o.GetValue()!=i;}      \
   friend bool operator>(ObjType o,ValueType i){return o.GetValue()>i;}        \
   friend bool operator>(ValueType i,ObjType o){return o.GetValue()<i;}        \
   friend bool operator<(ObjType o,ValueType i){return o.GetValue()<i;}        \
   friend bool operator<(ValueType i,ObjType o){return o.GetValue()>i;}        \
   friend bool operator>=(ObjType o,ValueType i){return o.GetValue()>=i;}      \
   friend bool operator>=(ValueType i,ObjType o){return o.GetValue()<=i;}      \
   friend bool operator<=(ObjType o,ValueType i){return o.GetValue()<=i;}      \
   friend bool operator<=(ValueType i,ObjType o){return o.GetValue()>=i;}      \
  }; ObjProperty_##Name< ObjectType , ObjType > Name
//------------------------------------------------------------------------------
template<class TypeItem, class Container>
class TxStaticListOfObjects: public IxListOfObjects
 {
  public:
   inline IxBaseClass*ClassItems(){return &TypeItem::Class::Instance();}
   virtual int First(){return Items.First();};
   virtual int Next(int i){return Items.Next(i);}
   virtual IxBaseObject* GetObject(int i){return Items.Get(i);};
           PTR<TypeItem>& Get(int i){return Items.Get(i);};
   int Prev(int i){return Items.Prev(i);}
   int Last() {return Items.Last();};
   virtual void AddItem(IxBaseObject*o){Items.Add((TypeItem*)o);}
           void Add(const PTR<TypeItem> o){Items.Add(o);}
   virtual void InsertItem(int pos,const PTR<TypeItem> o){Items.Insert(pos,o);}
   virtual int DeleteItem(int pos){pos=Items.Delete(pos);return pos;};
   virtual int DeleteItems(int from,int to){from=Items.Delete(from,to);return from;};
   virtual void Clear(){Items.Clear();};
   inline int GetCount(){return Items.Size();}
  protected:
   Container Items;
 };
template<class TxFinalObject,class TypeItem,class Container>
class TxStaticContainerObject: public TxStaticObject<TxFinalObject>
 {
  public:
    Container Items;
    virtual IxBaseObject * GetListNewItem(const Str& Name)
     {
      IxBaseClass*ItemClass = &TypeItem::Class::Instance();
      if(ItemClass->GetName()!=Name)
       {
        if(ItemClass->ClassSpace==0)return 0;
        IxBaseClass*ChildItemClass = ItemClass->ClassSpace->FindClass(Name);
        if(ChildItemClass==0)return 0;
        if(!ChildItemClass->ExistParent(ItemClass))return 0;
        ItemClass = ChildItemClass;
       }
      IxBaseObject* o = ItemClass->CreateObject();
      Items.AddItem(o);
      return o;
     }
   virtual IxListOfObjects*GetItems(){return &Items;};
   virtual IxBaseObject * GetNewItem(const Str& Name,bool isSimpleObject=false)
    {
     IxBaseObject * Property = TxStaticObject<TxFinalObject>::GetNewItem(Name,isSimpleObject);
     if(Property!=0)return Property;
     return GetListNewItem(Name);
    };
 };
template<class TxFinalObject,class TypeItem>
class TxStaticItemsListObject:public TxStaticContainerObject<TxFinalObject,TypeItem, TxStaticListOfObjects<TypeItem, List< PTR < TypeItem> > >   >{};

template<class TxFinalObject,class TypeItem>
class TxStaticItemsArrayObject:public TxStaticContainerObject<TxFinalObject,TypeItem, TxStaticListOfObjects<TypeItem, Array< PTR < TypeItem> > >   >{};
//------------------------------------------------------------------------------
class ObjStr:public TxStaticObject<ObjStr>
 {
  public:
   typedef Str ValueType;
   static const char* GetClassName(){return "String";}
   typedef TxStaticClass<ObjType> Class;
   //-----------------
   virtual ValueType GetValue(){return Value;};
   virtual void SetValue(const ValueType&s){Value = s;}
   inline const char* c_str(){return Value.c_str();}
   //-----------------
   virtual Str GetValueToStr(){return GetValue();};
   virtual void  SetValueFromStr(const Str&s){SetValue(s);};

   operator ValueType(){return GetValue();}
   ObjType& operator=(const ValueType& i){SetValue(i);return *this;}
  protected:
   ValueType Value;
 };
//------------------------------------------------------------------------------
class ObjInt:public TxStaticObject<ObjInt>
 {
  public:
   typedef int ValueType;
   static const char* GetClassName(){return "Int";}
   typedef TxStaticClass<ObjType> Class;
   //-----------------
   virtual ValueType GetValue(){return Value;};
   virtual void SetValue(const ValueType& i){Value = i;}
   //-----------------
   virtual Str GetValueToStr(){ValueType i = GetValue();if(i)return NumToStr(i);else return "";};
   virtual void  SetValueFromStr(const Str&s){if(s.Size())SetValue(StrToInt(s));else{SetValue(0);}};
   //-----------------
   operator ValueType(){return GetValue();}
   ObjType& operator=(const ValueType& i){SetValue(i);return *this;}
   ObjInt():Value(0){}
  protected:
   ValueType Value;
 };
//------------------------------------------------------------------------------
class ObjInt64:public TxStaticObject<ObjInt64>
 {
  public:
   typedef int64 ValueType;
   static const char* GetClassName(){return "Int64";}
   typedef TxStaticClass<ObjType> Class;
   //-----------------
   virtual ValueType GetValue(){return Value;};
   virtual void SetValue(const ValueType& i){Value = i;}
   //-----------------
   virtual Str GetValueToStr(){ValueType i = GetValue();if(i)return NumToStr(i);else return "";};
   virtual void  SetValueFromStr(const Str&s){if(s.Size())SetValue(StrToInt64(s));else{SetValue(0);}};
   //-----------------
   operator ValueType(){return GetValue();}
   ObjType& operator=(const ValueType& i){SetValue(i);return *this;}
   ObjInt64():Value(0){}
  protected:
   ValueType Value;
 };
//------------------------------------------------------------------------------
class ObjDouble:public TxStaticObject<ObjDouble>
 {
  public:
   typedef double ValueType;
   static const char* GetClassName(){return "Double";}
   typedef TxStaticClass<ObjType> Class;
   //-----------------
   virtual ValueType GetValue(){return Value;};
   virtual void SetValue(const ValueType& i){Value = i;}
   //-----------------
   virtual Str GetValueToStr(){ValueType i = GetValue();if(i)return NumToStr(i);else return "";};
   virtual void  SetValueFromStr(const Str&s){if(s.Size())SetValue(StrToDouble(s));else{SetValue(0.0);}};
   //-----------------
   operator ValueType(){return GetValue();}
   ObjType& operator=(const ValueType& i){SetValue(i);return *this;}
   ObjDouble():Value(0.0){}
  protected:
   ValueType Value;
 };
//------------------------------------------------------------------------------

class ObjDateTime:public TxStaticObject<ObjDateTime>
 {
  public:
   typedef int64 ValueType;
   static const char* GetClassName(){return "DateTime";}
   typedef TxStaticClass<ObjType> Class;
   //-----------------
   virtual ValueType GetValue(){return Value;};
   virtual void SetValue(const ValueType& i){Value = i;}
   //-----------------
   virtual Str GetValueToStr(){if(Value)return xDateTimeToStr(GetValue()); return "";};
   virtual void  SetValueFromStr(const Str&s){if(s.Size())SetValue(xStrToDateTime(s));else{SetValue(0);}};
   //-----------------
   operator ValueType(){return GetValue();}
   ObjType& operator=(const ValueType& i){SetValue(i);return *this;}
   ObjDateTime():Value(0){}
  protected:
   ValueType Value;
 };
//------------------------------------------------------------------------------
class TxSimplEnumItem:public TxStaticObject<TxSimplEnumItem>
 {
  public:
   ObjProperty(ObjInt,ID);
   ObjProperty(ObjStr,Name);
   //--------------------------------------------------------
   static const char* GetClassName(){return "SimplEnumItem";}
   class Class:public TxStaticClass<ObjType,Class>
    {
     public:
      Class()
       {
        PublishedProperty(ID);
        PublishedProperty(Name);
       }
    };
 };
//------------------------------------------------------------------------------
class TxSimplEnumItems:public TxStaticItemsListObject<TxSimplEnumItems,TxSimplEnumItem>
 {
  public:
   static const char* GetClassName(){return "SimplEnumItems";}
   typedef TxStaticClass<ObjType> Class;
   //-------------------------
   void Add(int id,const char* Name)
         {
          TxSimplEnumItem * EnumItem = new TxSimplEnumItem();
          EnumItem->ID = id; EnumItem->Name = Name;
          Items.Add(EnumItem);
         }
 };
//------------------------------------------------------------------------------
class ObjBool:public TxStaticObject<ObjBool,ObjInt>
 {
  public:
   static const char* GetClassName(){return "Bool";}
   class Class:public TxStaticClass<ObjType,Class>
    {
     public:
      TxSimplEnumItems EnumItems;
      Class(){EnumItems.Add(0,"False");EnumItems.Add(1,"True");}
    };
   virtual IxBaseObject*GetEnum(){return &Class::Instance().EnumItems;}
 };
//------------------------------------------------------------------------------
class TxBaseStaticClassSpace: public IxStaticClassSpace
 {
   public:
    TxBaseStaticClassSpace()
     {
      RegisterClass(&ObjStr::Class::Instance());
      RegisterClass(&ObjBool::Class::Instance());
      RegisterClass(&ObjInt::Class::Instance());
      RegisterClass(&ObjInt64::Class::Instance());
      RegisterClass(&ObjDateTime::Class::Instance());
     }
    virtual const char* GetName()const{return "BaseStaticClassSpace";}
 };
}
#endif
