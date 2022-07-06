//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitMain.h"
#include "xAntiStep.h"
#include <Time.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfmMain *fmMain;
//---------------------------------------------------------------------------
__fastcall TfmMain::TfmMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormActivate(TObject *Sender)
{
 static bool first=true;
 if(first)
  {
   first=false;
   BS = new Graphics::TBitmap();
   BS->PixelFormat = pf32bit;
   BS->Width = Image->Width;
   BS->Height = Image->Height;
   BS->Canvas->Draw(0,0,Image->Picture->Graphic);
   BD = new Graphics::TBitmap();
   BD->PixelFormat = pf32bit;
   BD->Width = Image->Width;
   BD->Height = Image->Height;
   S.Init(BS->Width,BS->Height,BS->ScanLine[0],((int)BS->ScanLine[1])-((int)BS->ScanLine[0]));
   D.Init(BD->Width,BD->Height,BD->ScanLine[0],((int)BD->ScanLine[1])-((int)BD->ScanLine[0]));

  }
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
 delete BS;
 delete BD;
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::bWorkClick(TObject *Sender)
{
   TxGraphColor A,B;
   A.RGBA=0; B.RGBA=0x80808080;
   int i=qCompareGraphColor(A,B);
   BD->Canvas->Draw(0,0,BS);
   long t,tt;
   t=clock();
   for(int i=0;i<1000;i++)
    xDeleteSteps(D,S);
   t=clock()-t;
   Caption=t;
   Canvas->Draw(Image->Left*2+Image->Width,Image->Top,BD);
}
//---------------------------------------------------------------------------
void __fastcall TfmMain::bTestCompareClick(TObject *Sender)
{
  int t[256];
  TxGraphColor A,B;
  for(int i=0;i<256;i++)t[i]=0;
  for(int i=0;i<256;i++)
   for(int j=0;j<256;j++)
    {
     A.Detail.A=i;  A.Detail.R=i;  A.Detail.G=i;   A.Detail.B=i;
     B.Detail.A=j;  B.Detail.R=j;  B.Detail.G=j;   B.Detail.B=j;
     if(qCompareGraphColor(A,B))
      {
       int k;
       if(i>j)k=i-j;else k=j-i;
       t[k]++;
      }
    }
  for(int i=0;i<256;i++)
   if(t[i]!=0)
    {
     AnsiString s=IntToStr(i)+":"+IntToStr(t[i]);
     mTest->Lines->Add(s);
    }
//mTest
}
//---------------------------------------------------------------------------


