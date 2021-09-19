#ifndef GCODEEDITOR_H
#define GCODEEDITOR_H

#include <QPlainTextEdit>

class LineNumberArea;


class GCodeEditor : public QPlainTextEdit
{
  Q_OBJECT
public:
  GCodeEditor(QWidget* parent = nullptr);

  void paintLineNumbers(QPaintEvent* event);
  int  lineNumberAreaWidth();
  void loadFile(QVariant fileName);

protected:
  void resizeEvent(QResizeEvent* event) override;

private slots:
  void updateLineNumberAreaWidth(int newBlockCount);
  void highlightCurrentLine();
  void updateLineNumberArea(const QRect& rect, int dy);

private:
  QWidget* lineNumberArea;
  };


class LineNumberArea : public QWidget
{
public:
  LineNumberArea(GCodeEditor *editor)
   : QWidget(editor)
   , editor(editor) {
    setFont(editor->font());
    }
  QSize sizeHint() const override {
    return QSize(editor->lineNumberAreaWidth(), 0);
    }

protected:
  void paintEvent(QPaintEvent *event) override {
    editor->paintLineNumbers(event);
    }

private:
  GCodeEditor* editor;
  };
#endif // GCODEEDITOR_H
