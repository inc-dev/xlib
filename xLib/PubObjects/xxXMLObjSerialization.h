#ifndef xxXMLObjSerializationH
#define xxXMLObjSerializationH
#include "xxObjSerialization.h"
#include "../UNICODE/xxCodePages.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
class TxXMLCoder:public IxObjectCoder
 {
  protected:
   enum TxXMLBodyFase{fbBegin,fbOUTCaption,fbInCaption,fbSimplData,fbSimplEnd};
   TxXMLBodyFase BodyFase;
   virtual bool isValidName(const Str&);
   Stack<Str> Names;
   bool isOneLine;
  public:
   Str encoding;//encoding
   IxBaseCodePage* CodePage;
   TxXMLCoder(){CodePage = CurrentCodePage; encoding = CodePage->Name;}
   //постепенно чтение
   virtual bool EventsBegin(){CodePage = 0;Level = 0;BodyFase = fbBegin; Names.Clear(); return IxObjectCoder::EventsBegin();};
   virtual TxDataEvent GetNextEvent();
   //постепенно «апись
   virtual bool WriteBegin() {BodyFase = fbBegin; Names.Clear(); return IxObjectCoder::WriteBegin();}
   virtual bool WriteSimpleObject(const Str& Name,const Str& Value);
   virtual bool WriteObjectBegin(const Str& Name);
   virtual bool isSimpleData(const Str& Value);
   virtual bool WriteValue(const Str& Value);
   virtual bool WriteObjectEnd();
   Str StrToXMLStr(const Str&);
   Str StrFromXMLStr(const Str&);
 };
}
//------------------------------------------------------------------------------
#endif
