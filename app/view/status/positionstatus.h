#ifndef POSITIONSTATUS_H
#define POSITIONSTATUS_H
#include <abscenterwidget.h>
#include <configacc.h>
#include <axismask.h>
#include <QDockWidget>
#include <QLabel>
#include <QResizeEvent>
namespace Ui {
class PositionForm;
class PositionMain;
}
class NumLabel;
class QString;
class QStackedLayout;

class PositionStatus : public AbstractCenterWidget
{
  Q_OBJECT
public:
  PositionStatus(const QString& fileName, const AxisMask& axisMask, QWidget* parent = nullptr);
  PositionStatus(const QString& fileName, const AxisMask& axisMask, QWidget* parent, QString ledOn, QString ledOff);
  virtual ~PositionStatus();

  void setLedStyles(QString onStyle, QString offStyle);
  void setXHomed(QVariant arg = QVariant(true));
  void setYHomed(QVariant arg = QVariant(true));
  void setZHomed(QVariant arg = QVariant(true));
  void setAHomed(QVariant arg = QVariant(true));
  void setBHomed(QVariant arg = QVariant(true));
  void setCHomed(QVariant arg = QVariant(true));
  void setUHomed(QVariant arg = QVariant(true));
  void setVHomed(QVariant arg = QVariant(true));
  void setWHomed(QVariant arg = QVariant(true));

public slots:
  void setAbsolute(QVariant arg = QVariant(true));
  void setRelative();

protected:
  virtual void updateStyles() override;
  virtual void connectSignals() override;
  virtual QWidget* createContent() override;
  void updatePos();
  void setActive();
  void setStyles(Ui::PositionForm* frm, const QString& s, const QFont& f, int w);
  void connectPos(Ui::PositionForm* frm, const QString& key, Config::GuiElem e);

private:
  Ui::PositionMain* frm;
  Ui::PositionForm* rel;
  Ui::PositionForm* abs;
  Ui::PositionForm* dtg;
  QStackedLayout*   sl;
  QFrame*           frmRel;
  QFrame*           frmAbs;
  bool       absolute;
  AxisMask   axisMask;
  QString    ledOn;
  QString    ledOff;

  static const char* widthPat;
  static const char* a[];
  };

#endif // POSITIONSTATUS_H
