#pragma hdrstop
#include <stdio.h>
#include "xRawTest.h"
#include "..\..\xxBase.h"
#include <sysutils.hpp>
#include "xxFileBuffer.h"
namespace XSPACE  
{
 void xxRawTest()
  {
   printf("Begin\n");
   char d[500];
   double DT = xGetMilliSeconds();
   TSearchRec sr;
   int i = FindFirst("F:\\foto\\!5100\\!NEF\\*.nef",-1,sr);
   while(i==0)
    {
     StrCopy(d,"F:\\foto\\!5100\\!NEF\\");
     StrCat(d,sr.Name.c_str());
     TxFileBuffer FileBuffer;
     FileBuffer.OpenFile(d);
     FileBuffer.RealReserv(1000000);
     FileBuffer.CloseFile();
     i = FindNext(sr);
    }
   FindClose(sr);

   DT = xGetMilliSeconds()-DT;
   printf("time %f ms\n",DT);
   printf("End\n");
  }
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
