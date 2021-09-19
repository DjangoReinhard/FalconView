#ifndef PWEDITOR_H
#define PWEDITOR_H
#include <dynwidget.h>
class QSplitter;
class QLineEdit;
class QVariant;
class QPlainTextEdit;
class QPushButton;
class GCodeEditor;
class GCodeHighlighter;


class PreViewEditor : public DynWidget
{
  Q_OBJECT
public:
  PreViewEditor(const QString& fileName, QWidget* parent);

protected:
  void initializeWidget();
  void connectSignals();
  void updateStyles();
  void loadFile(const QVariant& fileName);

private:
  QSplitter*        spV;
  QLineEdit*        fn;
  GCodeEditor*      ed;
  GCodeHighlighter* gh;
  QPushButton*      pbOpen;
  QPushButton*      pbSave;
  };
#endif // PWEDITOR_H
