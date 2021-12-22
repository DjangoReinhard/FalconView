#include <numlabel.h>
#include <core.h>
#include <QLocale>
#include <QResizeEvent>
#include <QDebug>


NumLabel::NumLabel(QWidget* parent, int digits)
 : QLabel(parent)
 , digits(digits) {
  }


NumLabel::~NumLabel() {
  }


void NumLabel::setDigits(int digits) {
  this->digits = digits;
  }


void NumLabel::setValue(const QVariant &v) {
  setText(Core().locale().toString(v.toDouble(), 'f', digits));
  }
