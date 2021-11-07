#ifndef TESTEDIT_H
#define TESTEDIT_H
#include <dynwidget.h>
#include <filemanagerclient.h>
class QSplitter;
class QLineEdit;
class QVariant;
class QPlainTextEdit;
class QPushButton;
class GCodeEditor;
class GCodeHighlighter;


class TestEdit : public DynWidget, FileManagerClient
{
  Q_OBJECT
public:
  TestEdit(const QString& fileName, QWidget* parent = nullptr);

  QString pageName() override;

public slots:
  void         openFile();
  virtual void fileSelected(const QString& filePath) override;

protected:
  void         initializeWidget();
  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual void showEvent(QShowEvent *event) override;
  virtual void loadFile(const QVariant& fileName);

  QLineEdit*        fn;
  GCodeEditor*      ed;
  QPushButton*      pbOpen;
  QPushButton*      pbSave;

private:
  GCodeHighlighter* gh;
  };
#endif // PWEDITOR_H
