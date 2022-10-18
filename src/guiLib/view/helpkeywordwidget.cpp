/* 
 * **************************************************************************
 * 
 *  file:       helpkeywordwidget.cpp
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
#include <helpkeywordwidget.h>
#include <QCoreApplication>
#include <QDomDocument>
#include <QDomNode>
#include <QUrl>
#include <QDebug>


HelpKeywordWidget::HelpKeywordWidget(QWidget* parent)
 : QListWidget(parent) {
  }


HelpKeywordWidget::~HelpKeywordWidget() {
  }


void HelpKeywordWidget::parse(const QByteArray &ba, QMap<QString, QString>& keyWords) {
  QDomDocument doc;

  doc.setContent(ba);
  QDomNodeList links = doc.elementsByTagName("keywords");

  clear();
  for (int i=0; i < links.count(); ++i) {
      QDomNode link = links.item(i);

//      qDebug() << "\n";
//      qDebug() << "check entry #" << i;
      if (link.isElement()) {
         QDomElement e = link.toElement();

         processChildren(e, keyWords);
         }
      }
  }


void HelpKeywordWidget::processChildren(const QDomElement& e, QMap<QString, QString>& keyWords) {
  for (QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling()) {
      if (n.isElement()) {
         QDomElement      elem = n.toElement();
         QListWidgetItem* item = new QListWidgetItem();
         QString          name;
         int              mx   = elem.attributes().count();

         item->setIcon(icon);
         for (int i=0; i < mx; ++i) {
             const QDomNode& n = elem.attributes().item(i);

             if (n.nodeName() == "name") {
                name  = n.nodeValue();
                QString out(QCoreApplication::translate("HelpContentWidget", name.toStdString().c_str(), nullptr));

//                qDebug() << "HelpKeywords - keyword:" << name << "translated:" << out;
                item->setText(out);
                }
             else if (n.nodeName() == "ref") item->setToolTip(n.nodeValue());
             }
         addItem(item);
         // item shows translated texts, but search works with "original" keywords
         keyWords[name] = item->toolTip();
         }
      }
  }


void HelpKeywordWidget::setIcon(const QIcon &icon) {
  this->icon = icon;
  }


void HelpKeywordWidget::sourceChanged(const QUrl &src) {
//  int ndx = src.path().lastIndexOf(".html");
//  QString keyWord = src.path().mid(0, ndx);
  int mx = count();

//  qDebug() << "HelpKeywordWidget::sourceChanged(" << src << ")"; // -> kw:" << keyWord;
  for (int i=0; i < mx; ++i) {
      QListWidgetItem* item = this->item(i);

//      qDebug() << "item at #" << i << " -> " << item->toolTip();
      if (item->toolTip() == src.path()) {
         this->setCurrentItem(item);
         return;
         }
      }
  }
