#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>
class QFile;
class QLabel;
class LabelAdapter;


class Overlay : public QWidget
{
  Q_OBJECT
public:
  LabelAdapter* relX;
  LabelAdapter* relY;

  explicit Overlay(QFile& uiDesc, QWidget *parent = nullptr);

signals:

protected:
  void initializeWidget(QFile& uiDesc);

private:
  QLabel*   ovRelX;
  QLabel*   ovRelY;
  QLabel*   ovRelZ;
  QLabel*   ovRelA;
  QLabel*   ovRelB;
  QLabel*   ovDtgX;
  QLabel*   ovDtgY;
  QLabel*   ovDtgZ;
  QLabel*   ovDtgA;
  QLabel*   ovDtgB;
  QLabel*   xTitle;
  };
#endif // OVERLAY_H
