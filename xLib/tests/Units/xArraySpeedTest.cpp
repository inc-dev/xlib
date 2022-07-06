#include "xArraySpeedTest.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <Time.h>
#include "../../base/xxArray.h"
using namespace XSPACE;
void  AddTest(const char* cc,int count)
 {
  std::string s;
  std::vector<char> v;
  Array<char> a;
  long t,tt;
  t=clock();
  for(int i=0;i<count;i++)
    s.append(cc);
  t=clock()-t;
  tt=clock();
   for(int i=0;i<count;i++)
    a.Add(cc);
  tt=clock()-tt;
  printf("%d;%d;%d;%dk\n",t,tt,strlen(cc),count/1000);

 }
template<typename T>
 void TestAccept(char* NameStr)
  {
  long t;
  T s1("12345678901234567890123456789012345678901234567890123456789012345678901234567890"),s2;
  t=clock();
  for(int i=0;i<10000000;i++)  s2=s1;
  t=clock()-t;
  printf("%s:%d\n",NameStr,t);
  }
void ArraySpeedTest()
 {
  printf("\n\nSTL;ARRAY;chars;iterations\n");
  std::string s;
//  for(int i=1;i<=20;i++)
   {
    s+='1';
    AddTest(s.c_str(),10000000);
   }
  TestAccept<std::string>("STL");
  TestAccept<Str>("Str");
 }
  //-----------------------------------

//---------------------------------------------------------------------------

