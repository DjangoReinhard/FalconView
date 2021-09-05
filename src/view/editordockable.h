#ifndef EDITORDOCKABLE_H
#define EDITORDOCKABLE_H
#include <dockable.h>
class QFile;
class GCodeEditor;
class GCodeHighlighter;
class QLineEdit;


class EditorDockable : public Dockable
{
  Q_OBJECT
public:
  EditorDockable(const QString& fileName, QWidget* parent = nullptr);
  virtual ~EditorDockable();

public slots:
  void loadFile();
  void loadFileAlt();

protected:
  void initializeWidget();

private:
  GCodeEditor*      editor;
  QLineEdit*        fileName;
  GCodeHighlighter* gh;
  };

#endif // EDITORDOCKABLE_H
