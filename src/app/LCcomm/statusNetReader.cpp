#define WANT_BENCH
#include <statusNetReader.h>
#include <LCStatus.h>
#include <string>
#include <cmath>
#include <QDebug>
#define WANT_MULTICAST


StatusNetReader::StatusNetReader(int port, QObject *parent)
 : AbstractStatusReader(parent)
 , mcAddr(QStringLiteral("226.1.1.1"))
 , port(port)
 , lcStatus(new LCStatus())
 , start(std::chrono::steady_clock::now()) {
#ifdef WANT_MULTICAST
  bool ok = udpSock.bind(QHostAddress::AnyIPv4, port);
#else
  bool ok = udpSock.bind(port, QUdpSocket::ShareAddress);
#endif

  if (ok) qDebug() << "successful bound to multi-/broadcast port:" << port;
  else    qDebug() << "OUPS - failed to bind to multi-/broadcast port:" << port;
#ifdef WANT_MULTICAST
  udpSock.joinMulticastGroup(mcAddr);
#endif
  connect(&udpSock, &QUdpSocket::readyRead, this, &StatusNetReader::read);
  }


bool StatusNetReader::isActive() const {
  return udpSock.isValid();
  }


void StatusNetReader::read() {
#ifdef WANT_BENCH
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

  qDebug() << "statusNetReader waited" << time_span.count() * 1000 << " milli-seconds";
#endif
  QByteArray datagram;

  while (udpSock.hasPendingDatagrams()) {
        datagram.resize(int(udpSock.pendingDatagramSize()));
        udpSock.readDatagram(datagram.data(), datagram.size());
        }
  memcpy((char*)lcStatus, datagram.data(), fmin(datagram.size(), sizeof(LCStatus)));
  qDebug() << "\t\tgot status update ..." << lcStatus->trajPosition[0]
           << "/" << lcStatus->trajPosition[1] << "/" << lcStatus->trajPosition[2];
  emit statusChanged(*lcStatus);
#ifdef WANT_BENCH
  start = std::chrono::steady_clock::now();
#endif
  }
