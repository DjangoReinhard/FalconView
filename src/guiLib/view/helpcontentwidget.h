/* 
 * **************************************************************************
 * 
 *  file:       helpcontentwidget.h
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
#ifndef HELPCONTENTWIDGET_H
#define HELPCONTENTWIDGET_H
#include <QTreeWidget>
class QDomElement;


class HelpContentWidget : public QTreeWidget
{
  Q_OBJECT
public:
  explicit HelpContentWidget(QWidget* parent = nullptr);
  virtual ~HelpContentWidget();

  void setFolderIcon(const QIcon& ico);
  void setHelpIcon(const QIcon& ico);
  void setPageIcon(const QIcon& ico);
  void parse(const QByteArray& ba, QMap<QString, QString>& pages);
  void sourceChanged(const QUrl& src);

protected:
  QTreeWidgetItem* createItem(const QDomElement& e, QMap<QString, QString>& pages, QTreeWidgetItem* parent);
  QTreeWidgetItem* processElement(const QDomElement& e, QMap<QString, QString>& pages, QTreeWidgetItem* parent);
  void processChildren(const QDomElement& e, QMap<QString, QString>& pages, QTreeWidgetItem* parentItem = nullptr);
  void processAttributes(const QDomElement& e, QMap<QString, QString>& pages, QTreeWidgetItem* item);
  void checkNode(QTreeWidgetItem* node, const QUrl& src);

private:
  int   level;
  QIcon folderIcon;
  QIcon pageIcon;
  QIcon helpIcon;
  };
#endif // HELPCONTENTWIDGET_H
