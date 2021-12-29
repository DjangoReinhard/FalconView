#ifndef CENTERVIEW_H
#define CENTERVIEW_H
#include <abscenterwidget.h>
#include <QMap>
class DynFrame;
class QKeyEvent;
class QCloseEvent;
class Kernel;


class CenterView : public AbstractCenterWidget
{
  Q_OBJECT
public:
  CenterView(QWidget* parent = nullptr);

  DynFrame* activatePage(const QString& name);
  QString   activePage() const;
  DynFrame* page(const QString& name);
//  void      addPage(DynFrame* page, const QString& name = QString());
  void      dump() const;
  void      windowClosing(QCloseEvent* e);

protected:
  virtual QWidget* createContent() override;
  virtual void connectSignals() override;
  virtual void updateStyles() override;

private:
  QMap<QString, DynFrame*> pages;
  QString                  curPage;
  friend class Kernel;
  };
#endif // CENTERVIEW_H
