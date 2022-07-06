#include <QtCore/QCoreApplication>
#include <stdio.h>
#include "D:\work\!\xLib\xBase.h"
#include "D:\work\!\xLib\tests\Units\xArrayTest.h"
#include "D:\work\!\xLib\tests\Units\xListTest.h"
#include "D:\work\!\xLib\tests\Units\xPTR_Test.h"
#include "D:\work\!\xLib\tests\Units\xArraySpeedTest.h"
#include "D:\work\!\xLib\tests\Units\xFindSpeedTest.h"



int main(int argc, char *argv[])
{
   printf("Test");
   const char*c=ArrayTest();
   if(c)
   printf("%s\n",c);
   else printf("\n\nArray TEST OK\n");

   c = ListTest();
   if(c)printf("Error:%s\n",c);
   else printf("\n\nList TEST OK\n");

   c = PTRTest();
   if(c)printf("Error:%s\n",c);
   else printf("\n\nPTR TEST OK\n");

   ArraySpeedTest();


   FindSpeedTest();


   XSPACE::Stack<char> MyStack;
   MyStack.Push('a');
   MyStack.Push('b');
   MyStack.Push('c');
   char saasa=MyStack.Pop();
   printf("%c\n",saasa);
   saasa=MyStack.Pop();
   printf("%c\n",saasa);
   saasa=MyStack.Pop();
   printf("%c\n",saasa);
   XSPACE::Queue<char> MyQueue;
   MyQueue.Push('a');
   MyQueue.Push('b');
   MyQueue.Push('c');
   saasa=MyQueue.Pop();
   printf("%c\n",saasa);
   saasa=MyQueue.Pop();
   printf("%c\n",saasa);
   saasa=MyQueue.Pop();
   printf("%c\n",saasa);
   int ioii=MyQueue.Size();
   printf("%d\n",ioii);




   QCoreApplication a(argc, argv);

    return a.exec();
}
