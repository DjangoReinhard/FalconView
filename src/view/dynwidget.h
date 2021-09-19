#ifndef DYNWIDGET_H
#define DYNWIDGET_H
#include <QWidget>
class QString;
class QWidget;


class DynWidget : public QWidget
{
  Q_OBJECT
public:
  DynWidget(QWidget* parent = nullptr) : QWidget(parent) {};

protected:
  DynWidget(const QString& fileName, QWidget* parent = nullptr);

  QWidget* loadFromUI(const QString& fileName);
  };
#endif // DYNWIDGET_H
