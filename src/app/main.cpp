#include <mainwindow.h>
#include <testmain.h>
#include <falconviewdb.h>
#include <guicore.h>
#include <guikernelcreator.h>

#include <QCoreApplication>
#include <QApplication>
#include <QFileInfo>
#include <QStyleFactory>
#include <QTranslator>
#include <QKeySequence>
#include <QDebug>


int main(int argc, char *argv[]) {
  try {
      QApplication a(argc, argv);

      GuiCore::setKernelCreator(new GuiKernelCreator());
      FalconViewDB dbHelper;
      GuiCore      appCore(a, "FalconView", dbHelper);
#ifndef WANT_SHORT_TESTS
      MainWindow* mainWindow = new MainWindow();
#else
      TestMain*   mainWindow = new TestMain();
#endif

      appCore.setMainWindow(mainWindow);
      mainWindow->initialize();
      appCore.checkBE();
      mainWindow->show();
      int rv = a.exec();

      return rv;
      }
  catch (const QString& s) {
      qDebug() << s;
      }
  catch (const std::exception& e) {
      qDebug() << e.what();
      }
  }
