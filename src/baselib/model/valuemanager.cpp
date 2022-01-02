#include <valuemanager.h>
#include <iostream>


ValueManager::ValueManager() {
  if (!instance) instance = new ValueHolder();
  assert(instance);
  }


ValueManager::ValueManager(void* pFromOuterAddressSpace) {
  if (!instance) instance = (ValueHolder*)pFromOuterAddressSpace;
  assert(instance);
  }


ValueModel* ValueManager::getModel(const QString& name, QVariant defaultValue) {
  ValueModel* vm = nullptr;

  if (!instance->models.contains(name)) {
     vm = new ValueModel(name, defaultValue);

     instance->models[name] = vm;
     }
  else vm = instance->models.value(name, nullptr);

  return vm;
  }


void ValueManager::setValue(const QString& name, const QVariant& value) {
  if (!instance->models.contains(name)) {
     ValueModel* vm = new ValueModel(name, value);

     instance->models[name] = vm;
     }
  else {
     ValueModel* vm = instance->models.value(name);

     vm->setValue(value);
     }
  }


QVariant ValueManager::getValue(const QString& name) {
  if (instance->models.contains(name)) {
     ValueModel* vm = instance->models.value(name);

     return vm->getValue();
     }
  return QVariant();
  }


void ValueManager::dump() {
  instance->dump();
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


ValueManager::ValueHolder* ValueManager::instance = nullptr;
