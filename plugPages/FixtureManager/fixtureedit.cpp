#include <fixtureedit.h>
#include <valuemanager.h>
#include <canonif.h>
#include <axismask.h>
#include <configacc.h>
#include <QKeyEvent>
#include <QLineEdit>
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <canon_position.hh>


FixtureEdit::FixtureEdit(const QString& title, int ordinal, const AxisMask& mask, QWidget* parent)
 : AbstractCenterWidget(QString(), "FixtureEdit", false, parent)
 , ui(new Ui::FixtureEditorForm())
 , ordinal(ordinal)
 , m(mask) {
  setupUi(this);
  ui->title->setText(title);
  layout()->setContentsMargins(0, 0, 0, 0);
  }


bool FixtureEdit::focusNextPrevChild(bool next) {
  QWidget* w = focusWidget();

  if (w != QApplication::focusWidget()) return false;
  int i;
  int mx = edits.size();

  // find focus widget in edits
  for (i=0; i < mx; ++i) if (edits.at(i) == w) break;

  if (next) {
     do {
        if (++i >= mx) i=0;
        } while (edits.at(i)->focusPolicy() == Qt::FocusPolicy::NoFocus
             || !edits.at(i)->isVisible());
     edits.at(i)->setFocus(Qt::TabFocusReason);
     }
  else {
     do {
        if (--i < 0) i = mx - 1;
        } while (edits.at(i)->focusPolicy() == Qt::FocusPolicy::NoFocus
             || !edits.at(i)->isVisible());
     edits.at(i)->setFocus(Qt::BacktabFocusReason);
     }
  return true;
  }


QWidget* FixtureEdit::createContent() {
  return nullptr;
  }


void FixtureEdit::connectSignals() {
  }


void FixtureEdit::updateStyles() {
  // we get styled by parent ;)
  }


void FixtureEdit::setEnabled(bool enable, QFont* f, QString* ss) {
  ui->title->setEnabled(enable);
  if (enable) {
     ui->title->setFont(f[0]);
     ui->title->setStyleSheet(ss[0]);
     }
  else {
     ui->title->setFont(f[1]);
     ui->title->setStyleSheet(ss[1]);
     }
  ui->lX->setFont(f[2]);
  ui->lX->setStyleSheet(ss[2]);
  ui->lY->setFont(f[2]);
  ui->lY->setStyleSheet(ss[2]);
  ui->lZ->setFont(f[2]);
  ui->lZ->setStyleSheet(ss[2]);
  ui->lA->setFont(f[2]);
  ui->lA->setStyleSheet(ss[2]);
  ui->lB->setFont(f[2]);
  ui->lB->setStyleSheet(ss[2]);
  ui->lC->setFont(f[2]);
  ui->lC->setStyleSheet(ss[2]);
  ui->lU->setFont(f[2]);
  ui->lU->setStyleSheet(ss[2]);
  ui->lV->setFont(f[2]);
  ui->lV->setStyleSheet(ss[2]);
  ui->lW->setFont(f[2]);
  ui->lW->setStyleSheet(ss[2]);

  for (int i=0; i < 9; ++i) {
      edits[i]->setFont(f[3]);
      edits[i]->setStyleSheet(ss[3]);
      edits[i]->setEnabled(enable);
      }
  if (enable) {
     for (int i=0; i < 9; ++i) {
         if (edits[i]->isVisible()) {
            edits[i]->setFocus();
            edits[i]->selectAll();
            break;
            }
         }
     }
  }


void FixtureEdit::setupUi(AbstractCenterWidget* parent) {
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
  for (int i=0; i < 9; ++i)
      edits[i]->installEventFilter(this);
  }

const char axisLetters[] = "XYZABCUVW";


bool FixtureEdit::eventFilter(QObject *, QEvent *event) {
  if (event->type() == QEvent::KeyPress) {
     QKeyEvent* e = static_cast<QKeyEvent*>(event);

     if (!e) return false;
     switch (e->key()) {
       case Qt::Key_Enter:
       case Qt::Key_Return:
            saveFixture();

            return true;
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
            if (e->modifiers() == Qt::AltModifier) {
               qDebug() << "FE::filter - numberkey pressed: " << e->key()
                        << "modifiers: " << e->modifiers()
                        << "ts: " << e->timestamp();
               AbstractCenterWidget::keyPressEvent(e);
               return true;
               }
       default: break;
       }
     }
  return false;
  }


//void FixtureEdit::keyReleaseEvent(QKeyEvent* e) {
//  switch (e->key()) {
//    case Qt::Key_Enter:
//    case Qt::Key_Return:
//         saveFixture();
//         e->accept();
//         break;
//    default:
//         qDebug() << "FE: pressed key: " << e->key();
//         qDebug() << "FE: modifiers: "   << e->modifiers();
//         AbstractCenterWidget::keyReleaseEvent(e);
//         break;
//    }
//}


void FixtureEdit::saveFixture() {
  qDebug() << "Enter pressed at" << ui->title->text();
  QString userData;
  bool    ok   = false;
  int     axis = -1;

  for (int i=0; i < 9; ++i) {
      if (edits.at(i)->hasFocus()) {
         userData = edits.at(i)->text();
         qDebug() << "userData: >" << userData << "< on field #" << i;
         axis = i;
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
     qDebug() << "FixEd: change fixture on" << ui->title->text() << "<" << ordinal
              << "> - axis " << axisLetters[axis] << "to user entry:" << dv
              << "calculated machine pos: " << curPos;
     //TODO: send command (ordinal > 0)
     // MDI-command:     G10 L2 P{ordinal} axisLetters[axis] curPos

     //TODO: check command to use for offset settings (ordinal == 0)
     }
  }
