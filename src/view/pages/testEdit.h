#ifndef TESTEDIT_H
#define TESTEDIT_H
#include <dyncenterwidget.h>
#include <filemanagerclient.h>
class QSplitter;
class QLineEdit;
class QVariant;
class QPlainTextEdit;
class QPushButton;
class GCodeEditor;
class GCodeHighlighter;


class TestEdit : public DynCenterWidget, FileManagerClient
{
  Q_OBJECT
public:
  static const QString& className;
  TestEdit(const QString& fileName, QWidget* parent = nullptr);

  QString pageName() override;

public slots:
  void openFile();
  void fileSelected(const QString& filePath) override;

protected:
  virtual QWidget* createContent() override;
  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual void showEvent(QShowEvent *event) override;
  virtual void closeEvent(QCloseEvent* e) override;
  virtual void loadFile(const QVariant& fileName);

  QLineEdit*        fn;
  GCodeEditor*      ed;
  QPushButton*      pbOpen;
  QPushButton*      pbSave;

private:
  GCodeHighlighter* gh;
  };
#endif // PWEDITOR_H
