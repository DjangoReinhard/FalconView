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

  QWidget* activatePage(const QString& name);
  QWidget* page(const QString& name);
  void     addPage(DynWidget* page, const QString& name = QString());

  void     dump() const;

private:
  QMap<QString, DynWidget*> pages;
  };
#endif // MAINVIEW_H
