#include <gcodeinfo.h>
#include <guicore.h>
#include <QString>
#include <QDebug>


GCodeInfo::GCodeInfo() {
  vm.setValue("fileName", " ");
  vm.setValue("curLine", -1);
  }


void GCodeInfo::update(int* activeGCodes
                     , int* activeMCodes
                     , const QString& fileName
                     , int curLine) {
  int mx = GuiCore().activeGCodes();

  for (int i=1; i < mx; ++i) {
      QString k = QString("GC%1").arg(i);
      QString v = " ";

      if (activeGCodes[i] >= 0) {
         double dv = (double)activeGCodes[i] / 10.0;

         v = QString("G%1").arg(dv, 0, 'F', activeGCodes[i] % 10 ? 1 : 0);
         }
//      qDebug() << "< active GCode(" << i << "):" << k << "\t" << v << "\traw:" << activeGCodes[i];
      vm.setValue(k, v);
      }
  mx = GuiCore().activeMCodes();

  for (int i=1; i < mx; ++i) {
      QString k = QString("MC%1").arg(i);
      QString v = " ";

      if (activeMCodes[i] >= 0) {
         double dv = (double)activeMCodes[i];

         v = QString("M%1").arg(dv, 0, 'F', 0);
         }
//      qDebug() << "> active MCode(" << i << "):" << k << "\t" << v << "\traw:" << activeMCodes[i];
      vm.setValue(k, v);
      }
  vm.setValue("fileName", fileName);
  vm.setValue("curLine", curLine + 1);
  }
