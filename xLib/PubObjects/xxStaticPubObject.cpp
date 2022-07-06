#ifndef __GNUC__
#pragma hdrstop
#endif
#include "xxStaticPubObject.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
//------------------------------------------------------------------------------
bool IxStaticClassSpace::RegisterClass(IxBaseClass *Class)
 {
  Class->ClassSpace = this;
  ClassList.Add(Class);            
  return true;
 };                  
IxBaseClass*IxStaticClassSpace::FindClass(const Str& ClassName)
 {
  int i = ClassList.First();
  while(i)
   {                          
    IxBaseClass *Class = ClassList.Get(i);
     if(Class->GetName()==ClassName)return Class;
    i = ClassList.Next(i);
   }
  i = IncludingClassSpacesList.First();
  while(i)
   {
    IxClassSpace*ClassSpace=IncludingClassSpacesList.Get(i);
    if(ClassSpace)
     {
      IxBaseClass *Class = ClassSpace->FindClass(ClassName);
      if(Class)return Class;
     }
    i = IncludingClassSpacesList.Next(i);
   }
  return 0; 
 }
//------------------------------------------------------------------------------
                
}
//------------------------------------------------------------------------------
#ifndef __GNUC__
#pragma package(smart_init)
#endif
