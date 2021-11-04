#include <fixtureedit.h>
#include <valuemanager.h>
#include <canonif.h>
#include <KeyCodes.h>
#include <QKeyEvent>
#include <QLineEdit>
#include <QLabel>
#include <QLayout>
#include <QDebug>


FixtureEdit::FixtureEdit(const QString& title, QWidget* parent)
 : DynWidget(QString(), parent)
 , ui(new Ui::frame()) {
  this->ui->setupUi(this);
  this->ui->title->setText(title);
  layout()->setContentsMargins(0, 0, 0, 0);
  }


void FixtureEdit::connectSignals() {
  }


void FixtureEdit::updateStyles() {
  }

const char axisLetters[] = "XYZABCUVW";

void FixtureEdit::keyReleaseEvent(QKeyEvent *e) {
  qDebug() << "released key: " << e->key();

  if (e->key() == KeyCodes::Enter || e->key() == KeyCodes::NB_Enter) {
     qDebug() << "Enter pressed at" << ui->title->text();
     QString userData;
     bool    ok   = false;
     int     axis = -1;

     for (int i=0; i < 9; ++i) {
         switch (i) {
           case 0: if (ui->edX->hasFocus()) { axis = i; userData = ui->edX->text(); } break;
           case 1: if (ui->edY->hasFocus()) { axis = i; userData = ui->edY->text(); } break;
           case 2: if (ui->edZ->hasFocus()) { axis = i; userData = ui->edZ->text(); } break;
           case 3: if (ui->edA->hasFocus()) { axis = i; userData = ui->edA->text(); } break;
           case 4: if (ui->edB->hasFocus()) { axis = i; userData = ui->edB->text(); } break;
           case 5: if (ui->edC->hasFocus()) { axis = i; userData = ui->edC->text(); } break;
           case 6: if (ui->edU->hasFocus()) { axis = i; userData = ui->edU->text(); } break;
           case 7: if (ui->edV->hasFocus()) { axis = i; userData = ui->edV->text(); } break;
           case 8: if (ui->edW->hasFocus()) { axis = i; userData = ui->edW->text(); } break;
           }
         }
     userData.replace(",", ".");
     double dv = userData.toDouble(&ok);

     if (ok) {
        CANON_POSITION to = CanonIF().toolOffset();
        double curPos;

        switch (axis) {
          case 0: {
               curPos = ValueManager().getValue("absX").toDouble();
               qDebug() << "FixEd: curPos (X)" << curPos;
               curPos -= to.x;
               qDebug() << "FixEd: applied tool offset: " << curPos;
               } break;
          case 1: {
               curPos = ValueManager().getValue("absY").toDouble();
               qDebug() << "FixEd: curPos (Y)" << curPos;
               curPos -= to.y;
               qDebug() << "FixEd: applied tool offset: " << curPos;
               } break;
          case 2: {
               curPos = ValueManager().getValue("absZ").toDouble();
               qDebug() << "FixEd: curPos (Z)" << curPos;
               curPos -= to.z;
               qDebug() << "FixEd: applied tool offset: " << curPos;
               } break;
          case 3: {
               curPos = ValueManager().getValue("absA").toDouble();
               qDebug() << "FixEd: curPos (A)" << curPos;
               curPos -= to.a;
               qDebug() << "FixEd: applied tool offset: " << curPos;
               } break;
          case 4: {
               curPos = ValueManager().getValue("absB").toDouble();
               qDebug() << "FixEd: curPos (B)" << curPos;
               curPos -= to.b;
               qDebug() << "FixEd: applied tool offset: " << curPos;
               } break;
          case 5: {
               curPos = ValueManager().getValue("absC").toDouble();
               qDebug() << "FixEd: curPos (C)" << curPos;
               curPos -= to.c;
               qDebug() << "FixEd: applied tool offset: " << curPos;
               } break;
          case 6: {
               curPos = ValueManager().getValue("absU").toDouble();
               qDebug() << "FixEd: curPos (U)" << curPos;
               curPos -= to.u;
               qDebug() << "FixEd: applied tool offset: " << curPos;
               } break;
          case 7: {
               curPos = ValueManager().getValue("absV").toDouble();
               qDebug() << "FixEd: curPos (V)" << curPos;
               curPos -= to.v;
               qDebug() << "FixEd: applied tool offset: " << curPos;
               } break;
          case 8: {
               curPos = ValueManager().getValue("absw").toDouble();
               qDebug() << "FixEd: curPos (W)" << curPos;
               curPos -= to.w;
               qDebug() << "FixEd: applied tool offset: " << curPos;
               } break;
          }
        curPos -= dv;
        qDebug() << "FixEd: change fixture on" << ui->title->text()
                 << "axis " << axisLetters[axis] << "to user entry:" << dv
                 << "calculated machine pos: " << curPos;
        }
     }
  }
