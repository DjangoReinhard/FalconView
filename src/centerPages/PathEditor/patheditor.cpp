/* 
 * **************************************************************************
 * 
 *  file:       patheditor.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    28.1.2022 by Django Reinhard
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
#include "patheditor.h"
#include <valuemanager.h>
#include <dynaaction.h>
#include <andcondition.h>
#include <equalcondition.h>
#include <smallercondition.h>
#include <guicore.h>
#include <gcodeeditor.h>
#include <gcodehighlighter.h>
#include <QSplitter>
#include <QFileDialog>
#include <QLabel>
#include <QDir>
#include <QDebug>
#include <QVariant>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QPushButton>


PathEditor::PathEditor(QWidget* parent)
 : TestEdit() {
  if (parent) setParent(parent);
  setObjectName("PathEditor");
  setWindowTitle(tr("PathEditor"));
  }


void PathEditor::closeEvent(QCloseEvent* e) {
  QWidget::closeEvent(e);
  }


void PathEditor::connectSignals() {
  connect(vm->getModel("fileName", " "), &ValueModel::valueChanged, this, &PathEditor::reallyLoadFile);
  TestEdit::connectSignals();
  connect(ed, &GCodeEditor::cursorPositionChanged, this, [=](){
    ValueModel* m = vm->getModel("edLine");

    qDebug() << "PE: address of <edLine>" << m;

//    vm->setValue("edLine", ed->textCursor().block().blockNumber());
    m->setValue(ed->textCursor().block().blockNumber());
    });
  }


// called from TestEdit::fileSelected
void PathEditor::loadFile(const QVariant& fileName) {
  if (core->checkBE()) {
     qDebug() << "PathEditor::loadFile (backend active)" << fileName;
     core->beLoadTaskPlan(fileName.toString());
     }
  else vm->setValue("fileName", fileName);
  }


QWidget* PathEditor::createContent() {
  return TestEdit::createContent();
  }


void PathEditor::updateStyles() {
  TestEdit::updateStyles();
  }


void PathEditor::dirtyChanged(bool dirty) {
  vm->setValue("gcodeDirty", dirty);
  TestEdit::dirtyChanged(dirty);
  }


void PathEditor::reallyLoadFile(const QVariant& fileName) {
  TestEdit::reallyLoadFile(fileName);
  core->setAppMode(ApplicationMode::Edit);
  }


void PathEditor::fileUpdated(const QString& fileName) {
  //TODO: ask backend to reload file
  qDebug() << "PathEdit: file" << fileName << "has been changed - need to trigger backend!";
  }


void PathEditor::showEvent(QShowEvent* e) {
  QWidget::showEvent(e);
  }


QAction* PathEditor::viewAction() {
  if (!action) {
     action = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                           , QIcon(":SK_Edit.png")
                           , QIcon(":SK_Edit_active.png")
                           , tr("Edit-mode")
                           , (new AndCondition(new EqualCondition(vm->getModel("taskState"), GuiCore::taskStateOn)
                                             , new SmallerCondition(vm->getModel("execState"), GuiCore::taskWaiting4Motion)))
                                ->addCondition(new EqualCondition(vm->getModel("errorActive"), false))
                           , new EqualCondition(vm->getModel("appMode"), ApplicationMode::Edit)
                           , this);
     }
  return action;
  }
