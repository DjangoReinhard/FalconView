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
  static const QString className;
  PreViewEditor(const QString& fileName, OcctQtViewer* view, QWidget* parent);

protected:
  virtual void connectSignals() override;
  virtual void showEvent(QShowEvent *event) override;
  virtual void keyPressEvent(QKeyEvent* e) override;
  virtual void closeEvent(QCloseEvent*) override;

protected slots:
  void setCurrentLine(const QVariant& line);
  void genPreView(const QVariant& fileName);

private:
  QSplitter*        spV;
  OcctQtViewer*     view3D;
  };
#endif // PWEDITOR_H
