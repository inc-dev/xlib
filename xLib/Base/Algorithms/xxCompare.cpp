#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxCompare.h"
namespace XSPACE
{
int StrCmp(const char * c1,const  char * c2)
 {
  if(c1==0)c1="";
  if(c2==0)c2="";
  return strcmp(c1,c2);
 }
int StrCmpICLat(const char * c1,const  char * c2)
 {
  if(c1==0)c1="";
  if(c2==0)c2="";
  char cc1;
  char cc2;
  while(*c1&&*c2)
   {
    cc1=*c1;
    cc2=*c2;
    if(cc1>='a'&&cc1<='z')cc1+='A'-'a';
    if(cc2>='a'&&cc2<='z')cc2+='A'-'a';
    if(cc1!=cc2)return cc1-cc2;
    c1++;
    c2++;
   }
  if((*c1==0)&&(*c2!=0))return -1;
  if((*c1!=0)&&(*c2==0))return 1;
  return 0;
 }
}

#ifndef __GNUC__
#pragma package(smart_init)
#endif
