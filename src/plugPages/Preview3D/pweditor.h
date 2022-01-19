#ifndef PWEDITOR_H
#define PWEDITOR_H
#include <testEdit.h>
#include <GCodeViewerInterface.h>
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


class PreViewEditor : public TestEdit, public GCodeViewerInterface
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_INTERFACES(GCodeViewerInterface)
  Q_PLUGIN_METADATA(IID "GCodeViewerInterface_iid" FILE "preview3D.json")
#endif
public:
  PreViewEditor(QWidget* parent = nullptr);

  virtual QString currentRow() const override;
  virtual long    curLine() const override;

public slots:
//  void toggleSub();
  void setCurrentLine(const QVariant& line);

protected:
  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual void showEvent(QShowEvent *event) override;
  virtual void closeEvent(QCloseEvent*) override;
  virtual bool eventFilter(QObject*, QEvent* e) override;
  virtual QWidget* createContent() override;
  virtual void patch(void* pk, void* pc, void* pv, void* pu = nullptr) override;
//  void createDecorations(OcctQtViewer* v, bool sip);

protected slots:
//  void genPreView(const QVariant& fileName);
  void setEditorLine(const QVariant& line);

private:
  QSplitter*        spV;
  QWidget*          frame;
  OcctQtViewer*     view3D;
  PositionStatus*   posStat;
  CurCodesStatus*   ccStat;
  ToolStatus*       toolStat;
  SpeedStatus*      speedStat;
  bool              statusInPreview;
  };
#endif // PWEDITOR_H
