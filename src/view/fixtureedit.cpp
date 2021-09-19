#include <fixtureedit.h>
#include <QPushButton>
#include <QLabel>
#include <QDebug>


FixtureEdit::FixtureEdit(const QString& title, const QString& fileName, QWidget* parent)
 : DynWidget(fileName, parent, 4) {
  QLabel* lt = w->findChild<QLabel*>("title");

  lt->setText(title);
  qDebug() << "fixtureEdit has size: " << this->size();
  }


void FixtureEdit::connectSignals() {
  QPushButton* pbTake = w->findChild<QPushButton*>("pbTake");
  QPushButton* pbSet  = w->findChild<QPushButton*>("pbSet");
  }


void FixtureEdit::updateStyles() {
  }
