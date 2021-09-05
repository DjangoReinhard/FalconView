#ifndef TOOLINFODOCKABLE_H
#define TOOLINFODOCKABLE_H
#include <dockable.h>
class LabelAdapter;


class ToolInfoDockable : public Dockable
{
  Q_OBJECT
public:
  ToolInfoDockable(const QString& fileName, QWidget* parent = nullptr);
  virtual ~ToolInfoDockable();

protected:
  void initializeWidget(QWidget* widget);

private:
  LabelAdapter* tlCur;
  LabelAdapter* tlDesc;
  LabelAdapter* tlLen;
  LabelAdapter* tlRad;
  LabelAdapter* tlNext;
  };
#endif // TOOLINFODOCKABLE_H
