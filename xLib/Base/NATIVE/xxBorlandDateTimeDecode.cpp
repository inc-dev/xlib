#pragma hdrstop
#include "xxBorlandDateTimeDecode.h"
namespace XSPACE
{
 int64 BorlandDateToDate(TDate dt)
  {
   unsigned short year,month,day;
   dt.DecodeDate(&year,&month,&day);
   tm t; setmem(&t,sizeof(t),0);
   t.tm_year = year-1900; t.tm_mon = month-1; t.tm_mday = day;
   return xCodeDateTime(t);
  }
 TDate DateToBorlandDate(int64 dt)
  {
   tm t = xDecodeDateTime(dt);
   return TDate(t.tm_year+1900,t.tm_mon+1,t.tm_mday);
  }
}
#pragma package(smart_init)
