#ifndef TOOLINFODOCKABLE_H
#define TOOLINFODOCKABLE_H
#include <dyncenterwidget.h>
class LabelAdapter;
class QVariant;
class QLabel;


class ToolInfoDockable : public DynCenterWidget
{
  Q_OBJECT
public:
  explicit ToolInfoDockable(const QString& fileName, QWidget* parent = nullptr);
  virtual ~ToolInfoDockable();

protected:
  virtual QWidget* createContent() override;
  virtual void updateStyles() override;
  virtual void connectSignals() override;

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
