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
  void genPreView(const QVariant& fileName);
  virtual void connectSignals() override;
  virtual void showEvent(QShowEvent *event) override;

private:
  QSplitter*        spV;
  OcctQtViewer*     view;
  };
#endif // PWEDITOR_H
