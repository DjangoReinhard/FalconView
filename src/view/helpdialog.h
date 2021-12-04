#ifndef HELPDIALOG_H
#define HELPDIALOG_H
#include <ui_HelpTitle.h>
#include <QDockWidget>
#include <QPixmap>
class HelpEngine;
class QSplitter;
class QTextBrowser;
class HelpContentWidget;
class HelpKeywordWidget;
class QTreeWidgetItem;
class QListWidgetItem;


class HelpDialog : public QDockWidget
{
  Q_OBJECT
public:
  HelpDialog(QWidget* parent = nullptr);

  void showHelp();

protected slots:
  void contentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
  void keywordItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
  void keyPressEvent(QKeyEvent* event) override;
  void closeEvent(QCloseEvent* event) override;

private:
  QSplitter*     sp;
  HelpEngine*    he;
  QTextBrowser*  tb;
  HelpContentWidget* cw;
  HelpKeywordWidget* kw;
  static const QString& className;
  };


class HelpTitleBar : public QWidget
{
  Q_OBJECT
public:
  explicit HelpTitleBar(QWidget* parent = nullptr);

  QSize sizeHint() const override { return minimumSizeHint(); }
  QSize minimumSizeHint() const override;

protected:
  void mouseReleaseEvent(QMouseEvent* event) override;

private:
  Ui::HelpTitle* title;
  };
#endif // HELPDIALOG_H
