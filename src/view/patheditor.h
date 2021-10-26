#ifndef PATHEDITOR_H
#define PATHEDITOR_H
#include <dynwidget.h>
class QSplitter;
class QLineEdit;
class QVariant;
class QPlainTextEdit;
class QPushButton;
class GCodeEditor;
class GCodeHighlighter;


class PathEditor : public DynWidget
{
  Q_OBJECT
public:
  PathEditor(const QString& fileName, QWidget* parent = nullptr);

public slots:
  void openFile();

protected:
  void initializeWidget();
  void connectSignals();
  void updateStyles();
  void loadFile(const QVariant& fileName);

private:
  QLineEdit*        fn;
  GCodeEditor*      ed;
  GCodeHighlighter* gh;
  QPushButton*      pbOpen;
  QPushButton*      pbSave;
  };
#endif // PWEDITOR_H
