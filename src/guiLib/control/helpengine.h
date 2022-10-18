/* 
 * **************************************************************************
 * 
 *  file:       helpengine.h
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
#ifndef HELPENGINE_H
#define HELPENGINE_H
#include <QObject>
#include <QMap>
#include <QtGui/private/qzipreader_p.h>
class QDomElement;
class HelpContentWidget;
class HelpKeywordWidget;


class HelpEngine : public QObject
{
  Q_OBJECT
public:
  explicit HelpEngine(const QString& helpFile, QObject *parent = nullptr);

  QByteArray fileData(const QString& file) const;
  QWidget*   contentWidget();
  QWidget*   keywordWidget();

  QString  document4Keyword(const QString& keyWord) const;
  void     tellContent();

protected:
  void       buildDir(const QVector<QZipReader::FileInfo> entries);
  QByteArray wrapPage(const QString& title, const QByteArray& ba) const;

private:
  QZipReader*            reader;
  QMap<QString, int>     helpDir;
  QMap<QString, QString> pages;
  QMap<QString, QString> keyWords;
  int                    level;
  HelpContentWidget*     cw;
  HelpKeywordWidget*     kw;
  const QString          locXT;
  const QString          defXT;
  };

#endif // HELPENGINE_H
