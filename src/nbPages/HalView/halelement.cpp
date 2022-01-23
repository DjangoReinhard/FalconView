#include "halelement.h"
#include <QVariant>


HalElement::HalElement(HalElement* parent)
 : QObject(parent)
 , p(nullptr) {
  }


HalElement::~HalElement() {
  qDeleteAll(children);
  }


void HalElement::appendChild(HalElement *child) {
  children.append(child);
  child->setParent(this);
  }


HalElement* HalElement::child(int row) {
  if (row < 0 || row >= children.size())
     return nullptr;
  return children.at(row);
  }


int HalElement::childCount() const {
  return children.count();
  }


int HalElement::childNumber() {
  HalElement* p = static_cast<HalElement*>(QObject::parent());

  if (p) return p->children.indexOf(const_cast<HalElement*>(this));
  return 0;
  }


//int HalElement::columnCount() const {
//  return 1;
//  }


QVariant HalElement::data(int column) const {
  if (column == 0) return name;
  return QVariant();
  }


void HalElement::setData(int column, const QVariant& value) {
  if (!column) name = value.toString();
  }


//int HalElement::row() const {
//  if (parentItem) return parentItem->children.indexOf(const_cast<HalElement*>(this));
//  return 0;
//  }
