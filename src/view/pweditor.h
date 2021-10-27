#ifndef PWEDITOR_H
#define PWEDITOR_H
#include <testEdit.h>
class QSplitter;
class QLineEdit;
class QVariant;
class QPlainTextEdit;
class QPushButton;
class OcctQtViewer;
class GCodeEditor;
class GCodeHighlighter;


class PreViewEditor : public TestEdit
{
  Q_OBJECT
public:
  PreViewEditor(const QString& fileName, OcctQtViewer* view, QWidget* parent);

protected:
  virtual void loadFile(const QVariant& fileName) override;
  virtual void connectSignals() override;

private:
  QSplitter*        spV;
  OcctQtViewer*     view;
  };
#endif // PWEDITOR_H
