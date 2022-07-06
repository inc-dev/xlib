#ifndef __GNUC__
#pragma hdrstop
#endif


#include "xxDateTime.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>    // usleep()
#endif
//------------------------------------------------------------------------------
const char* Months_Names[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
#ifdef _WIN32
class TempInternalGetTimeParam
 {
  public:
   LARGE_INTEGER TicksPerSec;
   LARGE_INTEGER BeginTicks;       
   static double Coefficient;
   TempInternalGetTimeParam()
    {
     QueryPerformanceFrequency(&TicksPerSec);
     QueryPerformanceCounter(&BeginTicks);
     Coefficient=1000.0/((double)TicksPerSec.QuadPart);
    }
 } static InternalGetTimeParam;
double TempInternalGetTimeParam::Coefficient;
double xGetMilliSeconds()
 {
   LARGE_INTEGER Ticks;
   QueryPerformanceCounter(&Ticks);
   return (TempInternalGetTimeParam::Coefficient*Ticks.QuadPart);
 }
//------------------------------------------------------------------------------
void xSleep(double ms)
 {
  double Begin = xGetMilliSeconds()-0.001;
  if(ms>70){Sleep(ms-40);}
  while(xGetMilliSeconds()<Begin+ms);
 }

#else
double xGetMilliSeconds()
 {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (((double)tv.tv_sec) * 1000.0 + (double)tv.tv_usec/1000.0);
 }
//------------------------------------------------------------------------------
void xSleep(double ms){usleep(ms * 1000);}
//void xSleep(double s){sleep(1+s/1000);}
#endif
//------------------------------------------------------------------------------
static int64 ShiftDateTime=0;
void xSetShiftDateTime(int64 i) {ShiftDateTime = i;}
int64 xGetShiftDateTime(){return ShiftDateTime;}
int64 xNow(){return time(0)+ShiftDateTime;}

tm xDecodeDateTime(int64 Date)
 {
  time_t timer = time_t(Date-ShiftDateTime);
   tm t = *localtime(&timer);
  return t;
 }
int GRShift=1000;
int GrinvichShiftHours()
 {
  if(GRShift==1000)
   {
     time_t time=0;
     tm tl = *localtime(&time);
     tm tg = *gmtime(&time);
     GRShift = tl.tm_hour - tg.tm_hour;
   }
  return GRShift;
 }

int64 xCodeDateTime(tm& iDecodeDateTime)
 {
   return mktime(&iDecodeDateTime)+ShiftDateTime;
 }

#ifndef __GNUC__
#pragma package(smart_init)
#endif

