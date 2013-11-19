#include <QApplication>
#include <QTranslator>
#include <DNTSystemDB.h>
#include <DNTRegister.h>
#include "MainWindow.h"
#include "App.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QTranslator ts;
  QString lang = QLocale::system().name();
  QString fileName = qApp->applicationDirPath();
  fileName.append("/translations/qt_");
  fileName.append(lang);
  if (ts.load(fileName))
    qApp->installTranslator(&ts);

  App app;
  if (!app.prepare()) return -1;

  MainWindow w;
  w.show();

  return a.exec();
}
