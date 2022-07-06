#pragma hdrstop
//------------------------------------------------------------------------------
#include "xxLibTest.h"
#include "..\..\xxBase.h"
#include "..\..\xxObjects.h"
#include "..\..\Utils\xxConsoleLogger.h"
#include "xArrayTest.h"
#include "xListTest.h"
#include "xPTR_Test.h"
#include "xXML_OBJ_Test.h"
#include "xThreadTest.h"
#include "xSocketsTest.h"

#include "xxGTLPixel.h"
using namespace XSPACE;
using namespace GTL;
//------------------------------------------------------------------------------
void Test()
 {
  SetDefaultLogger(&ConsoleLogger);  //ConsoleLogger.isAutonom = true;
  Mess("Start");
  //----------------------------------------------------------------------------
  const char * mError = ArrayTest();
  if(mError){Error(mError);  MessDialog("continue?");}
  mError = ListTest();
  if(mError){Error(mError);  MessDialog("continue?");}
  mError = PTRTest();
  if(mError){Error(mError);  MessDialog("continue?");}
  mError = XML_OBJ_Test();
  if(mError){Error(mError);  MessDialog("continue?");}
  mError = ThreadTest();
  if(mError){Error(mError);  MessDialog("continue?");}
  FractionWrap<uint8> fw;
  TxPixelRGBA8 a,b;
  TxPixelRGBA16 c;
  b=a;
//  DecodePixel(c,a);
  fw.Clear();
  mError = SocketsTest();
  if(mError){Error(mError);  MessDialog("continue?");}
  //----------------------------------------------------------------------------
 // MessDialog("");
 }
//------------------------------------------------------------------------------
#pragma package(smart_init)
