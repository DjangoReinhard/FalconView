#ifndef EDITORDOCKABLE_H
#define EDITORDOCKABLE_H
#include <dockable.h>
#include <QVariant>
class QFile;
class GCodeEditor;
class GCodeViewer;
class GCodeHighlighter;
class QLineEdit;


class EditorDockable : public Dockable
{
  Q_OBJECT
public:
  EditorDockable(const QString& fileName, QWidget* parent = nullptr);
  virtual ~EditorDockable();

public slots:
  void openFile();
  void setLine(QVariant line);

protected:
  void initializeWidget();
//void loadFile(QVariant fileName);

private:
  GCodeViewer*      editor;
  QLineEdit*        fileName;
  GCodeHighlighter* gh;
  };

#endif // EDITORDOCKABLE_H
