#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
#include <QObject>
#include <QMap>


class HttpRequest : public QObject
{
  Q_OBJECT
public:
  explicit HttpRequest(QObject* parent = nullptr);
  explicit HttpRequest(const HttpRequest& other);
  explicit HttpRequest(const QString& rawMsg, QObject* parent = nullptr);
  explicit HttpRequest(const QString& uri, const QByteArray& body, QObject* parent = nullptr);
  virtual ~HttpRequest() = default;

  QByteArray& content()        { return payload; }
  QString     headerValue(const QString& key) const { return hdArgs[key]; }
  QString     path() const     { return uri; }
  QString     protocol() const { return proto; }
  QString     type() const     { return reqType; }
  void        setHeaderValue(const QString& key, const QString& value);
  void        setRequestType(const QString& type);
  QByteArray  toByteArray();

  HttpRequest& operator=(const HttpRequest& other);

private:
  QString reqType;
  QString uri;
  QString proto;
  QByteArray payload;
  QMap<QString, QString> hdArgs;
  };
#endif // HTTPREQUEST_H
