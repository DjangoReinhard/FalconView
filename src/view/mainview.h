#ifndef MAINVIEW_H
#define MAINVIEW_H
#include <QWidget>
#include <QMap>


class MainView : public QWidget
{
  Q_OBJECT
public:
  MainView(QWidget* parent = nullptr);

  void activatePage(const QString& name);
  void addPage(const QString& name, QWidget* page);

private:
  QMap<QString, QWidget*> pages;
  };
#endif // MAINVIEW_H
