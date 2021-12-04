#include <htmlbrowser.h>
#include <helpengine.h>
#include <QDebug>


HTMLBrowser::HTMLBrowser(HelpEngine& engine, QWidget* parent)
 : QTextBrowser(parent)
 , engine(engine) {
  }


HTMLBrowser::~HTMLBrowser() {
  }


QVariant HTMLBrowser::loadResource(int type, const QUrl& link) {
  qDebug() << "loadResource(" << type << "url:" << link;

  return engine.readFile(link.path());
  }
