/* 
 * **************************************************************************
 * 
 *  file:       helpcontentwidget.cpp
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
#include <helpcontentwidget.h>
#include <QDomDocument>
#include <QHeaderView>
#include <QUrl>
//#include <QDebug>


HelpContentWidget::HelpContentWidget(QWidget* parent)
 : QTreeWidget(parent) {
  header()->setStretchLastSection(true);
  setHeaderLabel(tr("Title"));
  }


HelpContentWidget::~HelpContentWidget() {
  }


void HelpContentWidget::parse(const QByteArray& ba, QMap<QString, QString>& pages) {
  QDomDocument doc;

  doc.setContent(ba);
  QDomNodeList links = doc.elementsByTagName("toc");

  level = 0;
  clear();
  for (int i=0; i < links.count(); ++i) {
      QDomNode link = links.item(i);

      if (link.isElement()) {
         QDomElement e = link.toElement();

         processChildren(e, pages);
         }
      }
  }


void HelpContentWidget::processAttributes(const QDomElement& e, QMap<QString, QString>& pages, QTreeWidgetItem* item) {
  int mx = e.attributes().count();

  if (mx > 0) {
     for (int i=0; i < mx; ++i) {
         const QDomNode& n = e.attributes().item(i);

         if (n.nodeName() == "title")    item->setText(0, tr(n.nodeValue().toStdString().c_str()));
         else if (n.nodeName() == "ref") item->setText(1, n.nodeValue());
         }
     pages[item->text(1)] = item->text(0);
     }
  }


void HelpContentWidget::processChildren(const QDomElement& e, QMap<QString, QString>& pages, QTreeWidgetItem* parent) {
  ++level;
  for (QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling()) {
      if (n.isElement()) processElement(n.toElement(), pages, parent);
      }
  --level;
  }


QTreeWidgetItem* HelpContentWidget::createItem(const QDomElement &e, QMap<QString, QString>& pages, QTreeWidgetItem *parent) {
  QTreeWidgetItem* item;

  if (parent) {
     item = new QTreeWidgetItem(parent);
     parent->setIcon(0, folderIcon);
     }
  else item = new QTreeWidgetItem(this);
  item->setIcon(0, pageIcon);
  processAttributes(e, pages, item);

  return item;
  }


QTreeWidgetItem* HelpContentWidget::processElement(const QDomElement& e, QMap<QString, QString>& pages, QTreeWidgetItem* parent) {
  QTreeWidgetItem* item = nullptr;

  if (e.tagName() == "section") {     
     item = createItem(e, pages, parent);

     processChildren(e, pages, item);
     }
  return item;
  }


void HelpContentWidget::setFolderIcon(const QIcon &ico) {
  folderIcon = ico;
  }


void HelpContentWidget::setHelpIcon(const QIcon &ico) {
  helpIcon = ico;
  }


void HelpContentWidget::setPageIcon(const QIcon &ico) {
  pageIcon = ico;
  }

void HelpContentWidget::sourceChanged(const QUrl &src) {
//  qDebug() << "HelpContentWidget::sourceChanged(" << src << ")";

  QTreeWidgetItem* node = this->invisibleRootItem();

  checkNode(node, src);
  }


void HelpContentWidget::checkNode(QTreeWidgetItem *node, const QUrl& src) {
  int mx = node->childCount();

  //  qDebug() << "node:" << node->text(1);
  if (node->text(1) == src.path()) {
     setCurrentItem(node);
     return;
     }
  for (int i=0; i < mx; ++i) {
      checkNode(node->child(i), src);
      }
  }
