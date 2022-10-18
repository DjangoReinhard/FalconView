/* 
 * **************************************************************************
 * 
 *  file:       abscenterwidget.cpp
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
#include <abscenterwidget.h>
#include <configacc.h>
#include <guicore.h>
#include <QString>
#include <QFrame>
#include <QAction>
#include <QFile>
#include <QDebug>
#include <QKeyEvent>
#include <QUiLoader>
#include <QScrollArea>
#include <QStackedLayout>


/*! loads widgets from uiFile and allows late initialization at page usage
 */
AbstractCenterWidget::AbstractCenterWidget(const QString& fileName, QWidget* parent)
 : QWidget(parent)
 , core(nullptr)
 , cfg(nullptr)
 , vm(nullptr)
 , action(nullptr)
 , uiFileName(fileName)
 , addScrollArea(false) {
  }


/*! loads widgets from uiFile and allows late initialization at page usage
 */
AbstractCenterWidget::AbstractCenterWidget(const QString& fileName, bool adScrollArea, QWidget* parent)
 : QWidget(parent)
 , core(nullptr)
 , cfg(nullptr)
 , vm(nullptr)
 , action(nullptr)
 , uiFileName(fileName)
 , addScrollArea(adScrollArea) {
  }


void AbstractCenterWidget::closeEvent(QCloseEvent* e) {
  QWidget::closeEvent(e);
  }


QWidget* AbstractCenterWidget::createContent() {
  qDebug() << "ACW::createContent()";
  QWidget*  rv = nullptr;

  if (!fileName().isEmpty()) {
     QFile     uiDesc(fileName());

     if (!uiDesc.exists()) core->riseError(QString("invalid form-definition-file %1").arg(fileName()));
     QUiLoader loader;
     QWidget*  w = loader.load(&uiDesc, this);

     uiDesc.close();
//     qDebug() << "ACW: resource closed.";
     if (w) {
        if (addScrollArea) {
           QScrollArea* sa = new QScrollArea(this);

           sa->setWidget(w);
           sa->setWidgetResizable(true);
           rv = sa;
           }
        else rv = w;
        }
     }
  return rv;
  }


QString AbstractCenterWidget::fileName() const {
  return uiFileName;
  }


// offline initialization
void AbstractCenterWidget::initialize(const QString& name) {
  if (!core) {
     core = new GuiCore();
     cfg  = new Config();
     vm   = new ValueManager();
     }
  if (!name.isEmpty()) {
     setObjectName(name);
     setWindowTitle(tr(name.toStdString().c_str()));
     }
  QWidget* w = createContent();

  if (w) {
     setLayout(new QVBoxLayout);
     layout()->setContentsMargins(0, 0, 0, 0);
     layout()->addWidget(w);
     }
  connectSignals();
  updateStyles();
  layout()->invalidate();
  }


void AbstractCenterWidget::patch(void *pk, void *pc, void *pv, void*, bool) {
  core = new GuiCore(pk);
  cfg  = new Config(pc);
  vm   = new ValueManager(pv);

  qDebug() << "page:" << QWidget::objectName() << "ACW - core:" << core->kernel << "\tgiven:" << pk;
  }


QAction* AbstractCenterWidget::viewAction() {
  if (!action) {
     action = new QAction(this);

     action->setMenuRole(QAction::NoRole);
     action->setText(windowTitle());
     }
  return action;
  }


void AbstractCenterWidget::showEvent(QShowEvent* e) {
  QWidget::showEvent(e);
  if (e->type() == QEvent::Show) {
//     qDebug() << "ACW: check if help should be popped";
     if (cfg && cfg->value("showHelpAtPageChange").toBool()) {
//        qDebug() << "ACW: config says YES";
        if (core) {
//           qDebug() << "ACW: ask core for popping help";
           core->help4Keyword(QWidget::objectName());
           }
        }
     }
  }
