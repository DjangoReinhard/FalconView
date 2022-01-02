#ifndef VALUEMANAGER_H
#define VALUEMANAGER_H
#include <valuemodel.h>
#include <QString>
class AbstractCenterWidget;


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
    friend class ValueManager;

    ValueHolder();

    void dump();

    QMap<QString, ValueModel*> models;
    };

private:
  ValueManager(void* p);
  static ValueHolder* instance;
  friend class AbstractCenterWidget;
  friend class PluginPageFactory;
  };

#endif // VALUEMANAGER_H
