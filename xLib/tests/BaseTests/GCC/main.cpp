#include <cstdlib>
#include <iostream>
#include <wx/string.h>
#include "..\..\..\Base\xBase.h"
#include "..\..\Units\xArrayTest.h"
#include "..\..\Units\xPTR_Test.h"
#include "..\..\Units\xArraySpeedTest.h"
#include "..\..\Units\xFindSpeedTest.h"
#include "..\..\Units\xListTest.h"
using namespace std;
int main(int argc, char *argv[])
{
    XSPACE::PTR<int> a,b;
    int* p=0;
    if((int*)a!=p)
     printf("\n\nOK\n");
    char*c=ArrayTest();
    if(c)
    printf("%s\n",c);
    else printf("\n\nArray TEST OK\n");

    c=ListTest();
    if(c)
    printf("%s\n",c);
    else printf("\n\nList TEST OK\n");

    c=PTRTest();
    if(c)
    printf("%s\n",c);
    else printf("\n\nPTR TEST OK\n");
    
//    FindSpeedTest();
    ArraySpeedTest();
    system("PAUSE");
    return EXIT_SUCCESS;
}
