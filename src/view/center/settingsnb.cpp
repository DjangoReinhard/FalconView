#include <settingsnb.h>
#include <QVBoxLayout>
#include <QTabWidget>


SettingsNotebook::SettingsNotebook(QWidget *parent)
 : DynWidget(parent)
 , tw(nullptr) {
  setObjectName(tr("SettingsNotebook"));
  setLayout(new QVBoxLayout);
  setContentsMargins(0, 0, 0, 0);
  tw = new QTabWidget();
  tw->setTabPosition(QTabWidget::TabPosition::South);
  tw->setTabShape(QTabWidget::TabShape::Triangular);
  layout()->addWidget(tw);
  }


SettingsNotebook::~SettingsNotebook() {
  }


void SettingsNotebook::addPage(DynWidget* page) {
  assert(page);
  page->init();
  tw->addTab(page, page->objectName());
  }


void SettingsNotebook::connectSignals() {
  }


void SettingsNotebook::updateStyles() {
  }
