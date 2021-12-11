#include <helpbrowser.h>
#include <helpengine.h>
#include <QDebug>


HelpBrowser::HelpBrowser(QWidget* parent)
 : QTextBrowser(parent)
 , engine(nullptr) {
  this->document()->setDefaultStyleSheet(defaultStyles);
  qDebug() << "HB: def-styles:" << this->document()->defaultStyleSheet();
  }


HelpBrowser::~HelpBrowser() {
  }


QVariant HelpBrowser::loadResource(int type, const QUrl& link) {
  qDebug() << "loadResource(" << type << "url:" << link;

  return engine->readFile(link.path());
  }


void HelpBrowser::setHelpEngine(HelpEngine *he) {
  engine = he;
  }

const QString HelpBrowser::defaultStyles("table, th, td {"
                                         "border: thin solid red;"
                                         "border-collapse: collapse;"
                                         "}");
