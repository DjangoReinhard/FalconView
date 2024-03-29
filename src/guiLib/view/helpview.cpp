/* 
 * **************************************************************************
 * 
 *  file:       helpview.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    19.1.2022 by Django Reinhard
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
#include "helpview.h"
#include "helpbrowser.h"
#include <helpengine.h>
#include <helpcontentwidget.h>
#include <helpkeywordwidget.h>
#include <configacc.h>
#include <guicore.h>
#include <QSplitter>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QDebug>


HelpView::HelpView(QWidget* parent)
 : AbstractCenterWidget(QString(), parent)
 , tb(nullptr)
 , sp(nullptr)
 , he(nullptr)
 , cw(nullptr)
 , kw(nullptr) {
  setObjectName("HelpView");
  setWindowTitle(tr("HelpView"));
  setMinimumSize(800, 800);
  }


QWidget* HelpView::createContent() {
  tb = new HelpBrowser();
  sp = new QSplitter(Qt::Horizontal, this);
  qDebug() << "HelpEngine - helpfile is:" << core->fileName4("helpFile");
  he = new HelpEngine(core->fileName4("helpFile"), this);
  cw = static_cast<HelpContentWidget*>(he->contentWidget());
  kw = static_cast<HelpKeywordWidget*>(he->keywordWidget());
  HelpBrowser* hb = static_cast<HelpBrowser*>(tb);

  hb->setHelpEngine(he);
  tw = new QTabWidget(sp);
  sp->addWidget(tw);
  sp->addWidget(tb);
  tw->addTab(cw, tr("Content"));
  tw->addTab(kw, tr("Keywords"));
  setLayout(new QVBoxLayout());
  layout()->addWidget(sp);
  cw->expandAll();
  hb->installEventFilter(this);
  tw->installEventFilter(this);
  cw->installEventFilter(this);
  kw->installEventFilter(this);

  return nullptr;
  }


void HelpView::connectSignals() {
  connect(tw, &QTabWidget::currentChanged, this, &HelpView::tabChanged);
  connect(cw, &QTreeWidget::currentItemChanged, this, &HelpView::contentItemChanged);
  connect(kw, &QListWidget::currentItemChanged, this, &HelpView::keywordItemChanged);
  connect(tb, &QTextBrowser::sourceChanged, this, &HelpView::sourceChanged);
  }


void HelpView::updateStyles() {
  }


void HelpView::contentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *) {
  const QString& page = current->data(1, Qt::DisplayRole).toString();

  tb->setSource(page);
  }


void HelpView::tabChanged(int index) {
  qDebug() << "HelpView::tabChanged(" << index << ")";
  }


void HelpView::sourceChanged(const QUrl& src) {
  cw->sourceChanged(src);
  kw->sourceChanged(src);
  }


void HelpView::keywordItemChanged(QListWidgetItem *current, QListWidgetItem *) {
  const QString& page = current->toolTip();

  tb->setSource(page);
  }


void HelpView::help4Keyword(const QString &keyWord) {
  QString document = he->document4Keyword(keyWord);

//  qDebug() << "\tHD: keyword >" << keyWord << "< \tpage:" << document;
  if (!document.isEmpty()) tb->setSource(document);
  }


void HelpView::closeEvent(QCloseEvent*) {
  qDebug() << "HelpView::closeEvent ...";
  saveState();
  }


bool HelpView::eventFilter(QObject*, QEvent* event) {
  if (event->type() == QEvent::KeyPress) {
     QKeyEvent* e = static_cast<QKeyEvent*>(event);

     switch (e->key()) {
       case Qt::Key_Escape:
            //TODO: switch back
            break;
       }
     }
  return false;
  }


void HelpView::restoreState() {
  cfg->beginGroup("HelpView");
  sp->restoreState(cfg->value("state").toByteArray());
  cw->setFocus();
  }


void HelpView::saveState() {
  cfg->beginGroup("HelpView");
  cfg->setValue("state", sp->saveState());
  }
