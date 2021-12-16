#ifndef JOGVIEW_H
#define JOGVIEW_H
#include <dyncenterwidget.h>
#include <ui_Jog.h>


class JogView : public DynCenterWidget
{
  Q_OBJECT
public:
  static const QString& className;
  explicit JogView(QWidget* parent = nullptr);
  virtual ~JogView();

protected:
  virtual QWidget* createContent() override;
  virtual void     connectSignals() override;
  virtual void     updateStyles() override;
  virtual void     keyPressEvent(QKeyEvent* event) override;
  virtual void     setupUi(DynCenterWidget* parent);
  void jog(int axis, int step);
  void singleStep(bool singleStep);
  void stepSizeChanged();
  void jogVelChanged();
  void sliderChanged(const QVariant& v);

private:
  Ui::JogForm* ui;
  double       stepSize;
  double       defSpeed;
  double       maxSpeed;
  };
#endif // JOGVIEW_H
