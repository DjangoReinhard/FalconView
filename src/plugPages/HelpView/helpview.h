#ifndef HELPVIEW_H
#define HELPVIEW_H
#include <abscenterwidget.h>
class QTreeWidgetItem;
class QListWidgetItem;
class QTextBrowser;
class QTabWidget;
class QSplitter;
class HelpEngine;
class HelpContentWidget;
class HelpKeywordWidget;


class HelpView : public AbstractCenterWidget
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "PluginPageInterface_iid" FILE "helpView.json")
#endif
public:
  explicit HelpView(QWidget* parent = nullptr);

  void help4Keyword(const QString& keyWord);
  void restoreState();
  void saveState();

  virtual void closeEvent(QCloseEvent* event) override;

protected:
  virtual QWidget* createContent() override;
  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual bool eventFilter(QObject* o, QEvent* e) override;

protected slots:
  void contentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
  void keywordItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
  void sourceChanged(const QUrl &src);
  void tabChanged(int index);

private:
  QTextBrowser*      tb;
  QSplitter*         sp;
  HelpEngine*        he;
  QTabWidget*        tw;
  HelpContentWidget* cw;
  HelpKeywordWidget* kw;
  };
#endif // HELPVIEW_H
