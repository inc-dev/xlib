#ifndef xxObjSerializationH
#define xxObjSerializationH
#include "../Utils/xxTxtProvider.h"
//#include "../Utils/xxLogger.h"
#include "xxPubObjects.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
// Event for encoding and decoding objects
enum TxDataEvent{deOpen,deClose,deData,deEnd,deError};
//class to encode and decode objects
class IxObjectCoder
 {
  public:
   IxBaseTxtProvider* txtProvider; //
   IxClassSpace *    ClassSpace;   //they need to be initialize
   IxObjectCoder(){Level = 0;txtProvider=0;ClassSpace=0;}
//------------------------------------------------------------------------------
   virtual bool EventsBegin();          
   virtual TxDataEvent GetNextEvent()=0;
                   Str EventData;       
                   Str StrPosition;                          
                  bool isSimpleObject;  
                   int Level;           
   virtual IxBaseObject*GetFullObject(IxBaseObject*ExistObject=0);
   virtual bool EventsEnd();            
//------------------------------------------------------------------------------
   virtual bool WriteBegin();
   virtual bool WriteSimpleObject(const Str&Name,const Str&Value)=0;
   virtual bool WriteObject(IxBaseObject*);//work with the whole object
//------------------------------------------------------------------------------   
   virtual bool WriteObjectBegin(const Str&Name)=0;
   virtual bool WriteValue(const Str&Value)=0;
   virtual bool WriteObjectEnd()=0;
   virtual bool WriteEnd();
//------------------------------------------------------------------------------
   //-- SIMPLE -------------
   bool SaveObjectToFile(const Str&FileName,IxBaseObject* o);
   IxBaseObject*LoadObjectFromFile(const Str& FileName,IxClassSpace*);
   bool LoadObjectFromFile(const Str& FileName,IxBaseObject*ExistObject,IxClassSpace*);
//------------------------------------------------------------------------------
   Str DecodeDataEvent(TxDataEvent);    
   virtual bool isValidName(const Str& )=0;
   virtual bool isSimpleData(const Str& Value)=0;
 };
}
//------------------------------------------------------------------------------
#endif
