#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H
#include <QDialog>

class QDialogButtonBox;
class QTabWidget;
class QTreeWidget;


class GeneralTab : public QWidget
{
  Q_OBJECT
public:
  explicit GeneralTab(QWidget* parent = nullptr);
  };


class GLInfoTab : public QWidget
{
  Q_OBJECT
public:
  explicit GLInfoTab(QWidget* parent = nullptr);
  };


class PluginsTab : public QWidget
{
  Q_OBJECT
public:
  explicit PluginsTab(QWidget* parent = nullptr);

private:
  QTreeWidget* tree;
  };


class AboutDialog : public QDialog
{
  Q_OBJECT
public:
  AboutDialog(QWidget* parent = nullptr);

private:
  QTabWidget*       tw;
  QDialogButtonBox* bb;
  };
#endif // ABOUTDIALOG_H
