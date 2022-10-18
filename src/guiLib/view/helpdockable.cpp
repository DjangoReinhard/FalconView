/* 
 * **************************************************************************
 * 
 *  file:       helpdockable.cpp
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
#include "helpdockable.h"
#include "helpview.h"
#include <ui_HelpTitle.h>
#include <configacc.h>
#include <QMouseEvent>
#include <QDebug>


HelpDockable::HelpDockable(HelpView* view, QWidget* parent)
 : QDockWidget(tr("Help"), parent)
 , hv(view) {
  setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
  setTitleBarWidget(new HelpTitleBar(this));
  qDebug() << "0) HelpView->parent:" << view->parentWidget();
  layout()->setContentsMargins(0, 0, 0, 0);
  this->setWidget(hv);
  qDebug() << "1) HelpView->parent:" << view->parentWidget();
  this->hide();
  }


void HelpDockable::help4Keyword(const QString &keyWord) {
  hv->help4Keyword(keyWord);
  showHelp();
  }


void HelpDockable::showHelp() {
  if (!isFloating()) setFloating(true);
  QDockWidget::show();
  raise();
  activateWindow();
  Config cfg;

  hv->restoreState();
  restoreGeometry(cfg.value("geometry").toByteArray());
  cfg.endGroup();
  }


void HelpDockable::closeEvent(QCloseEvent* e) {
  if (hv) hv->closeEvent(e);
  Config cfg;

  cfg.setValue("geometry", saveGeometry());
  cfg.endGroup();
  }


void HelpDockable::keyPressEvent(QKeyEvent* e) {
//  qDebug() << "HelpDLG: pressed key: " << e->key()
//           << "modifiers: "   << e->modifiers()
//           << "event-ts: " << e->timestamp();
  switch (e->key()) {
    case Qt::Key_Escape:
         close();
         break;
    case Qt::Key_Right:
    case Qt::Key_Left:
    case Qt::Key_Up:
    case Qt::Key_Down:
         break;
    default:
         QDockWidget::keyPressEvent(e);
         break;
    }
  }


#ifdef REDNOSE
void HelpDockable::contentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *) {
  const QString& page = current->data(1, Qt::DisplayRole).toString();

  tb->setSource(page);
  }


void HelpDockable::tabChanged(int index) {
  qDebug() << "HelpDialog::tabChanged(" << index << ")";
  }


void HelpDockable::sourceChanged(const QUrl& src) {
  HelpTitleBar* htb = static_cast<HelpTitleBar*>(this->titleBarWidget());
//  int           index = tw->currentIndex();

//  qDebug() << "HelpDialog::sourceChanged - #" << index
//           << ":" << tb->documentTitle()
//           << " - src:" << src;

  cw->sourceChanged(src);
  kw->sourceChanged(src);
  if (htb) htb->setTitle(tb->documentTitle());
  }


void HelpDockable::keywordItemChanged(QListWidgetItem *current, QListWidgetItem *) {
  const QString& page = current->toolTip();

  tb->setSource(page);
  }


void HelpDockable::closeEvent(QCloseEvent*) {
  Config cfg;

  cfg.beginGroup(HelpDockable::className);
  cfg.setValue("state", sp->saveState());
  cfg.setValue("geometry", saveGeometry());
  cfg.endGroup();
  }


void HelpDockable::showHelp() {
  if (!isFloating()) setFloating(true);
  QDockWidget::show();  
  Config cfg;

  cfg.beginGroup(HelpDockable::className);
  sp->restoreState(cfg.value("state").toByteArray());
  restoreGeometry(cfg.value("geometry").toByteArray());
  cfg.endGroup();
  raise();
  activateWindow();
  cw->setFocus();
  }
#endif

HelpTitleBar::HelpTitleBar(QWidget *parent)
 : QWidget(parent)
 , titleBar(new Ui::HelpTitle) {
  titleBar->setupUi(this);
  layout()->setContentsMargins(0, 0, 0, 0);
  setStyleSheet("background: #4D565E;");
  }


QSize HelpTitleBar::minimumSizeHint() const {
  return QSize(300, 40);
  }


void HelpTitleBar::setTitle(const QString &title) {
//  qDebug() << "Help - Titlebar::setTitle(" << title << ")";
  this->titleBar->title->setText(title);
  }


void HelpTitleBar::mouseReleaseEvent(QMouseEvent* e) {
  QPoint       pos  = e->pos();
  QRect        rect = this->rect();
  QDockWidget* dw   = qobject_cast<QDockWidget*>(parentWidget());
  Q_ASSERT(dw);

  const int buttonRight = 5;
  const int buttonWidth = 32;
  int right  = rect.right() - pos.x();
  int button = (right - buttonRight)/buttonWidth;

  switch (button) {
    case 0:
         e->accept();
         dw->close();
         break;
    default:
         e->ignore();
         break;
    }
  }
