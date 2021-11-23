#ifndef TOOLSTATUS_H
#define TOOLSTATUS_H
#include <dyncenterwidget.h>
class LabelAdapter;
class QVariant;
class QLabel;


class ToolStatus : public DynCenterWidget
{
  Q_OBJECT
public:
  explicit ToolStatus(const QString& fileName, QWidget* parent = nullptr);
  virtual ~ToolStatus();

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
#endif // TOOLSTATUS_H
