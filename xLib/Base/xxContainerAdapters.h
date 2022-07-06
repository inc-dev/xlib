#ifndef xxContainerAdaptersH
#define xxContainerAdaptersH
#include "xxArray.h"
#include "xxList.h"
//------------------------------------------------------------------------------
namespace XSPACE
{
    template<typename T>
    class Stack:public Array<T>
     {
      public:
       typedef Array<T> Container;
       inline bool isEmpty(){return Container::Size()==0;}
       inline void Push(const T&item){Container::Add(item);}
       inline T    Pop(){T t;int l=Container::Last();if(l){t=Container::Get(l); Container::Delete(l);} return t;}
     };
    template<typename T>
    class Queue:public List<T>
     {
      public:
       typedef List<T> Container;
       inline bool isEmpty(){return Container::Size()==0;}
       inline void Push(const T&item){Container::Insert(Container::First(),item);}
       inline T    Pop(){T t;int l=Container::Last();if(l){t=Container::Get(l); Container::Delete(l);} return t;}
     };
}
#endif
