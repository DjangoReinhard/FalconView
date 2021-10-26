#ifndef DYNWIDGET_H
#define DYNWIDGET_H
#include <QWidget>
class QString;
class QWidget;
class QAction;


class DynWidget : public QWidget
{
  Q_OBJECT
public:
  DynWidget(QWidget* parent = nullptr) : QWidget(parent), vAction(nullptr) {};

  QAction* viewAction();

protected:
  DynWidget(const QString& fileName, QWidget* parent = nullptr);

  QWidget* loadFromUI(const QString& fileName);

private:
  QAction* vAction;
  };
#endif // DYNWIDGET_H
