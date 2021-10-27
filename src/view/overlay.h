#ifndef OVERLAY_H
#define OVERLAY_H
#include <dynwidget.h>
class QFile;
class QLabel;
class LabelAdapter;


class Overlay : public DynWidget
{
  Q_OBJECT
public:
  explicit Overlay(const QString& fileName, QWidget *parent = nullptr);

  virtual void connectSignals();
  virtual void updateStyles();

private:
  QLabel*       ovRelX;
  QLabel*       ovRelY;
  QLabel*       ovRelZ;
  QLabel*       ovRelA;
  QLabel*       ovRelB;
  QLabel*       ovDtgX;
  QLabel*       ovDtgY;
  QLabel*       ovDtgZ;
  QLabel*       ovDtgA;
  QLabel*       ovDtgB;
  QLabel*       xTitle;
  LabelAdapter* relX;
  LabelAdapter* relY;
  };
#endif // OVERLAY_H
