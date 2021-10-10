#ifndef TOOLMODEL_H
#define TOOLMODEL_H
#include <QSqlTableModel>


class ToolModel : public QSqlTableModel
{
  Q_OBJECT
public:
  explicit ToolModel(QObject *parent = nullptr);

  QVariant      headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  QVariant      promptData(int section, int role = Qt::DisplayRole) const;
  };
#endif // TOOLMODEL_H
