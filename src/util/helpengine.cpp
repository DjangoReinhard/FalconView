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
  QIcon      icoF, icoL;
  QPixmap    pm;

  pm.loadFromData(bp);
  icoF.addPixmap(pm, QIcon::Normal, QIcon::Off);
  bp = reader->fileData("images/folder-open.svg");
  pm.loadFromData(bp);
  icoF.addPixmap(pm, QIcon::Normal, QIcon::On);
  bp = reader->fileData("images/help-about.svg");
  pm.loadFromData(bp);
  icoL.addPixmap(pm);
  cw->setFolderIcon(icoF);
  cw->parse(ba, pages);
  kw->setIcon(icoL);
  kw->parse(ba, keyWords);
  tellContent();
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


QString  HelpEngine::page4Keyword(const QString& keyWord) const {
  if (keyWords.contains(keyWord)) return keyWords[keyWord];
  return QString();
  }


QVariant HelpEngine::readFile(const QString& file) {
  qDebug() << "HelpEngine::readFile(" << file << ")";
  QString page = file + locXT;

  if (!helpDir.contains(page)) {
     page = file + defXT;

     if (!helpDir.contains(page)) {
        if (!helpDir.contains(file)) return QVariant();
        page = file;
        }
     }
  QByteArray ba = reader->fileData(page);
  QString    title;

  if (page.endsWith(".html")) {
     title = pages[file];

     qDebug() << "page [" << file << "] has title: " << title;

     ba = wrapPage(title, ba);
     }
  return QVariant(ba);
  }


QByteArray HelpEngine::wrapPage(const QString& title, const QByteArray& ba) {
  QByteArray frame("<!DOCTYPE html><html lang=\"");

  frame += Core().languagePrefix().toUtf8();
  frame += QByteArray("\"><head><meta charset=\"utf-8\"><title>");
  frame += tr("Help").toUtf8();
  frame += QByteArray(" FalconView 0.1 | ");
  frame += title.toUtf8();
  frame += QByteArray("</title><style>");
  // styles ?!?
//  frame += QByteArray("table, th, td {"
//                      "border: medium solid black;"
//                      "border-collapse: collapse;"
//                      "}");

  frame += QByteArray("</style></head><body>");
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
