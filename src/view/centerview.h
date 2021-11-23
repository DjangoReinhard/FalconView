#ifndef CENTERVIEW_H
#define CENTERVIEW_H
#include <QWidget>
#include <QMap>
class DynFrame;
class QCloseEvent;
class Kernel;


class CenterView : public QWidget
{
  Q_OBJECT
public:
  CenterView(QWidget* parent = nullptr);

  QWidget*       activatePage(const QString& name);
  const QString& activePage() const;
  QWidget*       page(const QString& name);
  void           addPage(DynFrame* page, const QString& name = QString());
  void           dump() const;

private:
  void           windowClosing(QCloseEvent* e);

  QMap<QString, DynFrame*> pages;
  QString                  curPage;
  friend class Kernel;
  };
#endif // CENTERVIEW_H
