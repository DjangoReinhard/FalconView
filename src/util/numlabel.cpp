#include <numlabel.h>
#include <core.h>
#include <QLocale>
#include <QResizeEvent>
#include <QDebug>


NumLabel::NumLabel(QWidget* parent, int digits)
 : QLabel(parent)
 , client(nullptr)
 , digits(digits) {
  }


NumLabel::~NumLabel() {
  }


void NumLabel::setDependant(QLabel *client) {
  this->client = client;
  }


void NumLabel::setDigits(int digits) {
  this->digits = digits;
  }


void NumLabel::resizeEvent(QResizeEvent *e) {
  qDebug() << "NumLabel[" << objectName() << "] resized to" << e->size();
  qDebug() << "NumLabel[" << objectName() << "] min height:" << this->minimumHeight();
  if (client) {
     qDebug() << "NumLabel - client has old size:" << client->size();
     qDebug() << "NumLabel - client has min height:" << client->minimumHeight();
     client->resize(e->size());
     }
  }


void NumLabel::setValue(const QVariant &v) {
  setText(Core().locale().toString(v.toDouble(), 'f', digits));
  }
