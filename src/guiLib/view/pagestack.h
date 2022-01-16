#ifndef PAGESTACK_H
#define PAGESTACK_H
#include <abscenterwidget.h>
#include <QMap>
class CenterPage;
class QKeyEvent;
class QCloseEvent;
class Kernel;


class PageStack : public AbstractCenterWidget
{
  Q_OBJECT
public:
  PageStack(QWidget* parent = nullptr);

  CenterPage*    activatePage(const QString& name);
  QString        activePage() const;
  CenterPage*    page(const QString& name);
  QList<QString> pages() const;
  void           addPage(CenterPage* page, const QString& name = QString());
  void           dump() const;
  void           windowClosing(QCloseEvent* e);

protected:
  virtual QWidget* createContent() override;
  virtual void connectSignals() override;
  virtual void updateStyles() override;

private:
  QMap<QString, CenterPage*> pagePool;
  QString                    curPage;
  friend class Kernel;
  };
#endif // PAGESTACK_H
