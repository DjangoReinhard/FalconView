#include <fixturemanager.h>
#include <flowlayout.h>
#include <fixtureedit.h>
#include <QMessageBox>
#include <QScrollArea>
#include <QShowEvent>
#include <QDebug>


FixtureManager::FixtureManager(const AxisMask& mask, QWidget* parent)
 : DynCenterWidget(QString(), "FixtureManager", false, parent)
 , client(new QWidget(this))
 , axisMask(mask) {
  setObjectName("FixtureManager");
  setWindowTitle("FixtureManager");
  }


QWidget* FixtureManager::createContent() {
  FlowLayout*  fl = new FlowLayout(client);
  QScrollArea* sa = new QScrollArea(this);
  FixtureEdit* fe = new FixtureEdit(tr("Offsets"), 0, axisMask);

  client->setLayout(fl);
  fe->setEnabled(false);
  fl->setContentsMargins(0, 0, 0, 0);
  fl->addWidget(fe);
  for (int i=0; i < 9; ++i) {
      if (i < 6) fe = new FixtureEdit(QString("G%1").arg(54 + i), i+1, axisMask);
      else       fe = new FixtureEdit(QString("G59.%1").arg(i - 5), i+1, axisMask);
      fe->setEnabled(false);
      fl->addWidget(fe);
      }
  sa->setWidgetResizable(true);
  client->setObjectName("client");
  sa->setAutoFillBackground(true);
  sa->setWidget(client);

  return sa;
  }


void FixtureManager::activateEditor(int n) {
  QLayout* l = client->layout();
  int      mx = l->count();

  if (n < 0)   n = 0;
  if (n >= mx) n = mx - 1;
  qDebug() << "FM::activateEditor(" << n << ")";
  for (int i=0; i < mx; ++i)
      l->itemAt(i)->widget()->setEnabled(i == n);
  QScrollArea* sa = static_cast<QScrollArea*>(layout()->itemAt(0)->widget());

  if (sa) sa->ensureWidgetVisible(l->itemAt(n)->widget());
  }


void FixtureManager::connectSignals() {
  }


void FixtureManager::updateStyles() {
//  this->setStyleSheet("QWidget#client { background: #9CF788; }");
  }


void FixtureManager::keyPressEvent(QKeyEvent* e) {
  switch (e->key()) {
    case '0':   // offsets
    case '1':   // G54
    case '2':   // G55
    case '3':   // G56
    case '4':   // G57
    case '5':   // G58
    case '6':   // G59
    case '7':   // G59.1
    case '8':   // G59.2
    case '9':   // G59.3
         if (e->modifiers() == Qt::KeyboardModifier::ControlModifier) {
            qDebug() << "FM: detected Ctrl+Number - activateEditor" << (e->key() - '0');
            activateEditor(e->key() - '0');
            e->accept();
            break;
            }
    default: {
         QWidget* w = static_cast<QWidget*>(parent());

         qDebug() << "FM: pressed key: " << e->key()
                  << "modifiers: " << e->modifiers()
                  << "event->ts: " << e->timestamp();
         DynCenterWidget::keyPressEvent(e);
         } break;
    }
}


void FixtureManager::resizeEvent(QResizeEvent *e) {
  qDebug() << "resize from:" << e->oldSize() << "\tto" << e->size();
  DynCenterWidget::resizeEvent(e);
  }


void FixtureManager::showEvent(QShowEvent* e) {
  DynCenterWidget::showEvent(e);
  qDebug() << "FM: show Event ...";
  if (e->type() == QEvent::Show) {
     activateEditor(0);
     QMessageBox::information(this
                            , tr("QMessageBox::information()")
                            , tr("<p>Fixture-Manager helps you manage your individual "
                                 "coordinate system offsets.</p><p>Use CTRL+number to activate "
                                 "an editor. G54 is CTRL+1, G55 is CTRL+2 and CTRL+0 "
                                 "activates the relative offsets.</p><p>TAB / BackTAB can be"
                                 "used to select the axis. In an axis field, just enter the "
                                 "value you'd like to see at the current postion.</p><p>"
                                 "Usually you'd like to enter 0 - followed by ENTER.</p><p>"
                                 "That calculates the coordinate offset for that axis and "
                                 "sends the value to linuxcnc backend</p>"));
     }
  }
