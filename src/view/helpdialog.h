#ifndef HELPDIALOG_H
#define HELPDIALOG_H
#include <ui_HelpTitle.h>
#include <QDockWidget>
#include <QPixmap>
class HelpEngine;
class QSplitter;
class QTextBrowser;
class QTabWidget;
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
  void help4Keyword(const QString& keyWord);

protected slots:
  void contentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
  void keywordItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
  void keyPressEvent(QKeyEvent* event) override;
  void closeEvent(QCloseEvent* event) override;
  void sourceChanged(const QUrl &src);
  void tabChanged(int index);

private:
  QTextBrowser*      tb;
  QSplitter*         sp;
  HelpEngine*        he;
  QTabWidget*        tw;
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
  void  setTitle(const QString& title);

protected:
  void mouseReleaseEvent(QMouseEvent* event) override;

private:
  Ui::HelpTitle* titleBar;
  };
#endif // HELPDIALOG_H
