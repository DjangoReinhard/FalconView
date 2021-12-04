#include <helpengine.h>
#include <helpcontentwidget.h>
#include <helpkeywordwidget.h>
#include <QDomDocument>
#include <QDomNode>
#include <QVariant>
#include <QUrl>
#include <QDebug>


HelpEngine::HelpEngine(const QString& helpFile, QObject *parent)
 : QObject(parent)
 , reader(new QZipReader(helpFile))
 , level(0)
 , cw(nullptr) {
  buildDir(reader->fileInfoList());
  tellContent();
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
  bp = reader->fileData("images/help-info.png");
  pm.loadFromData(bp);
  icoL.addPixmap(pm);
  cw->setFolderIcon(icoF);
  cw->parse(ba);
  kw->setIcon(icoL);
  kw->parse(ba);
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


QVariant HelpEngine::readFile(const QString& file) {
  if (!helpDir.contains(file)) return QVariant();
  QByteArray ba = reader->fileData(file);

  return QVariant(ba);
  }


void HelpEngine::tellContent() {
  for (const QZipReader::FileInfo& e : reader->fileInfoList()) {
      qDebug() << "Helpfile-entry:" << e.filePath
               << (e.isDir ? "Dir" : "")
               << (e.isFile ? "File" : "")
               << (e.isSymLink ? "SymLink" : "");
      }
  }
