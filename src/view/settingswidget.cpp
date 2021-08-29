#include <settingswidget.h>
#include <QFile>
#include <QUiLoader>
#include <QGridLayout>


SettingsWidget::SettingsWidget(QFile& uiDesc, QWidget* parent)
 : QWidget(parent) {
  initializeWidget(uiDesc);
  }


void SettingsWidget::initializeWidget(QFile& uiDesc) {
  QUiLoader    loader;
  QWidget*     w = loader.load(&uiDesc, this);
  QGridLayout* layout = new QGridLayout(this);

  uiDesc.close();
  setLayout(layout);
  layout->addWidget(w, 0, 0);
  }
