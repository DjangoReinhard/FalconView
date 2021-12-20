#ifndef PATHEDITOR_H
#define PATHEDITOR_H
#include <testEdit.h>
class PreViewEditor;
class QSplitter;
class QLineEdit;
class QVariant;
class QPlainTextEdit;
class QPushButton;
class GCodeEditor;
class GCodeHighlighter;


class PathEditor : public TestEdit
{
  Q_OBJECT
public:
  static const QString className;
  PathEditor(const QString& fileName, QWidget* parent = nullptr);

protected:
  virtual void loadFile(const QVariant& fileName) override;
  virtual void connectSignals() override;
  virtual void fileUpdated(const QString& fileName) override;

private:
  void reallyLoadFile(const QVariant& fileName);
  };
#endif // PWEDITOR_H
