//---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "xPict32.h"
//---------------------------------------------------------------------------
class TfmMain : public TForm
{
__published:	// IDE-managed Components
        TImage *Image;
        TButton *bWork;
        TButton *bTestCompare;
        TMemo *mTest;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall bWorkClick(TObject *Sender);
        void __fastcall bTestCompareClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        Graphics::TBitmap *BS,*BD;
        TxProviderPict S,D;
        __fastcall TfmMain(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TfmMain *fmMain;
//---------------------------------------------------------------------------
#endif
