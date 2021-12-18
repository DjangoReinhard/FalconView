#ifndef HELPKEYWORDWIDGET_H
#define HELPKEYWORDWIDGET_H
#include <QListWidget>
class QDomElement;


class HelpKeywordWidget : public QListWidget
{
  Q_OBJECT
public:
  explicit HelpKeywordWidget(QWidget* parent = nullptr);
  virtual ~HelpKeywordWidget();

  void parse(const QByteArray& ba, QMap<QString, QString>& keyWords);
  void setIcon(const QIcon& icon);
  void sourceChanged(const QUrl &src);

protected:
  void processChildren(const QDomElement& e, QMap<QString, QString>& keyWords);

private:
  QIcon icon;
  };
#endif // HELPKEYWORDWIDGET_H
