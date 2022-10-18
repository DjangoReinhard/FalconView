/* 
 * **************************************************************************
 * 
 *  file:       helpengine.cpp
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
#include <helpengine.h>
#include <helpcontentwidget.h>
#include <helpkeywordwidget.h>
#include <core.h>
#include <QDomDocument>
#include <QDomNode>
#include <QVariant>
#include <QUrl>
#include <QDebug>


HelpEngine::HelpEngine(const QString& helpFile, QObject *parent)
 : QObject(parent)
 , reader(new QZipReader(helpFile))
 , level(0)
 , cw(nullptr)
 , locXT("_" + Core().languagePrefix() + ".html")
 , defXT(".html") {
  buildDir(reader->fileInfoList());
  cw = new HelpContentWidget();
  kw = new HelpKeywordWidget();
  QByteArray ba = reader->fileData("FalconView.qhp");
  QByteArray bp = reader->fileData("images/folder.svg");
  QIcon      icoF, icoL, icoP;
  QPixmap    pm;

  pm.loadFromData(bp);
  icoF.addPixmap(pm, QIcon::Normal, QIcon::Off);
  bp = reader->fileData("images/folder-open.svg");
  pm.loadFromData(bp);
  icoF.addPixmap(pm, QIcon::Normal, QIcon::On);
  bp = reader->fileData("images/help-about.svg");
  pm.loadFromData(bp);
  icoL.addPixmap(pm);
  bp = reader->fileData("images/text-info.svg");
  pm.loadFromData(bp);
  icoP.addPixmap(pm);
  cw->setFolderIcon(icoF);
  cw->setPageIcon(icoP);
  cw->parse(ba, pages);
  kw->setIcon(icoL);
  kw->parse(ba, keyWords);
//  tellContent();
  }


void HelpEngine::buildDir(const QVector<QZipReader::FileInfo> entries) {
  int mx = entries.count();

  for (int i=0; i < mx; ++i) {
      if (!entries[i].isFile) continue;
      helpDir.insert(entries[i].filePath, i);
      }
  }


QWidget* HelpEngine::contentWidget() {
  return cw;
  }


QWidget* HelpEngine::keywordWidget() {
  return kw;
  }


QString  HelpEngine::document4Keyword(const QString& keyWord) const {
  if (keyWords.contains(keyWord)) return keyWords[keyWord];
  return QString();
  }


QByteArray HelpEngine::fileData(const QString& file) const {
//  qDebug() << "HelpEngine::fileData(" << file << ")";
  QString page = file + locXT;

  if (!helpDir.contains(page)) {
     page = file + defXT;

     if (!helpDir.contains(page)) {
        if (!helpDir.contains(file)) return QByteArray();
        page = file;
        }
     }
  QByteArray ba = reader->fileData(page);
  QString    title;

  if (page.endsWith(".html")) {
     title = pages[file];

//     qDebug() << "page [" << file << "] has title: " << title;

     // markdown generates body part only, so we need to
     // add a bit to get valid html pages
     ba = wrapPage(title, ba);
     }
  return ba;
  }


QByteArray HelpEngine::wrapPage(const QString& title, const QByteArray& ba) const {
  QByteArray frame("<!DOCTYPE html><html lang=\"");

  frame += Core().languagePrefix().toUtf8();
  frame += QByteArray("\"><head><meta charset=\"utf-8\"><title>");
  frame += tr("Help").toUtf8();
  frame += QByteArray(" FalconView 0.1 | ");
  frame += title.toUtf8();
  // adding styles into meta section does not work!
  frame += QByteArray("</title></head><body>");
  frame += ba;
  frame += QByteArray("</body></html>");

  return frame;
  }


void HelpEngine::tellContent() {
  for (const QZipReader::FileInfo& e : reader->fileInfoList()) {
      qDebug() << "Helpfile-entry:" << e.filePath
               << (e.isDir ? "Dir" : "")
               << (e.isFile ? "File" : "")
               << (e.isSymLink ? "SymLink" : "");
      }
  for (auto k = pages.keyBegin(); k != pages.keyEnd(); k++) {
      qDebug() << "page[" << *k << "] => " << pages[*k];
      }
  for (auto k = keyWords.keyBegin(); k != keyWords.keyEnd(); k++) {
      qDebug() << "keywords[" << *k << "] => " << keyWords[*k];
      }
  }
