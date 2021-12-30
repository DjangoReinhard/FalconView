#include "micon.h"


MIcon::MIcon(const QString& stdFileName, const QString& selFileName)
 : QIcon(stdFileName) {
  addPixmap(QPixmap(selFileName), QIcon::Mode::Normal, QIcon::State::On);
  addPixmap(QPixmap(disabledFileName), QIcon::Mode::Disabled);
  }


MIcon::MIcon(const QString& normalFile, const QString& activeFile, const QString& selectedFile)
 : QIcon(normalFile) {
  addPixmap(QPixmap(activeFile), QIcon::Mode::Active);
  addPixmap(QPixmap(selectedFile), QIcon::Mode::Selected);
  }


void MIcon::setDisabledFileName(const QString &fileName) {
  MIcon::disabledFileName = fileName;
  }


QString MIcon::disabledFileName;
