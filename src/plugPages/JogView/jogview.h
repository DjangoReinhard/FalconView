#ifndef JOGVIEW_H
#define JOGVIEW_H
#include <abscenterwidget.h>
#include <ui_Jog.h>

class JogView : public AbstractCenterWidget
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "PluginPageInterface_iid" FILE "jogView.json")
#endif
public:
  explicit JogView(QWidget* parent = nullptr);
  virtual ~JogView();

protected:
  virtual QWidget* createContent() override;
  virtual void     connectSignals() override;
  virtual void     updateStyles() override;
  virtual void     keyPressEvent(QKeyEvent* event) override;
  virtual bool     eventFilter(QObject* src, QEvent* event) override;
  virtual void     setupUi(AbstractCenterWidget* parent);
  void incStepSize();
  void decStepSize();
  void jog(QWidget* o, int axis, int step);
  void singleStep(bool singleStep);
  void setStepSize();
  void jogVelChanged();
  void stepSizeChanged(const QVariant& stepSize);
  void sliderChanged(const QVariant& v);

private:
  Ui::JogForm*         ui;
  QList<QRadioButton*> rbl;
  double               stepSize;
  double               jogSpeed;
  double               defSpeed;
  double               maxSpeed;
  };
#endif // JOGVIEW_H
