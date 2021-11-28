#ifndef HELPDIALOG_H
#define HELPDIALOG_H
#include <QDockWidget>
class QHelpEngine;


class HelpDialog : public QDockWidget
{
  Q_OBJECT
public:
  HelpDialog(QWidget* parent = nullptr);

  void init();

private:
  QHelpEngine* helpEngine;
  };
#endif // HELPDIALOG_H
