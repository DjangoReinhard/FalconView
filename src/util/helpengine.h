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

  QVariant readFile(const QString& file);
  QWidget* contentWidget();
  QWidget* keywordWidget();

  QString  page4Keyword(const QString& keyWord) const;
  void     tellContent();

protected:
  void     buildDir(const QVector<QZipReader::FileInfo> entries);

private:
  QZipReader*            reader;
  QMap<QString, int>     helpDir;
  QMap<QString, QString> keyWords;
  int                    level;
  HelpContentWidget*     cw;
  HelpKeywordWidget*     kw;
  };

#endif // HELPENGINE_H
