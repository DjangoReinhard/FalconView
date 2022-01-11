#include <settingsnb.h>
#include <guicore.h>
#include <configacc.h>
#include <valuemanager.h>
#include <QVBoxLayout>
#include <QVariant>
#include <QTabWidget>
#include <QKeyEvent>
#include <QTabBar>
#include <QDebug>
#include <QFile>
#include <QFont>


SettingsNotebook::SettingsNotebook(QWidget *parent)
 : AbstractCenterWidget(QString(), parent)
 , tw(nullptr) {
  setObjectName("SettingsNotebook");
  setWindowTitle(tr("SettingsNotebook"));
  }


QWidget* SettingsNotebook::createContent() {
  QTabWidget::TabPosition tp = QTabWidget::TabPosition::South;

  tw = new QTabWidget();
  tw->setTabPosition(tp);
  tw->setTabShape(QTabWidget::TabShape::Rounded);
  tw->setUsesScrollButtons(true);
  tw->setStyleSheet(loadStyles(tp));

  return tw;
  }


SettingsNotebook::~SettingsNotebook() {
  }


void SettingsNotebook::addPage(AbstractCenterWidget* page) {
  assert(page);
  page->installEventFilter(this);
  connect(page, &AbstractCenterWidget::dataChanged, this, &SettingsNotebook::pageChanged);

  //NOTE: have to wrap tab-text with space, as Qt truncates styled texts
  tw->addTab(page, QString("  ") + page->windowTitle() + "  ");
  }


bool SettingsNotebook::eventFilter(QObject*, QEvent* event) {
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
  connect(vm->getModel("showAllButCenter"), &ValueModel::valueChanged
        , this, &SettingsNotebook::enableTabs);
  }


void SettingsNotebook::enableTabs(const QVariant& var) {
  bool enable = var.toBool();

  tw->tabBar()->setEnabled(enable);
  }


void SettingsNotebook::pageChanged(AbstractCenterWidget* page, const QVariant &dirty) {
  int n = tw->currentIndex();

  if (tw->currentWidget() != page) {
     for (int i=0; i < tw->count(); ++i) {
         if (tw->widget(i) == page) {
            n = i;
            break;
            }
         }
     }
  if (dirty.toBool()) tw->setTabText(n, QString("  *") + page->windowTitle() + "  ");
  else                tw->setTabText(n, QString("  ") + page->windowTitle() + "  ");
  }


void SettingsNotebook::updateStyles() {
  }


void SettingsNotebook::currentChanged(int) {
  core->setWindowTitle(tr(tw->currentWidget()->windowTitle().toStdString().c_str()));
  if (cfg->value("showHelpAtPageChange").toBool()) {
     qDebug() << "SN: show help for page:" << tw->currentWidget()->objectName();
     core->help4Keyword(tw->currentWidget()->objectName());
     }
  }


void SettingsNotebook::closeEvent(QCloseEvent* e) {
  qDebug() << "DynWidget::closeEvent() on widget " << objectName();
  int mx = tw->count();

  for (int i=0; i < mx; ++i) {
      AbstractCenterWidget* w = static_cast<AbstractCenterWidget*>(tw->widget(i));

      if (w) w->closeEvent(e);
      }
  }


void SettingsNotebook::resizeEvent(QResizeEvent* e) {
  qDebug() << "SN: resize event - from" << e->oldSize() << "to size:" << e->size();
  if (tw && tw->currentWidget()) {
     qDebug() << "SN: current widget is" << tw->currentWidget()->objectName();
    //  ToolManager* tm = static_cast<ToolManager*>(tw->currentWidget());

    //  if (tm) tm->setSize(e->size().width() - 15, e->size().height() - 80);
     }
  }


void SettingsNotebook::showEvent(QShowEvent* e) {
  AbstractCenterWidget::showEvent(e);
  if (e->type() == QEvent::Show) {
     if (cfg->value("showHelpAtPageChange").toBool()) {
        qDebug() << "SN: show help for page:" << tw->currentWidget()->objectName();
        core->help4Keyword(tw->currentWidget()->objectName());
        }
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
         [[fallthrough]];
    default:
//         qDebug() << "SN: whatever key (" << e->key()
//                  << ") pressed, modifier: " << e->modifiers()
//                  << "event-ts: " << e->timestamp();
         AbstractCenterWidget::keyPressEvent(e); break;
    }
  }


void SettingsNotebook::dump() {
  int mx = tw->count();

  for (int i=0; i < mx; ++i) {
      AbstractCenterWidget* page = static_cast<AbstractCenterWidget*>(tw->widget(i));

      if (page) qDebug() << "SN: page found ->" << page->objectName() << "with title" << page->windowTitle();
      else      qDebug() << "SN: invalid page at #" << i;
      qDebug() << "page has min. sizeHint:\t" << page->minimumSizeHint()
               << "\tand min height:\t"       << page->minimumHeight();
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
