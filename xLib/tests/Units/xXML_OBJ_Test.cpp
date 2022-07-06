#pragma hdrstop
#include "xXML_OBJ_Test.h"
#include "..\..\xxObjects.h"
#include "..\..\Graphics\xxSimpleSVG.h"
#include "..\..\Utils\xxLogger.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
const char*ObjSpeedTest()
 {
  TxDinamicClassSpace DinamicClassSpace;
  TxFileTxtProvider FileTxtProvider1,FileTxtProvider2;
  FileTxtProvider1.FileName = "test1.xml";
  FileTxtProvider2.FileName = "test2.xml";
  TxXMLCoder XMLCoder;
  TxXMLCoder XMLCoder2;
  XMLCoder.txtProvider = &FileTxtProvider1;
  XMLCoder.ClassSpace  = &DinamicClassSpace;
  //-----------------------------------------
  XMLCoder2.txtProvider = &FileTxtProvider2;
  XMLCoder2.ClassSpace  = &DinamicClassSpace;
  XMLCoder2.encoding = "UTF-8";
  //-----------------------------------------
  XMLCoder.WriteBegin();
  XMLCoder.WriteObjectBegin("Goods");
  XMLCoder.WriteSimpleObject("Склад","1");
  for(int i=1;i<1000;i++)
   {
     XMLCoder.WriteObjectBegin("Товар");
     XMLCoder.WriteSimpleObject("PLU",NumToStr(i));
     XMLCoder.WriteSimpleObject("Name","&<>\"\'&#1111;&Товар");
     XMLCoder.WriteSimpleObject("Price","55,5");
     if(i&8)
      {
       XMLCoder.WriteObjectBegin("Barcode");
       XMLCoder.WriteSimpleObject("Discont","5%");
       XMLCoder.WriteValue("1234567890123");
       XMLCoder.WriteObjectEnd();
      }else  XMLCoder.WriteSimpleObject("Barcode","1234567890123");
     XMLCoder.WriteObjectEnd();
   }
  XMLCoder.WriteObjectEnd();
  XMLCoder.WriteEnd();
//-----------------------------------------------------------
  XMLCoder.EventsBegin();
  IxBaseObject* o = XMLCoder.GetFullObject();
  XMLCoder.EventsEnd();
  XMLCoder2.WriteBegin();
  XMLCoder2.WriteObject(o);
  XMLCoder2.WriteEnd();
  delete o;
  XMLCoder2.EventsBegin();
  o = XMLCoder2.GetFullObject();
  XMLCoder2.EventsEnd();
  FileTxtProvider1.FileName = "test3.xml";
  XMLCoder.WriteBegin();
  XMLCoder.WriteObject(o);
  XMLCoder.WriteEnd();
  delete o;
  return 0;
 }
const char*StaticObjTest()
 {
  TxSVGClassSpace ClassSpace;
  TxFileTxtProvider FileTxtProvider1,FileTxtProvider2;
  FileTxtProvider1.FileName = "SVGtest1.SVG";
  FileTxtProvider2.FileName = "SVGtest2.SVG";
  TxXMLCoder XMLCoder;
  TxXMLCoder XMLCoder2;
  XMLCoder.txtProvider = &FileTxtProvider1;
  XMLCoder.ClassSpace  = &ClassSpace;
  //-----------------------------------------
  XMLCoder2.txtProvider = &FileTxtProvider2;
  XMLCoder2.ClassSpace  = &ClassSpace;
  XMLCoder2.encoding = "UTF-8";
  //-----------------------------------------
  TxShapeList ShapeList;
  ShapeList.width = 400;              
  ShapeList.height = 400;
  TxRectangle* rect = new TxRectangle();
  rect->x = 10;  rect->y = 10;
  rect->width = 400-10;  rect->height = 400-10;
  rect->fill = "red";
  ShapeList.Items.Add(rect);
  rect = new TxRectangle();
  rect->x = 0;  rect->y = 0;
  rect->width = 400;  rect->height = 400-80;
  rect->fill = "blue";
  ShapeList.Items.Add(rect);
  TxCircle*circle = new TxCircle();
  circle->cx = 0;  circle->cy = 400; circle->r = 100;
  circle->fill = "green";
  ShapeList.Items.Add(circle);
  //-----------------------------------------
  XMLCoder.WriteBegin();
  XMLCoder.WriteObject(&ShapeList);
  XMLCoder.WriteEnd();
//-----------------------------------------------------------
  XMLCoder.EventsBegin();
  IxBaseObject* o = XMLCoder.GetFullObject();
  XMLCoder.EventsEnd();
  XMLCoder2.WriteBegin();
  XMLCoder2.WriteObject(o);
  XMLCoder2.WriteEnd();
  delete o;
  XMLCoder2.EventsBegin();
  o = XMLCoder2.GetFullObject();
  XMLCoder2.EventsEnd();
  FileTxtProvider1.FileName = "SVGtest3.SVG";
  XMLCoder.WriteBegin();
  XMLCoder.WriteObject(o);
  XMLCoder.WriteEnd();
  delete o;
  return 0;
 }

const char* XML_OBJ_Test()
 {
  const char*c = ObjSpeedTest();
  if(c)return c;
  c = StaticObjTest();
  if(c)return c;
  return 0;
 }
}
//------------------------------------------------------------------------------
#pragma package(smart_init)
