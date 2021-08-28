#ifndef TOOLINFODOCKABLE_H
#define TOOLINFODOCKABLE_H
#include <QDockWidget>
class LabelAdapter;
class QFile;


class ToolInfoDockable : public QDockWidget
{
  Q_OBJECT

  const int DockingTitleHeight = 39;
public:
  ToolInfoDockable(QFile& uiDesc, QWidget* parent = nullptr);
  virtual ~ToolInfoDockable();

protected:
  virtual void resizeEvent(QResizeEvent* event);
  void initializeWidget(QFile& uiDesc);

private:
  LabelAdapter* tlCur;
  LabelAdapter* tlDesc;
  LabelAdapter* tlLen;
  LabelAdapter* tlRad;
  LabelAdapter* tlNext;
  int           height;
  };
#endif // TOOLINFODOCKABLE_H
