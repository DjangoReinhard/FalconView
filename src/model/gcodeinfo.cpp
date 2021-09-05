#include <gcodeinfo.h>
#include <QString>
#include <interp_base.hh>
#include <QDebug>


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
      double dv = (double)activeGCodes[i] / 10.0;
      QString v = QString("G%1").arg(dv, 0, 'F', 1);

      //TODO: strip real part if decimals are 0
      qDebug() << "active code: " << k << "\t" << v;
      vm.setValue(k, dv > 0 ? v : " ");
      }
  for (int i=0; i < ACTIVE_M_CODES; ++i) {
      QString k = QString("MC%1").arg(i);
      double dv = (double)activeMCodes[i] / 10.0;
      QString v = QString("M%1").arg(dv, 0, 'F', 1);

      //TODO: strip real part if decimals are 0
      qDebug() << "active code: " << k << "\t" << v;
      vm.setValue(k, dv > 0 ? v : " ");
      }
  vm.setValue("fileName", fileName);
  vm.setValue("curLine", curLine);
  }
