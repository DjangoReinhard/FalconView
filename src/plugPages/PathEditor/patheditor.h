#ifndef PATHEDITOR_H
#define PATHEDITOR_H
#include <testEdit.h>
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
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "PluginPageInterface_iid" FILE "pathEditor.json")
#endif
public:
  PathEditor(QWidget* parent = nullptr);

protected:
  virtual void loadFile(const QVariant& fileName) override;
  virtual void connectSignals() override;
  virtual void fileUpdated(const QString& fileName) override;
  virtual void dirtyChanged(bool dirty) override;

private:
  void reallyLoadFile(const QVariant& fileName);
  };
#endif // PWEDITOR_H
