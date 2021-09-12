#include "micon.h"


MIcon::MIcon(const QString& stdFileName, const QString& selFileName)
 : QIcon(stdFileName) {
  addPixmap(QPixmap(selFileName), QIcon::Mode::Normal, QIcon::State::On);
  addPixmap(QPixmap(disabledFileName), QIcon::Mode::Disabled);
  }


void MIcon::setDisabledFileName(const QString &fileName) {
  MIcon::disabledFileName = fileName;
  }


QString MIcon::disabledFileName;
