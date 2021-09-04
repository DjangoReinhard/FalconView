#include <gcodeinfo.h>
#include <QString>
#include <interp_base.hh>


GCodeInfo::GCodeInfo() {
  for (int i=0; i < ACTIVE_G_CODES; ++i) {
      QString k = QString("GC%1").arg(i);

      vm.setValue(k, " ");
      }
  for (int i=0; i < ACTIVE_M_CODES; ++i) {
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
  for (int i=0; i < ACTIVE_G_CODES; ++i) {
      QString k = QString("GC%1").arg(i);
      QString v = QString("G%1").arg((double)activeGCodes[i] / 100.0, 0, 'F', 2);

      //TODO: strip real part if decimals are 0
      vm.setValue(k, v);
      }
  for (int i=0; i < ACTIVE_M_CODES; ++i) {
      QString k = QString("MC%1").arg(i);
      QString v = QString("M%1").arg((double)activeMCodes[i] / 100.0, 0, 'F', 2);

      //TODO: strip real part if decimals are 0
      vm.setValue(k, v);
      }
  vm.setValue("fileName", fileName);
  vm.setValue("curLine", curLine);
  }
