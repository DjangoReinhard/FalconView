#ifndef EDITORDOCKABLE_H
#define EDITORDOCKABLE_H
#include <dockable.h>
#include <QVariant>
class QFile;
class GCodeEditor;
class GCodeViewer;
class GCodeHighlighter;
class QPushButton;
class QLineEdit;


class EditorDockable : public Dockable
{
  Q_OBJECT
public:
  EditorDockable(const QString& fileName, QWidget* parent = nullptr);
  virtual ~EditorDockable();

public slots:
  void openFile();
//  void setLine(QVariant line);

protected:
  void initializeWidget();
  void connectSignals();
  void updateStyles();

private:
  GCodeEditor*      editor;
  QLineEdit*        fileName;
  QPushButton*      pbOpen;
  GCodeHighlighter* gh;
  };

#endif // EDITORDOCKABLE_H
