#ifndef VALUEMANAGER_H
#define VALUEMANAGER_H
#include <valuemodel.h>
#include <QString>


class ValueManager
{
public:
  ValueManager();

  ValueModel* getModel(const QString& name, QVariant defaultValue = QVariant());
  QVariant    getValue(const QString& name);
  void        setValue(const QString& name, const QVariant& value);
  void        dump();

protected:
  class ValueHolder
  {
  public:
    ValueHolder();

    void dump();

    QMap<QString, ValueModel*> models;
    };
  ValueHolder* getInstance();

private:
  static ValueHolder* instance;
  };

#endif // VALUEMANAGER_H
