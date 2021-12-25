#ifndef CENTERVIEW_H
#define CENTERVIEW_H
#include <dyncenterwidget.h>
#include <QMap>
class DynFrame;
class QKeyEvent;
class QCloseEvent;
class Kernel;


class CenterView : public DynCenterWidget
{
  Q_OBJECT
public:
  CenterView(QWidget* parent = nullptr);

  DynFrame* activatePage(const QString& name);
  QString   activePage() const;
  DynFrame* page(const QString& name);
  void      addPage(DynFrame* page, const QString& name = QString());
  void      dump() const;
  virtual void keyPressEvent(QKeyEvent* e) override;
  virtual void keyReleaseEvent(QKeyEvent* e) override;

protected:
  virtual QWidget* createContent() override;
  virtual void connectSignals() override;
  virtual void updateStyles() override;

private:
  void           windowClosing(QCloseEvent* e);

  QMap<QString, DynFrame*> pages;
  QString                  curPage;
  friend class Kernel;
  };
#endif // CENTERVIEW_H
