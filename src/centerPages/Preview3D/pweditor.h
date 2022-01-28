#ifndef PWEDITOR_H
#define PWEDITOR_H
#include <testEdit.h>
#include <GCodeViewerInterface.h>
class QAction;
class QSplitter;
class QLineEdit;
class QVariant;
class QPlainTextEdit;
class QTextBlock;
class QPushButton;
class OcctQtViewer;
class GCodeEditor;
class GCodeHighlighter;


class PreViewEditor : public TestEdit, public GCodeViewerInterface
{
  Q_OBJECT
  Q_INTERFACES(GCodeViewerInterface)
  Q_INTERFACES(CenterPageInterface)
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "GCodeViewerInterface_iid" FILE "preview3D.json")
#endif
public:
  PreViewEditor(QWidget* parent = nullptr);

  virtual QString currentRow() const override;
  virtual long    curLine() const override;

public slots:
  void setCurrentLine(const QVariant& line);
  void nextEditorLine();
  void prevEditorLine();

protected:
  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual void showEvent(QShowEvent *event) override;
  virtual void closeEvent(QCloseEvent*) override;
  virtual bool eventFilter(QObject*, QEvent* e) override;
  virtual QWidget* createContent() override;
  virtual void patch(void* pk, void* pc, void* pv, void* pu = nullptr, bool flag = false) override;
  virtual QAction* viewAction() override;

protected slots:
  void setEditorLine(const QVariant& line);

private:
  QSplitter*        spV;
  QWidget*          frame;
  OcctQtViewer*     view3D;
  bool              previewIsCenter;
  };
#endif // PWEDITOR_H
