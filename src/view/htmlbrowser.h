#ifndef HTMLBROWSER_H
#define HTMLBROWSER_H
#include <QTextBrowser>
class HelpEngine;


class HTMLBrowser : public QTextBrowser
{
  Q_OBJECT
public:
  explicit HTMLBrowser(HelpEngine& engine, QWidget* parent = nullptr);
  virtual ~HTMLBrowser();

  QVariant loadResource(int type, const QUrl &name);

private:
  HelpEngine& engine;
  };
#endif // HTMLBROWSER_H
