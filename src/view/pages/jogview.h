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
  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual void setupUi(DynCenterWidget* parent);
  void jog(int axis, int step);
  void singleStep(bool singleStep);

private:
  Ui::JogForm* ui;
  };
#endif // JOGVIEW_H
