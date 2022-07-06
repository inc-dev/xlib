// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'UtilsColor.pas' rev: 6.00

#ifndef UtilsColorHPP
#define UtilsColorHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <ComCtrls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Variants.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Utilscolor
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall TextOut(int x, int y, int l, AnsiString s, Graphics::TCanvas* Canvas);
extern PACKAGE void __fastcall AddLineToRichEdit(Comctrls::TRichEdit* RichEdit, AnsiString s);
extern PACKAGE AnsiString __fastcall colorToStrR(int i);

}	/* namespace Utilscolor */
using namespace Utilscolor;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// UtilsColor
