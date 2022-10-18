#ifndef CREDENTIALS_H
#define CREDENTIALS_H
#include <QObject>


struct Credentials
{
  Credentials() {}
  Credentials(const QString& user, const QString password)
   : user(user)
   , password(password) {}

  QString user;
  QString password;
  };
#endif // CREDENTIALS_H
