#ifndef PLUGINDIALOG_H
#define PLUGINDIALOG_H

#include <QDialog>
#include <QIcon>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QStringList;
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE

class PluginDialog : public QDialog
{
  Q_OBJECT

public:
  PluginDialog(const QString &path, const QStringList &fileNames, QWidget *parent = nullptr);

private:
  void populateTreeWidget();

  QLabel*      label      = nullptr;
  QTreeWidget* treeWidget = nullptr;
  QPushButton* okButton   = nullptr;
  QIcon        interfaceIcon;
  QIcon        featureIcon;
  };
#endif // PLUGINDIALOG_H
