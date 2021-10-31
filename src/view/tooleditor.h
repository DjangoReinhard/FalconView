#ifndef TOOLEDITOR_H
#define TOOLEDITOR_H
#include <QWidget>
class QComboBox;
class QSqlRecord;
class QSqlQueryModel;
class ToolCategoryModel;
class ToolModel;

QT_BEGIN_NAMESPACE
namespace Ui { class Form; }
QT_END_NAMESPACE


class ToolEditor : public QWidget
{
  Q_OBJECT
public:
  explicit ToolEditor(QWidget *parent = nullptr);

  void getChanges(QSqlRecord& r);
  void setModel(const QSqlRecord& r);
  void setRow2Edit(int row);

protected:
  void selectCBEntry(QComboBox* cb, const QString& name);
  void dumpModel();

  Ui::Form*       ui;
  QSqlQueryModel* model;
  int             toolId;
  static QPair<QString, QString> names[];
  };
#endif // TOOLEDITOR_H
