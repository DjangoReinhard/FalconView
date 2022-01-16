#ifndef HELPDOCKABLE_H
#define HELPDOCKABLE_H
//#include <ui_HelpTitle.h>
#include <QDockWidget>
//#include <QPixmap>
class HelpView;
//class QSplitter;
//class QTextBrowser;
//class QTabWidget;
//class HelpContentWidget;
//class HelpKeywordWidget;
//class QTreeWidgetItem;
//class QListWidgetItem;

namespace Ui {
  class HelpTitle;
}


class HelpDockable : public QDockWidget
{
  Q_OBJECT
public:
  HelpDockable(HelpView* view, QWidget* parent = nullptr);

  void showHelp();
  void help4Keyword(const QString& keyWord);

protected:
  void closeEvent(QCloseEvent* event) override;

//  void contentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
//  void keywordItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
  void keyPressEvent(QKeyEvent* event) override;
//  void sourceChanged(const QUrl &src);
//  void tabChanged(int index);

//private:
//  QTextBrowser*      tb;
//  QSplitter*         sp;
//  HelpEngine*        he;
//  QTabWidget*        tw;
//  HelpContentWidget* cw;
//  HelpKeywordWidget* kw;
//  static const QString& className;
  HelpView* hv;
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
#endif // HELPDOCKABLE_H
