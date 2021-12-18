#include <jogbutton.h>
#include <QStylePainter>
#include <QStyleOptionFocusRect>
#include <QDebug>


/*
 * ugly coding around - as QIcon does not provide a combination for a pressed (unchecked)
 * button and QButtonGroup does not support unchecked buttons and QAbstractButton::setIcon
 * is not virtual ...
 * What a mess!
 */
JogButton::JogButton(QWidget* parent)
 : QToolButton(parent)
 , counterPart(nullptr) {
  connect(this, &QToolButton::pressed, this, &JogButton::pressed);
  connect(this, &QToolButton::released, this, &JogButton::released);
  connect(this, &QToolButton::toggled, this, &JogButton::toggled);
  }


JogButton::~JogButton() {
  }


/*
 * replacement for setIcon being not virtual
 */
void JogButton::init(JogButton* other) {
  counterPart = other;
  icoDefault = icon();
  icoActive  = icon().pixmap(128, 128, QIcon::Normal, QIcon::On);
  }


/*
 * replacement for button-group to allow unchecked buttons
 */
void JogButton::pressed() {
  if (!isCheckable()) setIcon(icoActive);
  else {
     if (counterPart->isChecked()) counterPart->setChecked(false);
     }
  }


/*
 * replacement for QIcon not having state for pressed but unchecked button
 */
void JogButton::released() {
  setIcon(icoDefault);
  }


/*
 * replacement for button::click not releasing buttons, that are checkable and checked
 */
void JogButton::toggled(bool checked) {
  if (checked) {
     if (counterPart->isChecked()) counterPart->setChecked(false);
     }
  }
