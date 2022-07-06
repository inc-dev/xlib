#pragma hdrstop
#include "xPTR_Test.h"
#include "..\..\base\xxPtr.h"
#include "xArrayTest.h"
//------------------------------------------------------------------------------
using namespace XSPACE;
template<typename T>
const char * PTRTest1()
 {
   T*n1=new T(1);
   PTR<T> p1(n1),p2;
   if(p1!=n1)return "p1!=n1";
   p2=p1;
   if(p2!=n1)return "p2!=n1";
   p1=0;p2=0;
   if(!p1.isEmpty()||(int)p2!=0)return "p1!=0||p2!=0";
   n1=new T(2);
   p1 = n1;
   p2 = p1;
   p1 = p1;
   if(p1!=p2)return "p1!=p2";
   p2=0;
   RefPTR<T> r1(p1),r2(r1);
   p2=r1;
   if(p1!=p2)return "p1!=p2";
   p1=0;
   if(p1==p2)return "p1==p2";
   p1 = r2;
   if(p1!=p2)return "p1!=p2";
   if(p1.isEmpty()||p2.isEmpty())return "p1==0||p2==0";
   p1=0;p2=0;
   p1 = r1;
   if(!p1.isEmpty())return "p1!=0";
   return 0;
 }
const char *PTRTest()
 {
  const char *error;
  error = PTRTest1<int>();
  if(error)return error;
  error = PTRTest1<TestDones>();
  if(error)return error;
  if(TestDones::isBad())return "isBad";
   #ifdef _DEBUG
  int i=TxInternalTicketMem<int>::Count(); //1 заглушка
  if(i!=1)return "Count()!=1 int";
  i=TxInternalTicketMem<TestDones>::Count();
  if(i!=1)return "Count()!=1 TestDones";
   #endif

  return 0;
 }


//------------------------------------------------------------------------------
#pragma package(smart_init)












