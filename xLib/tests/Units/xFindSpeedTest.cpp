#pragma hdrstop
#include "xFindSpeedTest.h"
#include <Time.h>
#include "..\..\xxBase.h"
#include <stdio.h>
#include <string>
//---------------------------------------------------------------------------
using namespace XSPACE;
void FindSpeedTest()
 {
   long t;
   Str s("1234567890qwertyuiopasdfghjklzxcvbnm");
   int j;
   t=clock();
   for(int i=0;i<3000000;i++)
    {
/*     j=Find(s,'n',1,37);
     j=Find(s,'n',1,37);
     j=Find(s,'n',1,37);
     j=Find(s,'n',1,37);
     j=Find(s,'n',1,37);*/
     j=Find(s,'n',1);
     j=Find(s,'n',1);
     j=Find(s,'n',1);
     j=Find(s,'n',1);
     j=Find(s,'n',1);
    }
   t=clock()-t;
   printf("FindSpeedTest STR %d  %d\n",t,j);
   //-------------
   std::string ss("1234567890qwertyuiopasdfghjklzxcvbnm");
   t=clock();
   for(int i=0;i<3000000;i++)
    {
     j=ss.find('n');
     j=ss.find('n');
     j=ss.find('n');
     j=ss.find('n');
     j=ss.find('n');
    }
   t=clock()-t;
   printf("FindSpeedTest STL %d  %d\n",t,j);
   //-------------
   char* c="1234567890qwertyuiopasdfghjklzxcvbnm";
   t=clock();
   for(int i=0;i<3000000;i++)
    {
     j=int(strchr(c,'n')-c);
     j=int(strchr(c,'n')-c);
     j=int(strchr(c,'n')-c);
     j=int(strchr(c,'n')-c);
     j=int(strchr(c,'n')-c);
    }
   t=clock()-t;
   printf("FindSpeedTest char* %d  %d\n",t,j);


 }

#pragma package(smart_init)
