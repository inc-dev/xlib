#include <QtCore/QCoreApplication>
#include "..\..\..\..\PubObjects\xxStaticPubObject.h"
#include "..\..\..\..\tests\Units\xxLibTest.h"

int main(int argc, char *argv[])
{

    Test();
    XSPACE::ObjBool b;
    XSPACE::TxSimplEnumItem c;
    XSPACE::TxSimplEnumItems d;
    c.Name = "hi";
    QCoreApplication a(argc, argv);

    return a.exec();
}
