#ifndef TOOLSTATUS_H
#define TOOLSTATUS_H
#include <abscenterwidget.h>
class QVariant;
class QLabel;


class ToolStatus : public AbstractCenterWidget
{
  Q_OBJECT
public:
  explicit ToolStatus(QWidget* parent = nullptr);
  virtual ~ToolStatus();

protected:
  virtual QWidget* createContent() override;
  virtual void updateStyles() override;
  virtual void connectSignals() override;

protected slots:
  void toolChanged(const QVariant& toolNum);

private:
  bool    isInPreview;
  QLabel* curTool;
  QLabel* nxtTool;
  QLabel* tDesc;
  QLabel* tLen;
  QLabel* tRad;
  QLabel* tPic;
  };
#endif // TOOLSTATUS_H
