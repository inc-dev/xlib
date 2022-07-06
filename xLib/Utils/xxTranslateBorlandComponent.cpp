#pragma hdrstop
#include "xxTranslateBorlandComponent.h"
#include "xxLang.h"
using namespace XSPACE;

void TranslateForm(TWinControl *f,bool WithCaption)
 {
  TControl *ChildControl;
  TWinControl*t=0;
  char b[512];  Str s;
  if(WithCaption)
   {
    f->GetTextBuf(b,sizeof(b)-10);
    s = Translate(b);
    f->SetTextBuf((char*)s.c_str());
   }
  for(int i=0;i<f->ControlCount;i++)
   {
    ChildControl = f->Controls[i];
    ChildControl->GetTextBuf(b,sizeof(b));
    s = Translate(b);
    ChildControl->SetTextBuf((char*)s.c_str());
    t = dynamic_cast<TWinControl *>(ChildControl);
    if(t)
     TranslateForm(t,false);
   }
 }
void TranslateDataSet(TDataSet *DataSet)
 {
  if(DataSet==0)return;
  for(int i = 0; i < DataSet->FieldCount; i++)
   DataSet->Fields->Fields[i]->DisplayLabel = Translate(DataSet->Fields->Fields[i]->DisplayLabel.c_str()).c_str();
 }

#pragma package(smart_init)
