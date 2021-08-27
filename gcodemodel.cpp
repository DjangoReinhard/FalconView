#include "gcodemodel.h"
#include <QDebug>


GCodeModel::GCodeModel(QObject* parent, const GCodeHighlighter& gh)
 : QAbstractTableModel(parent)
 , highlighter(gh) {
 }


bool GCodeModel::loadFile(const QString& fn) {
  if (!QFile::exists(fn)) return false;
  QFile file(fn);

  if (file.open(QFile::ReadOnly)) {
     char buf[1024];
     long i = 0;

     lines.clear();
     while (file.readLine(buf, sizeof(buf)) != -1) {
           QString s(buf);

           s.remove("\r");
           s.remove("\n");
           beginInsertRows(QModelIndex(), i, i);
           highlighter.highlightBlock(s);
           lines.append(s);
           endInsertRows();
           ++i;
           }
     file.close();

     return true;
     }
  return false;
  }


int GCodeModel::rowCount(const QModelIndex& /*parent*/) const {
  return lines.size();
  }


int GCodeModel::columnCount(const QModelIndex& /*parent*/) const {
  return 1;
  }


QVariant GCodeModel::data(const QModelIndex& index, int role) const {
  if (role == Qt::DisplayRole) {
     if (index.row() <= lines.size()) {
        return lines.at(index.row());
        }
     }
  return QVariant();
  }
