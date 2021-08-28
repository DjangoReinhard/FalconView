#ifndef TOOLINFOWIDGET_H
#define TOOLINFOWIDGET_H
#include <QDockWidget>
class LabelAdapter;
class QFile;


class ToolInfoWidget : public QDockWidget
{
  Q_OBJECT

  const int DockingTitleHeight = 39;
public:
  ToolInfoWidget(QFile& uiDesc, QWidget* parent = nullptr);
  virtual ~ToolInfoWidget();

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
#endif // TOOLINFOWIDGET_H
