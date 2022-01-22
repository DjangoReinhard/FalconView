#ifndef JOGVIEW_H
#define JOGVIEW_H
#include <abscenterwidget.h>
#include <CenterPageInterface.h>
#include <ui_Jog.h>

class JogView : public AbstractCenterWidget, public CenterPageInterface
{
  Q_OBJECT
  Q_INTERFACES(CenterPageInterface)
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "CenterPageInterface_iid" FILE "jogView.json")
#endif
public:
  explicit JogView(QWidget* parent = nullptr);
  virtual ~JogView();

protected:
  virtual void     closeEvent(QCloseEvent* e) override;
  virtual QWidget* createContent() override;
  virtual void     connectSignals() override;
  virtual void     updateStyles() override;
  virtual void     keyPressEvent(QKeyEvent* event) override;
  virtual bool     eventFilter(QObject* src, QEvent* event) override;
  virtual void     setupUi(AbstractCenterWidget* parent);
  virtual void     showEvent(QShowEvent* e) override;
  virtual QAction* viewAction() override;
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
