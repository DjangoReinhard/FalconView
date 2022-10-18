#ifndef COMMANDNETWRITER_H
#define COMMANDNETWRITER_H
#include "abstractcommandwriter.h"
class Authenticator;
class QEventLoop;
class QTcpSocket;
class QHostAddress;


class CommandNetWriter : public AbstractCommandWriter
{
  Q_OBJECT
public:
  explicit CommandNetWriter(Authenticator& auth, const QHostAddress& lcHost, int lcPort, QObject *parent = nullptr);

  bool isActive() const override;
  void onConnected();
  void onDisconnect();
  void onDataRead();

  int  sendCommand(RCS_CMD_MSG& msg) override;

  static const QString LCAuthUrl;
  static const QString LCCommandUrl;

private:
  Authenticator&      auth;
  const QHostAddress& addrLC;
  QTcpSocket*         sockLC;
  int                 portLC;
  QEventLoop*         eLoop;
  QByteArray*         body;
  int                 lastRead;
  QString             hash;
  };
#endif // COMMANDNETWRITER_H
