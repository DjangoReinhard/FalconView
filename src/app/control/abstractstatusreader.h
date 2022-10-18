#ifndef ABSTRACTSTATUSREADER_H
#define ABSTRACTSTATUSREADER_H
#include <QObject>
class LCStatus;


class AbstractStatusReader : public QObject
{
  Q_OBJECT
public:
  virtual bool isActive() const          = 0;
  virtual void read()                    = 0;
  virtual const LCStatus& status() const = 0;

signals:
  void statusChanged(const LCStatus& status);

protected:
  explicit AbstractStatusReader(QObject* parent = nullptr);
  };
#endif // ABSTRACTSTATUSREADER_H
