#include <fixturemanager.h>
#include <flowlayout.h>
#include <fixtureedit.h>
#include <QScrollArea>
#include <QShowEvent>
#include <QDebug>


FixtureManager::FixtureManager(const QString& fileName, QWidget* parent)
 : DynWidget(parent)
 , client(nullptr) {
  setObjectName(tr("FixtureManager"));
  setLayout(new QVBoxLayout);
  QScrollArea* sa = new QScrollArea;
  QLayout*     fl = new FlowLayout;

#ifdef REDNOSE
  client = new QWidget();
  client->setLayout(fl);
  for (int i=0; i < 9; ++i) {
      if (i < 7) fl->addWidget(new FixtureEdit(QString("G%1").arg(53 + i), fileName));
      else       fl->addWidget(new FixtureEdit(QString("G59.%1").arg(i - 6), fileName));
      }
  sa->setWidget(client);
#else
  sa->setLayout(fl);
  client = sa;
  for (int i=0; i < 9; ++i) {
      if (i < 7) fl->addWidget(new FixtureEdit(QString("G%1").arg(53 + i), fileName));
      else       fl->addWidget(new FixtureEdit(QString("G59.%1").arg(i - 6), fileName));
      }
#endif
  this->layout()->addWidget(sa);
  this->layout()->setContentsMargins(0, 0, 0, 0);
  }


void FixtureManager::connectSignals() {
  }


void FixtureManager::updateStyles() {
  }


void FixtureManager::resizeEvent(QResizeEvent *e) {
  qDebug() << "resize from:" << e->oldSize() << "\tto" << e->size();
  DynWidget::resizeEvent(e);
  }


void FixtureManager::showEvent(QShowEvent* e) {
  DynWidget::showEvent(e);

  qDebug() << "\tfixtureManager has size: " << this->size();

  QLayout* l = client->layout();
  QWidget* w;

  for (int i=0; i < 9; ++i) {
      w = l->itemAt(i)->widget();
      qDebug() << "\t\tchild #" << i << "has size: " << w->size();
      }
  }
