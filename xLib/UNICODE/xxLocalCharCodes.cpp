#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxLocalCharCodes.h"
namespace XSPACE
{
const char* CharCodeWin1251toLo =
"                                 !\"#$%&'()*+,-./0123456789:;<=>?@abcdefghijklmnopqrstuvwxyz[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~      …   ‰ ‹          –— ™ ›                   ¿ ±   µ  ¸¹÷»   ¿אבגדהוזחטיךכלםמןנסעףפץצקרשתûü‎‏ÿאבגדהוזחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ ";
const char* CharCodeWin1251toLoIgnoreLatinError =
"                                 !\"#$%&'()*+,-./0123456789:;<=>?@abcdefghijklmnopqrstuvwxyz[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~      …   ‰ ‹          –— ™ ›                   ¿ ±   µ  ¸¹÷»   ¿אבגדהוזחטיךכלםמןנסעףפץצקרשתûü‎‏ÿאבגדהוזחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ ";
const char* CharCodeWin1251toHi =
"                                 !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`ABCDEFGHIJKLMNOPQRSTUVWXYZ{|}~  ‚ „…†‡ ‰ ‹     ‘’“” –— ™ ›                  ®¯°±   µ¶·¨¹×»   ¯ְֱֲֳִֵֶַָֹÊֻּֽ־ֿ׀ׁׂ׃װױײ׳״ÙÚÛÜÝÞßְֱֲֳִֵֶַָֹÊֻּֽ־ֿ׀ׁׂ׃װױײ׳״ÙÚÛÜÝÞß ";
int StrCmpWithTable(const char * c1,const  char * c2,const  char * table)
 {
  if(c1==0)c1="";
  if(c2==0)c2="";
  unsigned char cc1=0;
  unsigned char cc2=0;
  while(*c1&&*c2)
   {
    cc1=table[(unsigned char)*c1];
    cc2=table[(unsigned char)*c2];
    if(cc1!=cc2)return cc1-cc2;
    c1++;
    c2++;
   }
  if((*c1==0)&&(*c2!=0))return -1;
  return cc1-cc2;
 }
int FindCaseIgnoreW1251(const Str& s1,const Str& s2)
 {
  const char*c1=s1.c_str();
  const char*c2=s2.c_str();
  for(int i=0;i<s1.Size();i++)
   if(StrCmpWithTable(c1+i,c2,CharCodeWin1251toLo)==0)
    return i+1;
  return 0;
 }
}
//---------------------------------------------------------------------------
#ifndef __GNUC__
#pragma package(smart_init)
#endif

