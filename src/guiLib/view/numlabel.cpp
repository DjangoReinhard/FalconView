#include <numlabel.h>
#include <QLocale>
#include <QResizeEvent>
#include <QDebug>
#include <guicore.h>


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
  setText(GuiCore().locale().toString(v.toDouble(), 'f', digits));
  }
