#ifndef PWEDITOR_H
#define PWEDITOR_H
#include <testEdit.h>
class QSplitter;
class QLineEdit;
class QVariant;
class QPlainTextEdit;
class QTextBlock;
class QPushButton;
class OcctQtViewer;
class GCodeEditor;
class GCodeHighlighter;
class PositionStatus;
class CurCodesStatus;
class ToolStatus;
class SpeedStatus;
//class JogView;


class PreViewEditor : public TestEdit
{
  Q_OBJECT
public:
  static const QString className;
  PreViewEditor(const QString& fileName, OcctQtViewer* view, bool statusInPreview, QWidget* parent = nullptr);

  QString currentRow() const;
  long    curLine() const;

public slots:
  void toggleSub();
  void setCurrentLine(const QVariant& line);

protected:
  virtual void connectSignals() override;
  virtual void showEvent(QShowEvent *event) override;
  virtual void closeEvent(QCloseEvent*) override;
  virtual bool eventFilter(QObject*, QEvent* e) override;
  virtual QWidget* createContent() override;
  void createDecorations(OcctQtViewer* v, bool sip);

protected slots:
  void genPreView(const QVariant& fileName);
  void setEditorLine(const QVariant& line);

private:
  QSplitter*        spV;
  QWidget*          frame;
//  JogView*          jp;
  OcctQtViewer*     view3D;
  PositionStatus*   posStat;
  CurCodesStatus*   ccStat;
  ToolStatus*       toolStat;
  SpeedStatus*      speedStat;
  bool              statusInPreview;
  };
#endif // PWEDITOR_H
