#ifndef PWEDITOR_H
#define PWEDITOR_H
#include <dynwidget.h>
class QSplitter;
class QLineEdit;
class QVariant;
class QPlainTextEdit;
class QPushButton;
class OcctQtViewer;
class GCodeEditor;
class GCodeHighlighter;


class PreViewEditor : public DynWidget
{
  Q_OBJECT
public:
  PreViewEditor(const QString& fileName, OcctQtViewer* view, QWidget* parent);

public slots:
  void openFile();

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
  OcctQtViewer*     view;
  QPushButton*      pbOpen;
  QPushButton*      pbSave;
  };
#endif // PWEDITOR_H
