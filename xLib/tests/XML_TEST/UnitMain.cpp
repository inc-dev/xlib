//---------------------------------------------------------------------------

#include <vcl.h>
#include "../../xLib/PubObjects/xxXMLObjSerialization.h"
#include "../../xLib/PubObjects/xxDinamicPubObject.h"

#pragma hdrstop

#include "UnitMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
using namespace XSPACE;
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    TxDinamicClassSpace DinamicClassSpace;
    TxFileTxtProvider FileTxtProvider;
    FileTxtProvider.FileName = "1.xml";
    TxXMLCoder XMLCoder;
    XMLCoder.txtProvider = &FileTxtProvider;
    XMLCoder.ClassSpace  = &DinamicClassSpace;
    XMLCoder.encoding = "UTF-8";
    //-------------------------
    if(!XMLCoder.EventsBegin()){}
    IxBaseObject* o = XMLCoder.GetFullObject();

    Str ev_d=XMLCoder.EventData+" "+Str("line ")+NumToStr(FileTxtProvider.GetLine())+Str("  str.")+NumToStr(FileTxtProvider.GetCol());
    ShowMessage(ev_d.c_str());
    XMLCoder.EventsEnd();

}
//---------------------------------------------------------------------------
