//---------------------------------------------------------------------------
#pragma hdrstop
#include <vcl.h>
#include "xxBase.h"
#include "xArrayTest.h"
#include "xListTest.h"
#include "xPTR_Test.h"
#include "DateTime_test.h"
#include "xArraySpeedTest.h"
#include "xFindSpeedTest.h"
#include "xXML_OBJ_Test.h"
#include <stdio.h>
#include <Time.h>
//#include <vector>
#include <string>
#include "xxBase.h"
#include "xxObjects.h"
#include "xxDateTime.h"
#include "xxConsoleLogger.h"
#include "xxBorlandLogger.h"
#include "Unit1.h"
#include "xxStaticPubObject.h"
//---------------------------------------------------------------------------
#pragma argsused

using namespace XSPACE;
template<class A, template<class > class B >
class ttt
 {
  public:

 };
 /*
template<typename T> struct HasSwap
{
    template<typename U, void (U::*fn)(U&)> struct CheckSwap
    {
        typedef int result;
    };

    template<typename U> static typename CheckSwap<U, &U::swap>::result HasSwapFn(U*);
    static char HasSwapFn(...);

    static const int value = sizeof(HasSwapFn((T*)NULL)) != 1 ? 1 : 0;
};        */
#include "UnitTemp.h"
typedef unsigned char u8;
typedef unsigned int u32;

void aFutureDate( u8 *dd, u8 *mm, u8 *yy, u32 o)
 {	// o = offset in days
  const u8 days[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
  u32 mLen, diff;
  while(o)
   {
     if( *mm == 12 && *dd == 31)
       (*yy)++;	// set yy
     mLen = days[*mm];
     if( *mm == 2 && (*yy)%4 == 0)
      mLen = 29;

     if( u32(*dd) == mLen)
       {

        if( ++(*mm) > 12)
          *mm = 1; 		// set mm
        *dd = 1; o--;
       }else
       {
        diff = mLen - *dd;
	if( o > diff){ *dd = u8(mLen); o -= diff;}
	else{ *dd += u8(o); break;}			// here dd is set finaly
       }
   }
 }
/*
class Father
{
public:
  Father() {}
  virtual ~Father() {printf("Father done");}
};

class Son : public Father
{
private:

public:
  Son() : Father() {  }
  ~Son() { printf("Son done");}
};        */
#include <time.h>
class ttttt1
 {
  public:
  typedef int ValueType;
 };
template<typename t1,typename t2=typename t1::ValueType>
class ttttt2
 {
   public:
   t2 r;
 };
#define NameToSTR(y) #y
int main(int argc, char* argv[])
{

  SetDefaultLogger(&ConsoleLogger);
  ConsoleLogger.isAutonom = true;
  Mess("Start");
  Mess(NameToSTR(Test));
   
  TxSimplEnumItem qqqq;
//  TxSimplEnumItem::ValueType sasasas=5;
  qqqq.ID = 1;
  ObjStr::ValueType qqwq("sdwdwe2");
  Mess(qqwq);
  qqqq.Name = "dwd";

  ObjStr wqqwqw;
  IxListOfObjects* ListOfObjects = wqqwqw.GetProperties();
  int iiii=ListOfObjects->First();
  ttttt2<ttttt1> qqqqqq;
  Error("qwertt");
  Warning("rterter");
  if(QueryOkCancel("продолжить?")==qrOk)Mess("продолжаем");else Mess("не продолжаем");

/*  Father*f=new Son();
  delete f;
  system("PAUSE");*/
  u8 d=15,mm=4,y=11;
  aFutureDate(&d,&mm,&y,366);
  char* a="122434523";
 // FindSpeedTest();
 // vector<string> ss;
  std::string ssss;
  Str s("1234567890"),ss("00");
  char*sssss="1234567890";
  int m=1,n=2;
  if(s=="1234567890")
  printf("%s\n",s.c_str());

  s='+'+s+'#'+s+s;
  printf("%s\n",s.c_str());
  Str sss(Portion(s,7));
  printf("%s\n",sss.c_str());
  int i = Find(s,'5');
  printf("%d\n",i);

 i = Find(s,ss);
 i = Find(s,"678",3);
 i = FindFirstIn(s,"768");
 i = FindFirstOut(s,"4321");
  printf("%d\n",i);
//  if(HasSwap<ss>::value)
//     ss.push_back("123");

//  ArraySpeedTest();
//  FindSpeedTest();

  const char*c = ArrayTest();
  if(c)printf("Error:%s\n",c);
  else printf("\n\nArray TEST OK\n");
  c = ListTest();
  if(c)printf("Error:%s\n",c);
  else printf("\n\nList TEST OK\n");

  c = PTRTest();
  if(c)printf("Error:%s\n",c);
  else printf("\n\nPTR TEST OK\n");

  c = DateTimeTest();
  if(c)printf("Error:%s\n",c);
  else printf("\n\nDateTime TEST OK\n");

  Stack<char> MyStack;
  MyStack.Push('a');
  MyStack.Push('b');
  MyStack.Push('c');
  char
  saasa=MyStack.Pop();
  saasa=MyStack.Pop();
  saasa=MyStack.Pop();
  Queue<char> MyQueue;
  MyQueue.Push('a');
  MyQueue.Push('b');
  MyQueue.Push('c');
  saasa=MyQueue.Pop();
  saasa=MyQueue.Pop();
  saasa=MyQueue.Pop();
  Mess("XML");
  c = XML_OBJ_Test();
  if(c)printf("Error XML_OBJ_Test:%s\n",c);
  else printf("\n\nXML_OBJ_Test TEST OK\n");


  Mess("Stop");
  system("PAUSE");
  return 0;
}
//---------------------------------------------------------------------------








