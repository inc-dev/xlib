//---------------------------------------------------------------------------
#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxSmallStr.h"
using namespace XSPACE;
void SmallStr::Assign(const char*s)
 {
   Len=0; Shift=0;
   while(*s&&Len<MaxSize){Data[Len]=*s;Len++;s++;}
   Data[Len]=0;
 }
#ifndef __GNUC__
#pragma package(smart_init)
#endif

