#ifndef PATHEDITOR_H
#define PATHEDITOR_H
#include <testEdit.h>
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
  PathEditor(const QString& fileName, QWidget* parent = nullptr);

protected:
  virtual void loadFile(const QVariant& fileName) override;
  };
#endif // PWEDITOR_H
