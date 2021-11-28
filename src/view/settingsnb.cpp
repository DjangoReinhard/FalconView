#include <settingsnb.h>
#include <core.h>
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
  page->installEventFilter(this);

  //NOTE: have to wrap tab-text with space, as Qt truncates styled texts
  tw->addTab(page, QString("  ") + page->windowTitle() + "  ");
  }

bool SettingsNotebook::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::KeyPress) {
     QKeyEvent* e = static_cast<QKeyEvent*>(event);

     switch (e->key()) {
       case Qt::Key_0:
       case Qt::Key_1:
       case Qt::Key_2:
       case Qt::Key_3:
       case Qt::Key_4:
       case Qt::Key_5:
       case Qt::Key_6:
       case Qt::Key_7:
       case Qt::Key_8:
       case Qt::Key_9:
            qDebug() << "SN::filter - numberkey pressed, modifier: " << e->modifiers()
                     << "event-ts: " << e->timestamp();

            if (e->modifiers() == Qt::AltModifier) {
               keyPressEvent(e);
               return true;
               }
       default: break;
       }
     }
  return false;
  }


void SettingsNotebook::connectSignals() {
  connect(tw, &QTabWidget::currentChanged, this, &SettingsNotebook::currentChanged);
  }


void SettingsNotebook::updateStyles() {
  }


void SettingsNotebook::currentChanged(int) {
  Core().setWindowTitle(tr(tw->currentWidget()->windowTitle().toStdString().c_str()));
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
  switch (e->key()) {
    case Qt::Key_0:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
         qDebug() << "SN: numberkey pressed, modifier: " << e->modifiers()
                  << "event-ts: " << e->timestamp();

         if (e->modifiers() == Qt::AltModifier) {
            // real humans don't start counting at 0
            if (switchTabPage(e->key() - Qt::Key_0 - 1)) {
               e->accept();
               break;
               }
            }
    default:
         qDebug() << "SN: whatever key (" << e->key()
                  << ") pressed, modifier: " << e->modifiers()
                  << "event-ts: " << e->timestamp();
         DynCenterWidget::keyPressEvent(e); break;
    }
  }


bool SettingsNotebook::switchTabPage(int pageIndex) {
  qDebug() << "switch TAB-page to index #" << pageIndex << " - pageCount:" << tw->count();

  if (pageIndex < 0) pageIndex = 9;
  if (pageIndex < tw->count()) {
     tw->tabBar()->setCurrentIndex(pageIndex);

     return true;
     }
  return false;
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
