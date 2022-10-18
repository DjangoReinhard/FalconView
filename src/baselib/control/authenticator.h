#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H
#include <QObject>
#include <QMap>
#include <credentials.h>
class HttpRequest;


class Authenticator : public QObject
{
  Q_OBJECT
public:
  explicit Authenticator(QObject *parent = nullptr);

  QString calculateRealm(const QString& uri, const QString& hash) const;
  bool    contains(const QString& uri) const;
  bool    isConfigured() const;
  bool    isValid(const HttpRequest* request) const;
  QString lastHash() const;
  void    setHash(const QString& hash);
  void    setup(const QString& uri, const QString& user, const QString& password);

private:
  QString hash;
  QMap<QString, Credentials> config;
  };
#endif // AUTHENTICATOR_H
