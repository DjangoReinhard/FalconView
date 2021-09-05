#ifndef DYNWIDGET_H
#define DYNWIDGET_H
#include <QFrame>
class QString;
class QWidget;


class DynWidget : public QFrame
{
  Q_OBJECT
public:
  DynWidget(const QString& fileName, QWidget* parent = nullptr);
  };
#endif // DYNWIDGET_H
