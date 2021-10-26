#ifndef MAINVIEW_H
#define MAINVIEW_H
#include <QWidget>
#include <QMap>
class DynWidget;


class MainView : public QWidget
{
  Q_OBJECT
public:
  MainView(QWidget* parent = nullptr);

  void activatePage(const QString& name);
  void addPage(const QString& name, DynWidget* page);

private:
  QMap<QString, DynWidget*> pages;
  };
#endif // MAINVIEW_H
