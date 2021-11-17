#ifndef TOOLINFODOCKABLE_H
#define TOOLINFODOCKABLE_H
#include <dockable.h>
class LabelAdapter;
class QVariant;
class QLabel;


class ToolInfoDockable : public Dockable
{
  Q_OBJECT
public:
  ToolInfoDockable(const QString& fileName, QWidget* parent = nullptr);
  virtual ~ToolInfoDockable();

protected:
  void initializeWidget(QWidget* widget);
  void updateStyles();
  void connectSignals();

protected slots:
  void toolChanged(const QVariant& toolNum);

private:
  LabelAdapter* curTool;
  LabelAdapter* nxtTool;
  QLabel*       tlDesc;
  LabelAdapter* tlLen;
  LabelAdapter* tlRad;
  };
#endif // TOOLINFODOCKABLE_H
