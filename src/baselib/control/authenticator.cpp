#include <authenticator.h>
#include <httprequest.h>
#include <QDateTime>
#include <QCryptographicHash>
#include <QDebug>


Authenticator::Authenticator(QObject *parent)
 : QObject(parent) {
  }

bool Authenticator::contains(const QString &uri) const {
  return config.contains(uri);
  }


bool Authenticator::isConfigured() const {
  return config.size() > 0;
  }


bool Authenticator::isValid(const HttpRequest* request) const {
  if (!request
   || !config.contains(request->path())) return false;
  QString realm = calculateRealm(request->path(), hash);

  return request->headerValue(QStringLiteral("Realm")) == realm;
  }


QString Authenticator::lastHash() const {
  return hash;
  }


void Authenticator::setup(const QString &uri, const QString &user, const QString &rawPW) {
  QString password = QString(QCryptographicHash::hash(rawPW.toLatin1(), QCryptographicHash::Md5).toHex()).toUpper();
  config.insert(uri, Credentials(user, password));
  }


void Authenticator::setHash(const QString &hash) {
  qDebug() << "stored hash: " << hash;
  this->hash = hash;
  }


QString Authenticator::calculateRealm(const QString& uri, const QString& hash) const {
  Credentials c     = config.value(uri);
  qint64      when  = ((QDateTime::currentSecsSinceEpoch() + 1) / 2) * 2;
  QString     src   = QStringLiteral("%1%2%3%4").arg(hash).arg(c.user).arg(when).arg(c.password);
  QString     token = QString(QCryptographicHash::hash(src.toLatin1(), QCryptographicHash::Md5).toHex()).toUpper();

  qDebug() << "calculated token:" << token;

  return token;
  }
