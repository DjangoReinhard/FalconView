#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H
#include <dynwidget.h>


class SettingsWidget : public DynWidget
{
  Q_OBJECT
public:
  SettingsWidget(const QString& fileName, QWidget* parent = nullptr);
  };
#endif // SETTINGSWIDGET_H
