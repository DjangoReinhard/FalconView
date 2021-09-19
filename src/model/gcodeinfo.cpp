#include <gcodeinfo.h>
#include <QString>
#include <interp_base.hh>
#include <QDebug>


GCodeInfo::GCodeInfo() {
  for (int i=1; i < ACTIVE_G_CODES; ++i) {
      QString k = QString("GC%1").arg(i);

      vm.setValue(k, " ");
      }
  for (int i=1; i < ACTIVE_M_CODES; ++i) {
      QString k = QString("MC%1").arg(i);

      vm.setValue(k, " ");
      }
  vm.setValue("fileName", " ");
  vm.setValue("curLine", 0);
  }


void GCodeInfo::update(int* activeGCodes
                     , int* activeMCodes
                     , const QString& fileName
                     , int curLine) {
    /*
raw gcode value:  0
raw gcode value:  800
raw gcode value:  -1
raw gcode value:  170
raw gcode value:  400
raw gcode value:  200
raw gcode value:  900
raw gcode value:  940
raw gcode value:  540
raw gcode value:  490
raw gcode value:  990
raw gcode value:  640
raw gcode value:  -1
raw gcode value:  970
raw gcode value:  911
raw gcode value:  80
raw gcode value:  922
     */
  for (int i=0; i < ACTIVE_G_CODES; ++i) {
      qDebug() << "raw gcode value: " << activeGCodes[i];
      QString k = QString("GC%1").arg(i);
      QString v = " ";

      if (activeGCodes[i] >= 0) {
         double dv = (double)activeGCodes[i] / 10.0;

         v = QString("G%1").arg(dv, 0, 'F', activeGCodes[i] % 10 ? 1 : 0);
         }
//      qDebug() << "active code: " << k << "\t" << v;
      vm.setValue(k, v);
      }
  for (int i=0; i < ACTIVE_M_CODES; ++i) {
      qDebug() << "raw mcode value: " << activeMCodes[i];
      QString k = QString("MC%1").arg(i);
      QString v = " ";

      if (activeMCodes[i] >= 0) {
         double dv = (double)activeMCodes[i];

         v = QString("M%1").arg(dv, 0, 'F', 0);
         }
//      qDebug() << "active code: " << k << "\t" << v;
      vm.setValue(k, v);
      }
  vm.setValue("fileName", fileName);
  vm.setValue("curLine", curLine + 1);
  }
