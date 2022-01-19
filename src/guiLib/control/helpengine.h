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
