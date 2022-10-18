/* 
 * **************************************************************************
 * 
 *  file:       fixturemanager.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    10.1.2022 by Django Reinhard
 *  copyright:  (c) 2022 Django Reinhard -  all rights reserved
 * 
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 2 of the License, or 
 *  (at your option) any later version. 
 *   
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details. 
 *   
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * **************************************************************************
 */
#include "fixturemanager.h"
#include "fixtureedit.h"
#include <flowlayout.h>
#include <valuemanager.h>
#include <configacc.h>
#include <guicore.h>
#include <axismask.h>
#include <QMessageBox>
#include <QScrollArea>
#include <QShowEvent>
#include <QDebug>


FixtureManager::FixtureManager(QWidget* parent)
 : AbstractCenterWidget(QString(), parent)
 , client(new QWidget(this))
 , axisMask(nullptr) {
  setObjectName("FixtureManager");
  setWindowTitle(tr("FixtureManager"));
  }


void FixtureManager::activateEditor(int n) {
  QLayout* l = client->layout();
  int      mx = l->count();

  if (n < 0)   n = 0;
  if (n >= mx) n = mx - 1;
  qDebug() << "FM::activateEditor(" << n << ")";
  for (int i=0; i < mx; ++i) {
      FixtureEdit* fe = static_cast<FixtureEdit*>(l->itemAt(i)->widget());

      if (fe) {
         fe->setEnabled(i == n, cFonts, cStyle);
         }
      }
  QScrollArea* sa = static_cast<QScrollArea*>(layout()->itemAt(0)->widget());

  if (sa) sa->ensureWidgetVisible(l->itemAt(n)->widget());
  }


QWidget* FixtureManager::createContent() {
  axisMask = new AxisMask(core->axisMask());
  FlowLayout*  fl = new FlowLayout(client);
  QScrollArea* sa = new QScrollArea(this);  
  FixtureEdit* fe = new FixtureEdit(tr("Offsets"), 0, *axisMask);

  client->setLayout(fl);
  fe->initialize("Offsets");
  fl->setContentsMargins(0, 0, 0, 0);
  fl->addWidget(fe);
  for (int i=0; i < 9; ++i) {
      if (i < 6) {
         QString id = QString("G%1").arg(54 + i);

         fe = new FixtureEdit(id, i+1, *axisMask);
         fe->initialize(id);
         }
      else {
         QString id = QString("G59.%1").arg(i - 5);

         fe = new FixtureEdit(id, i+1, *axisMask);
         fe->initialize(id);
         }
      fl->addWidget(fe);
      }
  sa->setWidgetResizable(true);
  client->setObjectName("client");
  sa->setWidget(client);

  return sa;
  }


void FixtureManager::connectSignals() {
  }



void FixtureManager::updateStyles() {
  QColor       colBg = vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::FixTitle)).value<QColor>();
  QColor       colFg = vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::FixTitle)).value<QColor>();

  cFonts[0] = vm->getValue("cfgF"  + cfg->nameOf(Config::GuiElem::FixTitle)).value<QFont>();
  cStyle[0] = QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16);

  colBg = vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::FixDisabledTitle)).value<QColor>();
  colFg = vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::FixDisabledTitle)).value<QColor>();
  cFonts[1] = vm->getValue("cfgF"  + cfg->nameOf(Config::GuiElem::FixDisabledTitle)).value<QFont>();
  cStyle[1] = QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16);

  colBg = vm->getValue("cfgBg" + cfg->nameOf(Config::GuiElem::FixPrompt)).value<QColor>();
  colFg = vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::FixPrompt)).value<QColor>();
  cFonts[2] = vm->getValue("cfgF"  + cfg->nameOf(Config::GuiElem::FixPrompt)).value<QFont>();
  cStyle[2] = QString("color: #%1; background: #%2;").arg(colFg.rgb(), 0, 16).arg(colBg.rgba(), 0, 16);

  colFg = vm->getValue("cfgFg" + cfg->nameOf(Config::GuiElem::FixEdit)).value<QColor>();
  cFonts[3] = vm->getValue("cfgF"  + cfg->nameOf(Config::GuiElem::FixEdit)).value<QFont>();
  cStyle[3] = QString("color: #%1;").arg(colFg.rgb(), 0, 16);
  activateEditor(0);
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
         [[fallthrough]];
    default: {
         qDebug() << "FM: pressed key: " << e->key()
                  << "modifiers: " << e->modifiers()
                  << "event->ts: " << e->timestamp();
         AbstractCenterWidget::keyPressEvent(e);
         } break;
    }
}


//void FixtureManager::resizeEvent(QResizeEvent *e) {
//  qDebug() << "resize from:" << e->oldSize() << "\tto" << e->size();
//  AbstractCenterWidget::resizeEvent(e);
//  }


void FixtureManager::showEvent(QShowEvent* e) {
  AbstractCenterWidget::showEvent(e);
  qDebug() << "FM: show Event ...";
  if (e->type() == QEvent::Show) {
     activateEditor(0);
//     QMessageBox::information(this
//                            , tr("QMessageBox::information()")
//                            , tr("<p>Fixture-Manager helps you manage your individual "
//                                 "coordinate system offsets.</p><p>Use CTRL+number to activate "
//                                 "an editor. G54 is CTRL+1, G55 is CTRL+2 and CTRL+0 "
//                                 "activates the relative offsets.</p><p>TAB / BackTAB can be"
//                                 "used to select the axis. In an axis field, just enter the "
//                                 "value you'd like to see at the current postion.</p><p>"
//                                 "Usually you'd like to enter 0 - followed by ENTER.</p><p>"
//                                 "That calculates the coordinate offset for that axis and "
//                                 "sends the value to linuxcnc backend</p>"));
     }
  }
