#ifndef xxTranslateBorlandComponentH
#define xxTranslateBorlandComponentH
#include <vcl.h>
//#include <DBCommon.hpp>	// Pascal unit
#include <DB.hpp>	// Pascal unit

//------------------------------------------------------------------------------
 void TranslateForm(TWinControl *f,bool WithCaption=true);

 void TranslateDataSet(TDataSet *DataSet);
//------------------------------------------------------------------------------
#endif
