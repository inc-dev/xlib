#ifndef xxBorlandDateTimeDecodeH
#define xxBorlandDateTimeDecodeH
#include "xxDateTime.h"
#include "vcl.h"
//---------------------------------------------------------------------------
namespace XSPACE
{
 int64 BorlandDateToDate(TDate dt);
 TDate DateToBorlandDate(int64 dt);
}
#endif
