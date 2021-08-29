#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
class QFile;


class SettingsWidget : public QWidget
{
  Q_OBJECT
public:
  SettingsWidget(QFile& uiDesc, QWidget* parent);

protected:
  void initializeWidget(QFile& uiDesc);
  };
#endif // SETTINGSWIDGET_H
