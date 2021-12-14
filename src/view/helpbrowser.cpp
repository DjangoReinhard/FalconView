#include <helpbrowser.h>
#include <helpengine.h>
#include <QDebug>


HelpBrowser::HelpBrowser(QWidget* parent)
 : QTextBrowser(parent)
 , engine(nullptr) {
  document()->setDefaultStyleSheet(defaultStyles);
  }


HelpBrowser::~HelpBrowser() {
  }


QVariant HelpBrowser::loadResource(int, const QUrl& link) {
  // all files for help system are inside the helpfile, so
  // don't need to use type of url ...
  return engine->fileData(link.path());
  }


void HelpBrowser::setHelpEngine(HelpEngine *he) {
  engine = he;
  }

const QString HelpBrowser::defaultStyles("table, th, td {"
                                           "border-width: 1px;"
                                           "border-color: #CCCCCC;"
                                           "border-collapse: collapse;"
                                         "}"
                                         "img {vertical-align: middle; }"
                                         "th, td {"
                                           "padding: 15px;"
                                         "}");
