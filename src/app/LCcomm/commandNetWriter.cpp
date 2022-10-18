#include "commandNetWriter.h"
#include "authenticator.h"
#include "httprequest.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <cmd_msg.hh>


CommandNetWriter::CommandNetWriter(Authenticator& auth, const QHostAddress& addrLC, int portLC, QObject *parent)
 : AbstractCommandWriter(parent)
 , auth(auth)
 , addrLC(addrLC)
 , sockLC(nullptr)
 , portLC(portLC)
 , lastRead(0) {
  }


bool CommandNetWriter::isActive() const {
  return true; //sockLC && sockLC->isValid();
  }


void CommandNetWriter::onConnected() {
  qDebug() << "socket connected ...";
  HttpRequest r;

  if (lastRead) {
     // send command with authentication
     r = HttpRequest(LCCommandUrl, *body);
     r.setHeaderValue(QStringLiteral("Realm")
                    , auth.calculateRealm(r.path(), hash));
     }
  else {
     // request auth token
     connect(sockLC, &QTcpSocket::readyRead, this, &CommandNetWriter::onDataRead);
     r = HttpRequest(LCAuthUrl, QByteArray());

     r.setRequestType(QStringLiteral("GET"));
     }
  qint64 bytesWritten = sockLC->write(r.toByteArray());
  sockLC->flush();

  qDebug() << "wrote" << bytesWritten << "bytes";
  if (lastRead) {
     lastRead = 0;
     delete body;
     sockLC->disconnect();
     }
  }


void CommandNetWriter::onDisconnect() {
  qDebug() << "Bye";
  }


void CommandNetWriter::onDataRead() {
  char buffer[64];
  int  bytesRead = sockLC->read(buffer, 64);

  if (!bytesRead) return;
  if (bytesRead < 64) buffer[bytesRead] = '\0';
  else buffer[63] = '\0';
  hash = QString(buffer); // auth token to authenticate command

  qDebug() << "read from socket: " << hash << " " << hash.size() << "bytes";

  sockLC->close();
  if (!lastRead) lastRead = hash.size();
  sockLC->connectToHost(addrLC, portLC); // reconnect for fresh client connection
  }


int  CommandNetWriter::sendCommand(RCS_CMD_MSG& msg) {
  body = new QByteArray((char*)&msg, msg.size);
  if (!sockLC) {
     sockLC = new QTcpSocket();
     sockLC->setSocketOption(QTcpSocket::LowDelayOption, 1);
     connect(sockLC, &QTcpSocket::connected, this, &CommandNetWriter::onConnected);
     connect(sockLC, &QTcpSocket::disconnected, this, &CommandNetWriter::onDisconnect);
     }
  sockLC->connectToHost(addrLC, portLC);

  return 0;
  }


const QString CommandNetWriter::LCAuthUrl    = QStringLiteral("/linuxcnc/auth");
const QString CommandNetWriter::LCCommandUrl = QStringLiteral("/linuxcnc/command");
