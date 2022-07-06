#ifndef xxSimpleSVGH
#define xxSimpleSVGH
#include "..\PubObjects\xxStaticPubObject.h"
//------------------------------------------------------------------------------
// Â האכüםוירול ןנוהןמכמדאועסÿ 
namespace XSPACE
{
 class TxShape:public TxStaticObject<TxShape>
 {
  public:
   ObjProperty(ObjStr,fill);
   static const char* GetClassName(){return "AbstractShape";}
   class Class:public TxStaticClass<ObjType,Class>
    {
     public:
      Class()                        
       {
        PublishedProperty(fill);
       }
    };
 };
class TxRectangle:public TxStaticObject<TxRectangle,TxShape>
 {
  public:
   ObjProperty(ObjInt,x);
   ObjProperty(ObjInt,y);
   ObjProperty(ObjInt,width);
   ObjProperty(ObjInt,height);
   static const char* GetClassName(){return "rect";}
   class Class:public TxInheritableStaticClass<ParentObjType::Class,ObjType,Class>
    {
     public:
      Class()
       {
        PublishedProperty(x);
        PublishedProperty(y);
        PublishedProperty(width);
        PublishedProperty(height);
       }
    };
 };
class TxCircle:public TxStaticObject<TxCircle,TxShape>
 {
  public:
   ObjProperty(ObjInt,cx);
   ObjProperty(ObjInt,cy);
   ObjProperty(ObjInt,r);
   static const char* GetClassName(){return "circle";}
   class Class:public TxInheritableStaticClass<ParentObjType::Class,ObjType,Class>
    {
     public:
      Class()
       {
        PublishedProperty(cx);
        PublishedProperty(cy);
        PublishedProperty(r);
       }
    };
 };
class TxShapeList:public TxStaticItemsListObject<TxShapeList,TxShape>
 {
  public:
    TxShapeList()
      {version = "1.1"; baseProfile = "full";
         xmlns = "http://www.w3.org/2000/svg";
         xmlns_xlink = "http://www.w3.org/1999/xlink";
         xmlns_ev = "http://www.w3.org/2001/xml-events";}
    ObjProperty(ObjStr,version);
    ObjProperty(ObjStr,baseProfile);
    ObjProperty(ObjStr,xmlns);
    ObjPropertyEx(ObjStr,xmlns_xlink,"xmlns:xlink");
    ObjPropertyEx(ObjStr,xmlns_ev,"xmlns:ev");
    ObjProperty(ObjInt,width);
    ObjProperty(ObjInt,height);
   static const char* GetClassName(){return "svg";}
   class Class:public TxStaticClass<ObjType,Class>
    {
     public:
      Class()
       {
        PublishedProperty(version);
        PublishedProperty(baseProfile);
        PublishedProperty(xmlns);
        PublishedProperty(xmlns_xlink);
        PublishedProperty(xmlns_ev);
        PublishedProperty(width);
        PublishedProperty(height);
       }
    };
 };        
class TxSVGClassSpace: public IxStaticClassSpace
 {
   public:
    TxSVGClassSpace()
     {
      RegisterClass(&TxShape::Class::Instance());
      RegisterClass(&TxRectangle::Class::Instance());
      RegisterClass(&TxCircle::Class::Instance());
      RegisterClass(&TxShapeList::Class::Instance());
     }
    virtual const char* GetName()const{return "SVGClassSpace";}
    static TxSVGClassSpace & Instance(){static TxSVGClassSpace t;return t;}
 };

}
//------------------------------------------------------------------------------
#endif
