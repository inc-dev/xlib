#include <QtCore/QCoreApplication>
#include "..\..\..\..\tests\Units\xArrayTest.h"
//#include "..\..\..\..\..\xBase.h"
//using namespace XSPACE;
#include <stdio.h>
class TTest
{
 int j;
public:
inline void Fun1(){j=j*j+1;}
 virtual void Fun2(){j=j*j+1;}
 void Clear(){j=0;}
 void prn(){printf("%d\n",j);}
};

int main(int argc, char *argv[])
{
    printf("qwer\n");
    TTest t;
    int count = 20000005; double tim;
    t.Clear();
    tim=xGetMilliSeconds();
    for(int i = 0; i<count;i++)
       {
        t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();
        t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();
        t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();
        t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();
        t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();
        t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();
        t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();
        t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();
        t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();
        t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();t.Fun2();
       }
        printf("%f\n",xGetMilliSeconds()-tim);
   t.prn();
    t.Clear();
    tim=xGetMilliSeconds();
    for(int i = 0; i<count;i++)
     {
        t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();
        t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();
        t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();
        t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();
        t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();
        t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();
        t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();
        t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();
        t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();
        t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();t.Fun1();
     }
    printf("%f\n",xGetMilliSeconds()-tim);
    t.prn();
   // QCoreApplication a(argc, argv);
    //printf("hi");
    //return a.exec();
//       XSPACE::Stack<char> MyStack;
    printf("%s\n",ArrayTest());
    return 0;
}
