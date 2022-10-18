/* 
 * **************************************************************************
 * 
 *  file:       mdieditor.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    22.1.2022 by Django Reinhard
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
#include "mdieditor.h"
#include <applicationmode.h>
#include <configacc.h>
#include <guicore.h>
#include <dynaaction.h>
#include <andcondition.h>
#include <equalcondition.h>
#include <smallercondition.h>
#include <QListWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <QDebug>
#include <cmath>


MDIEditor::MDIEditor(QWidget* parent)
 : AbstractCenterWidget(":MDIEditor.ui", parent)
 , history(nullptr)
 , cmd(nullptr) {
  setObjectName("MDIEditor");
  setWindowTitle(tr("MDIEditor"));
  }


MDIEditor::~MDIEditor() {
  }


void MDIEditor::append(const QString &command) {
  int  mx    = history->count();
  bool found = false;

  for (int i = 0; i < mx; ++i) {
      if (history->item(i)->text() == command) {
         found = true;
         break;
         }
      }
  if (!found) history->addItem(command);
  cmd->clear();
  }


void MDIEditor::closeEvent(QCloseEvent*) {
  QStringList sl;
  int mx = history->count();

  for (int i = fmax(0, mx - 50); i < mx; ++i)
      sl.append(history->item(i)->text());

  cfg->beginGroup("MDIEditor");
  cfg->setValue("history", sl);
  cfg->endGroup();
  }


QString MDIEditor::command() const {
  return cmd->text().toUpper().replace(",", ".");
  }


QWidget* MDIEditor::createContent() {
  QWidget* rv = AbstractCenterWidget::createContent();

  history = rv->findChild<QListWidget*>("history");
  cmd     = rv->findChild<QLineEdit*>("command");
  history->installEventFilter(this);
  cmd->installEventFilter(this);
  cfg->beginGroup("MDIEditor");
  QStringList sl = cfg->value("history").toStringList();
  cfg->endGroup();

  for (const QString& s : sl) {
      qDebug() << "history command: " << s;

      history->addItem(s);
      }
  if (history->count() < 1) createTestData();

  return rv;
  }


void MDIEditor::createTestData() {
  for (int i=0; !testData[i].isEmpty(); ++i) {
      history->addItem(testData[i]);
      }
  }


void MDIEditor::connectSignals() {
  connect(history->selectionModel(), &QItemSelectionModel::currentChanged, this, &MDIEditor::currentChanged);
  }


void MDIEditor::currentChanged(const QModelIndex& current, const QModelIndex&) {
//  qDebug() << "currentChanged" << current;
  cmd->setText(history->item(current.row())->text());
  }


bool MDIEditor::eventFilter(QObject*, QEvent* event) {
  if (event->type() == QEvent::KeyPress) {
     QKeyEvent* e = static_cast<QKeyEvent*>(event);

     switch (e->key()) {
       case Qt::Key_Up:
            history->setCurrentRow(history->currentRow() > 0
                                 ? history->currentRow() - 1 : 0);
            return true;
       case Qt::Key_Down:
            history->setCurrentRow(history->currentRow() < (history->count() - 1)
                                 ? history->currentRow() + 1 : history->count() - 1);
            return true;
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            return true;
       }
     }
  return false;
  }


void MDIEditor::showEvent(QShowEvent* e) {
  if (e->type() == QEvent::Show) {
     cmd->setFocus();
     }
  AbstractCenterWidget::showEvent(e);
  }


void MDIEditor::updateStyles() {
  }


QAction* MDIEditor::viewAction() {
  if (!action) {
     action = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                           , QIcon(":SK_MDI.png")
                           , QIcon(":SK_MDI_active.png")
                           , tr("MDI-mode")
                           , (new AndCondition(new EqualCondition(vm->getModel("taskState"), GuiCore::taskStateOn)
                                             , new EqualCondition(vm->getModel("allHomed"), true)))
                                ->addCondition(new SmallerCondition(vm->getModel("execState"), GuiCore::taskWaiting4Motion))
                                ->addCondition(new EqualCondition(vm->getModel("errorActive"), false))
                           , new EqualCondition(vm->getModel("appMode"), ApplicationMode::MDI)
                           , this);

     }
  return action;
  }

const QString MDIEditor::testData[] = {
  "T1 M6"
, "S400 M3"
, "F100"
, "G21 G40 G80"
, "T3 M6"
, "T6 M6"
, "G0 G90 G54 X0 Y0"
, ""
  };
