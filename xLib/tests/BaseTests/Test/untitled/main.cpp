#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

class A
 {
  private:
  int b;
   public:
  A(){b = 1;}
  A(const A&out){b = out.b;}
  void hhh()
  {
      A uuu;
      uuu.b = b;
  }
 };
A test1;
A test2(test1);

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    test1.hhh();
    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/untitled/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
