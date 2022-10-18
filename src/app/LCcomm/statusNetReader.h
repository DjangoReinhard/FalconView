#ifndef STATUSNETREADER_H
#define STATUSNETREADER_H
#include <QObject>
#include <QHostAddress>
#include <QUdpSocket>
#include <abstractstatusreader.h>
class LCStatus;


class StatusNetReader : public AbstractStatusReader
{
  Q_OBJECT
public:
  explicit StatusNetReader(int port = 4321, QObject *parent = nullptr);

  virtual bool isActive() const;
  virtual void read();
  virtual const LCStatus& status() const { return *lcStatus; }

private:
  QUdpSocket   udpSock;
  QHostAddress mcAddr;
  int          port;
  LCStatus*    lcStatus;
#ifdef WANT_BENCH
  std::chrono::steady_clock::time_point start;
#endif
  };
#endif // STATUSNETREADER_H
