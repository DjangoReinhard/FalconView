/* 
 * **************************************************************************
 * 
 *  file:       pagestack.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    30.1.2022 by Django Reinhard
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
#include <pagestack.h>
#include <centerpage.h>
#include <abscenterwidget.h>
#include <valuemanager.h>
#include <guicore.h>
#include <QAction>
#include <QStackedLayout>
#include <QDebug>


PageStack::PageStack(QWidget* parent)
 : AbstractCenterWidget(QString(), parent) {
  setObjectName(tr("PageStack"));
  setLayout(new QStackedLayout);
  layout()->setContentsMargins(0, 0, 0, 0);
  }


QWidget* PageStack::createContent() {
  return nullptr;
  }


void PageStack::connectSignals() {
  }


void PageStack::updateStyles() {
  }


CenterPage* PageStack::page(const QString& name) {
  qDebug() << "CenterView: requested page \"" << name << "\"";

  if (pagePool.contains(name)) return pagePool[name];
  qDebug() << "CenterView: sorry - no page with name >" << name << "<";
  dump();

  return nullptr;
  }


CenterPage* PageStack::activatePage(const QString& name) {
  qDebug() << "CenterView: activatePage \""  << name << "\"";

  if (pagePool.contains(name)) {
     CenterPage*     w = pagePool[name];
     QStackedLayout* l = qobject_cast<QStackedLayout*>(layout());

     if (l && w) {
        qDebug() << "CenterView: ok, found page [" << name << "] - gonna switch view";
        l->setCurrentWidget(w);
        vm->setValue("lastPage", curPage);
        curPage = name;
        GuiCore().setWindowTitle(w->name().toStdString().c_str());

        return w;
        }
     }
  qDebug() << "CenterView: sorry - no page for name >" << name << "<";
  dump();

  return nullptr;
  }


QString PageStack::activePage() const {
  return curPage;
  }


void PageStack::dump() const {
  qDebug() << "CenterView contains" << pagePool.size() << " pages";
  for (auto e = pagePool.constKeyValueBegin(); e != pagePool.constKeyValueEnd(); e++) {
      qDebug() << "MainView holds page >>" << e->first;
      }
  }


void PageStack::addPage(CenterPage* page, const QString& name) {
  QString pageName(name);

  if (pageName.isEmpty()) pageName = page->objectName();
  pagePool.insert(pageName, page);
  QStackedLayout* l = qobject_cast<QStackedLayout*>(layout());

  if (l) {
     l->addWidget(page);
     connect(page->viewAction(), &QAction::triggered, this, [=]() {
       GuiCore().activatePage(page->objectName());
       });
     }
  activatePage(pageName);
  }


QList<QString> PageStack::pages() const {
  return pagePool.keys();
  }


void PageStack::windowClosing(QCloseEvent* e) {
  for (auto t = pagePool.constKeyValueBegin(); t != pagePool.constKeyValueEnd(); t++) {
      t->second->closeEvent(e);
      }
  }


QAction* PageStack::viewAction() {
  if (!action) action = new QAction();
  return action;
  }
