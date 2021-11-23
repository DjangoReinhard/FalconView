#include <settingsnb.h>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QKeyEvent>
#include <QTabBar>
#include <QDebug>
#include <QFile>
#include <QFont>


SettingsNotebook::SettingsNotebook(QWidget *parent)
 : DynCenterWidget(QString(), "SettingsNotebook", false, parent)
 , tw(nullptr) {
  setObjectName(SettingsNotebook::className);
  }


QWidget* SettingsNotebook::createContent() {
  QTabWidget::TabPosition tp = QTabWidget::TabPosition::South;

  tw = new QTabWidget();
  tw->setTabPosition(tp);
  tw->setTabShape(QTabWidget::TabShape::Rounded); 
  tw->setStyleSheet(loadStyles(tp));

  return tw;
  }


SettingsNotebook::~SettingsNotebook() {
  }


void SettingsNotebook::addPage(DynCenterWidget* page) {
  assert(page);
  page->initialize();

  //NOTE: have to wrap tab-text with space, as Qt truncates styled texts
  tw->addTab(page, QString("  ") + page->windowTitle() + "  ");
  }


void SettingsNotebook::connectSignals() {
  }


void SettingsNotebook::updateStyles() {
  }


void SettingsNotebook::closeEvent(QCloseEvent* e) {
  qDebug() << "DynWidget::closeEvent() on widget " << objectName();
  int mx = tw->count();

  for (int i=0; i < mx; ++i) {
      DynCenterWidget* w = static_cast<DynCenterWidget*>(tw->widget(i));

      if (w) w->closeEvent(e);
      }
  }


void SettingsNotebook::keyPressEvent(QKeyEvent* e) {
  //TODO: add shortcut for each page
  switch (e->key()) {
    default: DynCenterWidget::keyPressEvent(e); break;
    }
  }


QString SettingsNotebook::loadStyles(QTabWidget::TabPosition tp) {
  QFile   styles;
  QString rv;

  if (tp == QTabWidget::TabPosition::South)
     styles.setFileName(":/res/BottomTabButtonStyles.css");
  else if (tp == QTabWidget::TabPosition::North)
     styles.setFileName(":/res/TopTabButtonStyles.css");
  if (styles.open(QIODevice::ReadOnly | QIODevice::Text)) {
     rv = styles.readAll();
     styles.close();
     }
  return rv;
  }


const QString SettingsNotebook::className = "SettingsNotebook";
