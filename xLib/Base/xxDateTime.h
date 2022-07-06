#ifndef xxDateTimeH
#define xxDateTimeH
#include "xxTypes.h"
#include <time.h>
//------------------------------------------------------------------------------
/*
<time.h>         
struct tm:
int tm_sec; seconds of the minute (0.59)
int tm_min; minutes of the hour (0.59)
int tm_hour; hours from midnight (0.23)
int tm_mday; of the month (1.31)
int tm_mon; Months after January (0.11)
int tm_year; Years 1900
int tm_wday; Days Sunday (0.6)
int tm_yday; days from the first of January (0.365)
int tm_isdst; Symptom summer time
*/
//------------------------------------------------------------------------------
extern const char* Months_Names[];
void  xSetShiftDateTime(int64 i);
int64 xGetShiftDateTime();
//----------------------------------------------
int64 xNow();//seconds
tm    xDecodeDateTime(int64 Date);
int64 xCodeDateTime(tm& iDecodeDateTime);
int GrinvichShiftHours();
//------------------------------------------------------------------------------
//whole millisecond accuracy with an error of about 4 microseconds (not miles)
double xGetMilliSeconds();
// more accurate Sleep
// integer mlisekundy, accuracy to within about 4 microseconds (not miles)
void   xSleep(double);
//------------------------------------------------------------------------------
class TxStopWatch
 {
  public:
   inline TxStopWatch():Sum(0),Min(0),Max(0),laps(0){}
   void inline Start(){StartTime = xGetMilliSeconds();}
   void inline Stop()
    {
     double Delta = xGetMilliSeconds()-StartTime;
     if(laps==0){Min=Delta;Max=Delta;}
     else
      {
       if(Delta<Min)Min = Delta;
       if(Delta>Max)Max = Delta;
      }
     Sum=Sum+Delta;
     laps++;
    }
   double GetMSEC(){return Sum;}
   int    GetLaps(){return laps;}
   void inline Clear(){Sum=0;laps=0;Min=0;Max=0;}
   //---
   double Sum,Min,Max;
   int    laps;
  protected:  
   double StartTime;
 };
#endif
