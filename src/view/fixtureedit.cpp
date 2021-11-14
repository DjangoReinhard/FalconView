#include <fixtureedit.h>
#include <valuemanager.h>
#include <canonif.h>
#include <QKeyEvent>
#include <QLineEdit>
#include <QLabel>
#include <QLayout>
#include <QDebug>


FixtureEdit::FixtureEdit(const QString& title, const AxisMask& mask, QWidget* parent)
 : DynWidget(QString(), parent)
 , ui(new Ui::frame())
 , m(mask) {
  setupUi(this);
  ui->title->setText(title);
  layout()->setContentsMargins(0, 0, 0, 0);
  }


void FixtureEdit::changeEvent(QEvent* e) {
  DynWidget::changeEvent(e);
  qDebug() << "changeEvent(" << e->type() << ")";

  if (e->type() == QEvent::EnabledChange) {
     for (int i=0; i < 9; ++i)
         if (edits.at(i)->isVisible()) {
            ui->edX->setFocus();
            break;
            }
     }
  }


void FixtureEdit::focusInEvent(QFocusEvent* e) {
  DynWidget::focusOutEvent(e);
  qDebug() << "FE: focus in Event";
  }


void FixtureEdit::focusOutEvent(QFocusEvent* e) {
  DynWidget::focusOutEvent(e);
  qDebug() << "FE:: focus out Event";
  }


void FixtureEdit::connectSignals() {
  }


void FixtureEdit::updateStyles() {
  }


void FixtureEdit::setupUi(DynWidget* parent) {
  ui->setupUi(parent);
  ui->lX->setVisible(m.hasXAxis());
  ui->lY->setVisible(m.hasYAxis());
  ui->lZ->setVisible(m.hasZAxis());
  ui->lA->setVisible(m.hasAAxis());
  ui->lB->setVisible(m.hasBAxis());
  ui->lC->setVisible(m.hasCAxis());
  ui->lU->setVisible(m.hasUAxis());
  ui->lV->setVisible(m.hasVAxis());
  ui->lW->setVisible(m.hasWAxis());
  ui->edX->setVisible(m.hasXAxis());
  ui->edY->setVisible(m.hasYAxis());
  ui->edZ->setVisible(m.hasZAxis());
  ui->edA->setVisible(m.hasAAxis());
  ui->edB->setVisible(m.hasBAxis());
  ui->edC->setVisible(m.hasCAxis());
  ui->edU->setVisible(m.hasUAxis());
  ui->edV->setVisible(m.hasVAxis());
  ui->edW->setVisible(m.hasWAxis());
  edits.append(ui->edX);
  edits.append(ui->edY);
  edits.append(ui->edZ);
  edits.append(ui->edA);
  edits.append(ui->edB);
  edits.append(ui->edC);
  edits.append(ui->edU);
  edits.append(ui->edV);
  edits.append(ui->edW);
  int start = -1, first = 0, second = 1, mx = edits.size() - 1;

  do {
     while (first < mx) {
           if (m.hasAxis(first)) break;
           ++first;
           }
     second = first + 1;
     while (second < mx) {
           if (m.hasAxis(second)) break;
           ++second;
           }
//     qDebug() << "set taborder" << first << "->" << second;
     QWidget::setTabOrder(edits.at(first), edits.at(second));
     if (start < 0) start = first;
     first = second;
     } while (first < mx);
//  qDebug() << "set taborder" << second << "->" << start;
//  QWidget::setTabOrder(edits.at(second), edits.at(start));
  }

const char axisLetters[] = "XYZABCUVW";


void FixtureEdit::keyReleaseEvent(QKeyEvent* e) {
  switch (e->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
         saveFixture();
         e->accept();
         break;
    default:
         qDebug() << "FE: released key: " << e->key();
         qDebug() << "FE: modifiers: "    << e->modifiers();
         DynWidget::keyReleaseEvent(e);
         break;
    }
}


void FixtureEdit::saveFixture() {
  qDebug() << "Enter pressed at" << ui->title->text();
  QString userData;
  bool    ok   = false;
  int     axis = -1;

  for (int i=0; i < 9; ++i) {
      if (edits.at(i)->hasFocus()) {
         userData = edits.at(i)->text();
         break;
         }
      }
  userData.replace(",", ".");
  double dv = userData.toDouble(&ok);

  if (ok) {
     CANON_POSITION to     = CanonIF().toolOffset();
     double         curPos = 0;

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
     //TODO: send command
     }
  }
