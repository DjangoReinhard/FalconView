#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>
class QFile;


class Overlay : public QWidget
{
  Q_OBJECT
public:
  explicit Overlay(QFile& uiDesc, QWidget *parent = nullptr);

signals:

protected:
  void initializeWidget(QFile& uiDesc);
  };
#endif // OVERLAY_H
