#ifndef GCODEMODEL_H
#define GCODEMODEL_H

#include "gcodehighlighter.h"
#include <QAbstractTableModel>
#include <QVector>
#include <QFile>


class GCodeModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  GCodeModel(QObject* parent, const GCodeHighlighter& highlighter);

  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  bool loadFile(const QString& fileName);

private:
  QVector<QString> lines;
  GCodeHighlighter highlighter;
  };

#endif // GCODEMODEL_H
