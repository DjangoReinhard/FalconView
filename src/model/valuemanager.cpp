#include <valuemanager.h>
#include <iostream>


ValueManager::ValueManager() {
  }


ValueManager::ValueHolder* ValueManager::getInstance() {
  if (!instance) {
     instance = new ValueHolder();
     }
  return ValueManager::instance;
  }


ValueModel* ValueManager::getModel(const QString& name, QVariant defaultValue) {
  ValueModel* vm = nullptr;

  if (!getInstance()->models.contains(name)) {
     vm = new ValueModel(name, defaultValue);

     getInstance()->models[name] = vm;
     }
  else vm = getInstance()->models.value(name, nullptr);

  return vm;
  }


void ValueManager::setValue(const QString& name, const QVariant& value) {
  if (!getInstance()->models.contains(name)) {
     ValueModel* vm = new ValueModel(name, value);

     getInstance()->models[name] = vm;
     }
  else {
     ValueModel* vm = getInstance()->models.value(name);

     vm->setValue(value);
     }
  }


QVariant ValueManager::getValue(const QString& name) {
  if (getInstance()->models.contains(name)) {
     ValueModel* vm = getInstance()->models.value(name);

     return vm->getValue();
     }
  return QVariant();
  }


void ValueManager::dump() {
  getInstance()->dump();
  }


ValueManager::ValueHolder::ValueHolder() {
  }


void ValueManager::ValueHolder::dump() {
  QMap<QString, ValueModel*>::const_iterator i = models.constBegin();

  std::cout << "known ValueModels are:" << std::endl;
  while (i != models.constEnd()) {
        std::cout << i.key().toStdString().c_str()
                  << ": " << i.value()->getName().toStdString().c_str()
                  << "\t with value: " << i.value()->getValue().toString().toStdString().c_str()
                  << std::endl;
        ++i;
        }
  std::cout << std::endl;
  }


ValueManager::ValueHolder* ValueManager::instance;
