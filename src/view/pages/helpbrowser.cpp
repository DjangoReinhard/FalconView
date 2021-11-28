#include <helpbrowser.h>
#include <QHelpEngine>


HelpBrowser::HelpBrowser(QHelpEngine* helpEngine, QWidget* parent)
 : QTextBrowser(parent)
 , helpEngine(helpEngine) {
  }


QVariant HelpBrowser::loadResource(int type, const QUrl& link) {
  if (link.scheme() == "qthelp")
     return QVariant(helpEngine->fileData(link));
  else
     return QTextBrowser::loadResource(type, link);
  }
