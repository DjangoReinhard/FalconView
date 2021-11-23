#include <fixturemanager.h>
#include <flowlayout.h>
#include <fixtureedit.h>
#include <QScrollArea>
#include <QShowEvent>
#include <QDebug>


FixtureManager::FixtureManager(const AxisMask& mask, QWidget* parent)
 : DynCenterWidget(QString(), "FixtureManager", false, parent)
 , client(new QWidget(this))
 , axisMask(mask) {
  setObjectName(tr("FixtureManager"));
  }


QWidget* FixtureManager::createContent() {
  FlowLayout*  fl = new FlowLayout;
  QScrollArea* sa = new QScrollArea;
  FixtureEdit* fe = new FixtureEdit(tr("Offsets"), axisMask);

  client->setLayout(fl);
  fe->setEnabled(false);
  fl->setContentsMargins(0, 0, 0, 0);
  fl->addWidget(fe);
  for (int i=0; i < 9; ++i) {
      if (i < 6) fe = new FixtureEdit(QString("G%1").arg(54 + i), axisMask);
      else       fe = new FixtureEdit(QString("G59.%1").arg(i - 5), axisMask);
      fe->setEnabled(false);
      fl->addWidget(fe);
      }
  sa->setWidgetResizable(true);
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
  }


void FixtureManager::keyReleaseEvent(QKeyEvent* e) {
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
            }
         else DynCenterWidget::keyReleaseEvent(e);
         break;
    default:
         qDebug() << "FM: released key: " << e->key();
         qDebug() << "FM: modifiers: "    << e->modifiers();
         DynCenterWidget::keyReleaseEvent(e);
         break;
    }
  }


void FixtureManager::resizeEvent(QResizeEvent *e) {
  qDebug() << "resize from:" << e->oldSize() << "\tto" << e->size();
  DynCenterWidget::resizeEvent(e);
  }


void FixtureManager::showEvent(QShowEvent* e) {
  DynCenterWidget::showEvent(e);
  qDebug() << "FM: show Event ...";
  if (e->type() == QEvent::Show) activateEditor(0);
  }
