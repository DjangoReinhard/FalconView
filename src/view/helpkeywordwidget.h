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

  void parse(const QByteArray& ba);
  void setIcon(const QIcon& icon);

protected:
  void processChildren(const QDomElement& e);

private:
  QIcon icon;
  };
#endif // HELPKEYWORDWIDGET_H
