#include "httprequest.h"
#include <QDebug>


// POST /linuxcnc/command HTTP/1.1
// Realm: what-ever
// Content-Type: text/plain
// User-Agent: PostmanRuntime/7.29.2
// Accept: */*
// Postman-Token: f581c4d3-4608-4cda-b5c6-928b34fd8a47
// Host: 192.39.29.19:1234
// Accept-Encoding: gzip, deflate, br
// Connection: keep-alive
// Content-Length: 19
//
// [was geht ab mann?]
//
//Receivers request
HttpRequest::HttpRequest(const QString& rawMsg, QObject *parent)
 : QObject(parent) {
  QStringList parts = rawMsg.split("\r\n");
  QRegExp reg(":\\s+");

  if (parts.size()) {
     QStringList sp = parts[0].split(" ");

     if (sp.size() > 2) {
        parts.pop_front();
        reqType  = sp.at(0);
        uri      = sp.at(1);
        proto    = sp.at(2);
        }

     while (parts.size()) {
           QStringList sub = parts[0].split(reg);

           parts.pop_front();
           if (sub.size() > 1) {
              hdArgs[sub[0]] = sub[1];
              }
           else break;
           }
     payload = parts.join("\r\n").toLatin1();        // undo initial splitting
     }
  }


HttpRequest::HttpRequest(QObject* parent)
 : QObject(parent)
 , reqType("POST")
 , proto("HTTP/1.1") {
  }


HttpRequest::HttpRequest(const HttpRequest& other) {
  *this = other;
  }


//Senders request
HttpRequest::HttpRequest(const QString& uri, const QByteArray& body, QObject* parent)
 : QObject(parent)
 , reqType("POST")
 , uri(uri)
 , proto("HTTP/1.1")
 , payload(body) {
  }


HttpRequest& HttpRequest::operator=(const HttpRequest &other) {
  if (this == &other) return *this;
  reqType = other.reqType;
  uri     = other.uri;
  proto   = other.proto;
  payload = other.payload;
  hdArgs  = other.hdArgs;

  return *this;
  }


void HttpRequest::setHeaderValue(const QString &key, const QString &value) {
  hdArgs.insert(key, value);
  }


void HttpRequest::setRequestType(const QString &type) {
  reqType = type;
  }


QByteArray HttpRequest::toByteArray() {
  QByteArray rv;

  hdArgs["Content-Length"] = QString("%0").arg(payload.size());
  rv.append(reqType.toLatin1());
  rv.append(' ');
  rv.append(uri.toLatin1());
  rv.append(' ');
  rv.append(proto.toLatin1());
  rv.append("\r\n");

  for (int i=0; i < hdArgs.size(); ++i) {
      QString k = hdArgs.keys().at(i);

      rv.append(k.toLatin1());
      rv.append(": ");
      rv.append(hdArgs.value(k).toLatin1());
      rv.append("\r\n");
      }
  rv.append("\r\n");
  rv.append(payload);

  return rv;
  }
