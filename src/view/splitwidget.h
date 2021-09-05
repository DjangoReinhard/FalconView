#ifndef SPLITWIDGET_H
#define SPLITWIDGET_H
#include <QFrame>
#include <Qt>
class QSplitter;
class QWidget;


class SplitWidget : public QFrame
{
  Q_OBJECT
public:
  SplitWidget(Qt::Orientation orientation = Qt::Vertical, QWidget* parent = nullptr);

private:
  QSplitter* divider;
  };
#endif // SPLITWIDGET_H
