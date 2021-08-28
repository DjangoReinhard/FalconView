#ifndef EDITORDOCKABLE_H
#define EDITORDOCKABLE_H
#include <QDockWidget>
class QFile;
class QTextEdit;
class GCodeHighlighter;
class QLineEdit;


class EditorDockable : public QDockWidget
{
  Q_OBJECT
public:
  EditorDockable(QFile& uiDesc, QWidget* parent = nullptr);
  virtual ~EditorDockable();

public slots:
  void loadFile();

protected:
  void initializeWidget(QFile& uiDesc);

private:
  QTextEdit*        editor;
  QLineEdit*        fileName;
  GCodeHighlighter* gh;
  };

#endif // EDITORDOCKABLE_H
