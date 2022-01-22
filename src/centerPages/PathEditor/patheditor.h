#ifndef PATHEDITOR_H
#define PATHEDITOR_H
#include <testEdit.h>
#include <CenterPageInterface.h>
class PreViewEditor;
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
  Q_INTERFACES(CenterPageInterface)
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "CenterPageInterface_iid" FILE "pathEditor.json")
#endif
public:
  PathEditor(QWidget* parent = nullptr);

protected:
  virtual void     closeEvent(QCloseEvent* e) override;
  virtual QWidget* createContent() override;
  virtual void     loadFile(const QVariant& fileName) override;
  virtual void     connectSignals() override;
  virtual void     fileUpdated(const QString& fileName) override;
  virtual void     dirtyChanged(bool dirty) override;
  virtual void     showEvent(QShowEvent* e) override;
  virtual void     updateStyles() override;
  virtual QAction* viewAction() override;

private:
  void reallyLoadFile(const QVariant& fileName) override;
  };
#endif // PATHEDITOR_H
