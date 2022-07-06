#ifndef xxFindH
#define xxFindH
#include "..//xxDataAccess.h"
#include "../xxArray.h"
#include <string.h>
namespace XSPACE
{
////////////////////////////////////////////////////////////////////////////////
// Find(Container,item)          // find the object
// Find(Container,item,From)     // find the object from
// Find(Container,item,From,To)  // find an object from and ending on
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
// Find(Container,item)          
template< template<typename> class TContainer, typename TItem >
inline int Find(const TContainer<TItem>& c,const TItem & i)
  {
   return internalFind(c,i,&c,(TItem*)0);
  }
// Find(Container,item,From)   
template< template<typename> class TContainer, typename TItem >
inline int Find(const TContainer<TItem>& c,const TItem & i,int From)
  {
   return internalFind(c,i,&c,(TItem*)0,From);
  }

// Find(Container,item,From,To) 
template< template<typename> class TContainer, typename TItem >
inline int Find(const TContainer<TItem>& c,const TItem & i,int From,int To)
  {
   return internalFind(c,i,&c,(TItem*)0,From,To);
  }
//------------------------------------------------------------------------------
// Find(Container,Container)        
template< template<typename> class TContainer,template<typename> class TContainerTemplate, typename TItem >
inline int Find(const TContainer<TItem>& c,const TContainerTemplate<TItem>& cTemplate)
  {
   return internalFindContainer(c,cTemplate,&c,&cTemplate,c.First(),c.Last());
  }
// Find(Container,Container,from)      
template< template<typename> class TContainer,template<typename> class TContainerTemplate, typename TItem >
inline int Find(const TContainer<TItem>& c,const TContainerTemplate<TItem>& cTemplate,int From)
  {
   return internalFindContainer(c,cTemplate,&c,&cTemplate,From,c.Last());
  }
// Find(Container,Container,from,to)     
template< template<typename> class TContainer,template<typename> class TContainerTemplate, typename TItem >
inline int Find(const TContainer<TItem>& c,const TContainerTemplate<TItem>& cTemplate,int From,int To)
  {
   return internalFindContainer(c,cTemplate,&c,&cTemplate,From,To);
  }
//------------------------------------------------------------------------------
// Find(Container,char*)    
template< template<typename> class TContainer>
inline int Find(const TContainer<char>& c,const char* i)
  {
   return internalFind(c,i,&c,c.First());
  }
// Find(Container,char*,from)    
template< template<typename> class TContainer>
inline int Find(const TContainer<char>& c,const char* i,int From)
  {
   return internalFind(c,i,&c,From);
  }

////////////////////////////////////////////////////////////////////////////////
// INTERNAL ROUTINE FUNCTIONS                                                 //
////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
template<typename TContainer, typename TItem >
int internalFind(const TContainer& c,const TItem & i,const TxSerialAccess*a,TItem*b)
 {
   int iterator = c.First();
   while(iterator!=0)
    {
     if(c.QGET(iterator)==i)return iterator;
     iterator = c.Next(iterator);
    }
   return 0;
 }
//------------------------------------------------------------------------------
template<typename TContainer, typename TItem>
 int internalFind(const TContainer& c,const TItem & i,const TxSerialAccess*,TItem*,int From)
  {
   int iterator = From;
   while(iterator!=0)
    {
     if(c.QGET(iterator)==i)return iterator;
     iterator = c.Next(iterator);
    }
   return 0;
  }
//------------------------------------------------------------------------------
template<typename TContainer, typename TItem>
 int internalFind(const TContainer& c,const TItem & i,const TxSerialAccess*,TItem*,int From,int To)
  {
   int iterator = From;
   while(iterator!=0&&iterator!=To)
    {
     if(c.QGET(iterator)==i)return iterator;
     iterator = c.Next(iterator);
    }
   return 0;
  }
//------------------------------------------------------------------------------
template<typename TContainer, typename TItem >
 int internalFind(const TContainer& c,const TItem & i,const TxRandomAccess*,TItem*,int From=1)
  {
   for(int j=From;j<=c.Size();j++)
     if(c.QGET(j)==i)return j;
   return 0;
  }
//------------------------------------------------------------------------------
template<typename TContainer, typename TItem >
 int internalFind(const TContainer& c,const TItem & i,const TxRandomAccess*,TItem*,int From,int To)
  {
   if(To>c.Size())To = c.Size();
   for(int j=From;j<=To;j++)
     if(c.QGET(j)==i)return j;
   return 0;
  }
//------------------------------------------------------------------------------
template<typename TContainer, typename TItem >
 int internalFind(const TContainer& c,const TItem & i,const TxMonolithAccess*,TItem*,int From=1)
  {
   TItem*ii = c.GetItems();
   for(int j=From-1;j<c.Size();j++)
     if(ii[j]==i)return j+1;
   return 0;
  }
//------------------------------------------------------------------------------
template<typename TContainer, typename TItem >
 int internalFind(const TContainer& c,const TItem & i,const TxMonolithAccess*,TItem*,int From,int To)
  {
   TItem*ii = c.GetItems();
   if(To>c.Size())To = c.Size();
   for(int j=From-1;j<To;j++)
     if(ii[j]==i)return j+1;
   return 0;
  }
//------------------------------------------------------------------------------
template<typename TContainer>
inline int internalFind(const TContainer& c,const char & i,const Str*,char*,int From=1)
  {
   const char* s = c.c_str();
   const char* ss = strchr(s+From-1,i);
   if(ss)return ss-s+1;
   return 0;
  }
//------------------------------------------------------------------------------
// Find(Container,Container,From,To) 
template<typename TContainer,typename TContainer2>
int internalFindContainer(const TContainer&c,const TContainer2 &cTemplate,const TxRandomAccess*,const TxRandomAccess*,int From,int To)
 { //until the "naive" method, in future we have to recycle
  register int j;
  int L_Templ = cTemplate.Size();
  int L = To-L_Templ+1;
  for(int i=From;i<=L;i++)
   {
    for(j=1;j<=L_Templ;j++)
     if(c[i+j-1]!=cTemplate[j])break;
    if(j>L_Templ)return i;
   }
  return 0;
 }
//------------------------------------------------------------------------------
// Find(Container,char*,from)   
template<typename TContainer>
inline int internalFind(const TContainer& c,const char * chars,const Str*,int From=1)
  {
   const char* s = c.c_str();
   const char* ss = strstr(s+From-1,chars);
   if(ss)return ss-s+1;
   return 0;
  }

// FindFirstIn 
template< template<typename> class TContainer>
inline int FindFirstIn(const TContainer<char>& c,const char* chars)
  {
   return internalFindFirstIn(c,chars,&c,c.First());
  }
template< template<typename> class TContainer>
inline int FindFirstIn(const TContainer<char>& c,const char* chars,int From)
  {
   return internalFindFirstIn(c,chars,&c,From);
  }
template<typename TContainer>
int internalFindFirstIn(const TContainer& c,const char * chars,const TxSerialAccess*,int From)
  {
    int Current = From;
    while(Current)
     {
      int j=0;
      while(chars[j])
       {
        if(chars[j]==c.QGET(Current))return Current;
        j++;
       }
      Current = c.Next(Current);
     }
    return 0;
  }
template<typename TContainer>
int internalFindFirstIn(const TContainer& c,const char * chars,const TxMonolithAccess*,int From)
  {
   char *D = c.GetItems();
   int Len = c.Size();
   for(int i=From-1;i<Len;i++)
    {
      int j=0;
      while(chars[j])
       {
        if(chars[j]==D[i])return i+1;
        j++;
       }
    }
   return 0;
  }

template< template<typename> class TContainer>
inline int FindFirstOut(const TContainer<char>& c,const char* chars)
  {
   return internalFindFirstOut(c,chars,&c,c.First());
  }
template< template<typename> class TContainer>
inline int FindFirstOut(const TContainer<char>& c,const char* chars,int From)
  {
   return internalFindFirstOut(c,chars,&c,From);
  }
template<typename TContainer>
int internalFindFirstOut(const TContainer& c,const char * chars,const TxSerialAccess*,int From)
  {
    int Current = From;
    while(Current)
     {
      int j=0;
      while(chars[j])
       {
        if(chars[j]==c.QGET(Current))break;
        j++;
       }
      if(chars[j]==0)return Current;
      Current = c.Next(Current);
     }
    return 0;
  }
template<typename TContainer>
int internalFindFirstOut(const TContainer& c,const char * chars,const TxMonolithAccess*,int From)
  {
   char *D = c.GetItems();
   int Len = c.Size();
   for(int i=From-1;i<Len;i++)
    {
      int j=0;
      while(chars[j])
       {
        if(chars[j]==D[i])break;
        j++;
       }
      if(chars[j]==0)return i+1;       
    }
   return 0;
  }
};
#endif
