#ifndef TESTEDIT_H
#define TESTEDIT_H
#include <abscenterwidget.h>
#include <CenterPageInterface.h>
#include <filemanagerclient.h>

QT_BEGIN_NAMESPACE
class QSplitter;
class QLineEdit;
class QVariant;
class QPlainTextEdit;
class QPushButton;
class GCodeEditor;
class GCodeHighlighter;
QT_END_NAMESPACE


class TestEdit : public AbstractCenterWidget, public CenterPageInterface, protected FileManagerClient
{
  Q_OBJECT
  Q_INTERFACES(CenterPageInterface)
public:
  TestEdit(const QString& fileName = ":/src/guiLib/view/GCodeEditor.ui", QWidget* parent = nullptr);

  QString pageName() override;
  void    restoreState();
  virtual QAction* viewAction() override;

public slots:
  void openFile();
  void saveFile();
  void fileSelected(const QString& filePath) override;

protected:
  virtual QWidget* createContent() override;
  virtual void connectSignals() override;
  virtual void closeEvent(QCloseEvent* e) override;
  virtual void dirtyChanged(bool dirty);
  virtual bool eventFilter(QObject*, QEvent* e) override;
  virtual void fileUpdated(const QString& fileName);
  virtual void loadFile(const QVariant& fileName);
  virtual void reallyLoadFile(const QVariant& fileName);
  virtual void showEvent(QShowEvent *event) override;
  virtual void updateStyles() override;

  QLineEdit*        fn;
  GCodeEditor*      ed;
  QPushButton*      pbOpen;
  QPushButton*      pbSave;

private:
  GCodeHighlighter* gh;
  QString           fileName;
  };
#endif // PWEDITOR_H
