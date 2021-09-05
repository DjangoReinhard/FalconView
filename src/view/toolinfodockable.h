#ifndef TOOLINFODOCKABLE_H
#define TOOLINFODOCKABLE_H
#include <dockable.h>
class LabelAdapter;
class QLabel;


class ToolInfoDockable : public Dockable
{
  Q_OBJECT
public:
  ToolInfoDockable(const QString& fileName, QWidget* parent = nullptr);
  virtual ~ToolInfoDockable();

protected:
  void initializeWidget(QWidget* widget);

private:
  QLabel*       curTool;
  QLabel*       nxtTool;
  LabelAdapter* tlDesc;
  LabelAdapter* tlLen;
  LabelAdapter* tlRad;
  };
#endif // TOOLINFODOCKABLE_H
