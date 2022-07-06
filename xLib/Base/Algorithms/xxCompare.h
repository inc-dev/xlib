#ifndef xxCompareH
#define xxCompareH
#include "../xxDataAccess.h"
#include "../xxArray.h"
#include <string.h>
//------------------------------------------------------------------------------
namespace XSPACE
{
//compare
//Return Value
//If s1 is...	return value is...
//less than s2     < 0
//the same as s2  == 0
//greater than s2 > 0
template<class TContainer1,class TContainer2>
inline int Compare(const TContainer1 &c1,const TContainer2 &c2)
 {
  return internalCompare(c1,c2,&c1,&c2);
 }
inline int Compare(const Str&s1,const Str&s2)
 {
   return strcmp(s1.c_str(), s2.c_str());
 }
//equal (this is a faster operation than Compare (...) == 0)
inline bool Equally(const Str&s1,const Str&s2)
 {
  if(s1.Size()!=s2.Size())return false;
  const char*ch1=s1.c_str(),*ch2=s2.c_str();
  if(ch1==ch2)return true;
  return memcmp(ch1,ch2,s1.Size())==0;
 }
inline bool Equally(const Str&s1,const char * ch){return strcmp(s1.c_str(),ch)==0;}
inline bool Equally(const char * ch,const Str&s2){return strcmp(ch,s2.c_str())==0;}

template< template<typename TItem> class TContainer1, template<typename TItem> class TContainer2, typename TItem >
//template<class TContainer1,class TContainer2>
inline bool Equally(const TContainer1<TItem> &c1,const TContainer2<TItem> &c2)
 {
  return internalEqually(c1,c2,&c1,&c2);
 }
//------------------------------------------------------------------------------
template<class TContainer1, class TContainer2>
bool internalEqually(const TContainer1& c1,const TContainer2& c2,const TxSerialAccess*,const TxSerialAccess*)
 {
    int iterator1 = c1.First(),iterator2 = c2.First();
   while(iterator1!=0&&iterator1!=0)
    {
     if(c1.QGET(iterator1)!=c2.QGET(iterator2))return false;
     iterator1 = c1.Next(iterator1);
     iterator2 = c2.Next(iterator2);
    }
   return iterator1==iterator2;
 }
template<class TContainer1, class TContainer2>
bool internalEqually(const TContainer1& c1,const TContainer2& c2,const TxRandomAccess*,const TxRandomAccess*)
 {
  int size=c1.Size();
  if(size!=c2.Size())return false;
  for(int i=1;i<=size;i++)
   if(c1.QGET(i)!=c1.QGET(i))return false;
  return true;
 }

//------------------------------------------------------------------------------
template<class TContainer1, class TContainer2>
int internalCompare(const TContainer1& c1,const TContainer2& c2,const TxSerialAccess*,const TxSerialAccess*)
 {
   int iterator1 = c1.First(),iterator2 = c2.First();
   while(iterator1!=0&&iterator2!=0)
    {
     if(c1.QGET(iterator1)!=c2.QGET(iterator2))
      {
       if(c1.QGET(iterator1)<c2.QGET(iterator2))return -1;
       return 1;
      }
     iterator1 = c1.Next(iterator1);
     iterator2 = c2.Next(iterator2);
    }
   return iterator1-iterator2;
 }
int StrCmp(const char * c1,const  char * c2);
int StrCmpICLat(const char * c1,const  char * c2);
}
//------------------------------------------------------------------------------
#endif
