#ifndef HELPBROWSER_H
#define HELPBROWSER_H
#include <QTextBrowser>
class HelpEngine;


class HelpBrowser : public QTextBrowser
{
  Q_OBJECT
public:
  explicit HelpBrowser(QWidget* parent = nullptr);
  virtual ~HelpBrowser();

  QVariant loadResource(int type, const QUrl &name);
  void     setHelpEngine(HelpEngine* he);

private:
  HelpEngine*          engine;
  static const QString defaultStyles;
  };
#endif // HELPBROWSER_H
