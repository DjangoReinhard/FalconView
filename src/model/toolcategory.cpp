#include <toolcategory.h>
#include <QDebug>


ToolCategory::ToolCategory(int id, const QString& name, ToolCategory* parent)
 : QObject((QObject*)parent)
 , id(id)
 , name(name) {
  }


void ToolCategory::appendChild(ToolCategory* child) {
  children.append(child);
  }


int ToolCategory::columnCount() const {
  return 1;
  }


int ToolCategory::childCount() const {
  return children.count();
  }


QVariant ToolCategory::data(int column) const {
  if (column == 0) return name;
  if (column == 9) return id;
  return QVariant();
  }


ToolCategory* ToolCategory::child(int row) {
  if (row < 0 || row >= children.size()) return nullptr;
  return children.at(row);
  }


ToolCategory* ToolCategory::parent() {
  return static_cast<ToolCategory*>(QObject::parent());
  }


int ToolCategory::row() const {
  if (QObject::parent()) return static_cast<ToolCategory*>(QObject::parent())->children.indexOf(const_cast<ToolCategory*>(this));
  return 0;
  }


void ToolCategory::dump() {
  qDebug() << "toolCategory: #" << id << " / " << name << " (" << static_cast<ToolCategory*>(QObject::parent())->name << ")";
  }
