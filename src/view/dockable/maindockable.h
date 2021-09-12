#ifndef MAINDOCKABLE_H
#define MAINDOCKABLE_H
#include <QDockWidget>
class QStackedLayout;


class MainDockable : public QDockWidget
{
  Q_OBJECT
public:
  MainDockable(QWidget* parent = nullptr);

  int addPage(const QString& name, QWidget* page);

private:
  QStackedLayout* layout;
  };
#endif // MAINDOCKABLE_H
