#pragma hdrstop
#include "DateTime_test.h"
#include "..\..\base\xxDateTime.h"
//#include <time.h>
//------------------------------------------------------------------------------
char *DateTimeTest()
 {
  xSetShiftDateTime(0);
  int64 d;
  time_t dd1,dd2;
  do{
   dd1=time(0);
   d = xNow();
   dd2=time(0);
  } while(dd1!=dd2);
  tm tm1=*localtime(&dd2);
  tm tm2=xDecodeDateTime(d);
  int64 d2=xCodeDateTime(tm2);
  tm tm3=xDecodeDateTime(d2);
  if(tm1.tm_hour!=tm2.tm_hour||tm1.tm_isdst!=tm2.tm_isdst||tm1.tm_mday!=tm2.tm_mday
   ||tm1.tm_min!=tm2.tm_min||tm1.tm_mon!=tm2.tm_mon||tm1.tm_sec!=tm2.tm_sec
   ||tm1.tm_wday!=tm2.tm_wday||tm1.tm_yday!=tm2.tm_yday||tm1.tm_year!=tm2.tm_year)
  return "tm1!=tm2";
  if(tm1.tm_hour!=tm3.tm_hour||tm1.tm_isdst!=tm3.tm_isdst||tm1.tm_mday!=tm3.tm_mday
   ||tm1.tm_min!=tm3.tm_min||tm1.tm_mon!=tm3.tm_mon||tm1.tm_sec!=tm3.tm_sec
   ||tm1.tm_wday!=tm3.tm_wday||tm1.tm_yday!=tm3.tm_yday||tm1.tm_year!=tm3.tm_year)
  return "tm1!=tm3";
  double t=xGetMilliSeconds();
  xSleep(53.333);
  t=xGetMilliSeconds()-t;
  if(t>53.335||t<53.331)return "xSleep(53.333);";
  t=xGetMilliSeconds();
  xSleep(153.333);
  t=xGetMilliSeconds()-t;
  if(t>153.335||t<153.331)return "xSleep(153.333);";
  return 0;
 }
//------------------------------------------------------------------------------
#pragma package(smart_init)
