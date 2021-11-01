#include <gcodeeditor.h>
#include <configacc.h>
#include <valuemanager.h>
#include <QPainter>
#include <QTextBlock>
#include <QScrollBar>
#include <QFile>
#include <QDebug>


GCodeEditor::GCodeEditor(QWidget* parent)
 : QPlainTextEdit(parent) {
  lineNumberArea = new LineNumberArea(this);

  connect(this, &GCodeEditor::blockCountChanged,     this, &GCodeEditor::updateLineNumberAreaWidth);
  connect(this, &GCodeEditor::updateRequest,         this, &GCodeEditor::updateLineNumberArea);
  connect(this, &GCodeEditor::cursorPositionChanged, this, &GCodeEditor::highlightCurrentLine); 

  updateLineNumberAreaWidth(0);
  highlightCurrentLine();
  }


int GCodeEditor::lineNumberAreaWidth() {
  int digits = 1;
  int max = qMax(1, document()->blockCount());

  while (max >= 10) {
        max /= 10;
        ++digits;
        }
  int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

  return space;
  }


void GCodeEditor::updateLineNumberAreaWidth(int /* bc */) {
  setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
  }


void GCodeEditor::updateLineNumberArea(const QRect& rect, int dy) {
  if (dy) lineNumberArea->scroll(0, dy);
  else    lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

  if (rect.contains(viewport()->rect()))
     updateLineNumberAreaWidth(0);
  }


void GCodeEditor::resizeEvent(QResizeEvent *e) {
  QPlainTextEdit::resizeEvent(e);
  QRect cr = contentsRect();

  lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
  }


void GCodeEditor::loadFile(QVariant name) {
  QFile file(name.toString());

  if (file.open(QFile::ReadOnly | QFile::Text))
     setPlainText(file.readAll());
  }


void GCodeEditor::highlightCurrentLine() {
  QList<QTextEdit::ExtraSelection> extraSelections;
  QTextEdit::ExtraSelection selection;
  QColor bgHLLine = ValueManager().getValue("cfgBg" + Config().nameOf(Config::GuiElem::LineHL)).value<QColor>();
  QColor fgHLLine = ValueManager().getValue("cfgFg" + Config().nameOf(Config::GuiElem::LineHL)).value<QColor>();
//  QColor lineColor = QColor(Qt::yellow).lighter(140);

  selection.format.setBackground(bgHLLine);
  selection.format.setForeground(fgHLLine);
  selection.format.setProperty(QTextFormat::FullWidthSelection, true);
  selection.cursor = textCursor();
  selection.cursor.clearSelection();
  extraSelections.append(selection);
  setExtraSelections(extraSelections);
  }


void GCodeEditor::paintLineNumbers(QPaintEvent *e) {    
  QPainter painter(lineNumberArea);
  QColor   bgLineNum = ValueManager().getValue("cfgBg" + Config().nameOf(Config::GuiElem::EdLinNum)).value<QColor>();
  QColor   fgLineNum = ValueManager().getValue("cfgFg" + Config().nameOf(Config::GuiElem::EdLinNum)).value<QColor>();

//  painter.fillRect(e->rect(), QColor(239, 240, 241));
  painter.fillRect(e->rect(), bgLineNum);
  painter.setFont(font());
  QTextBlock block    = firstVisibleBlock();        // lines == block
  int        blockNum = block.blockNumber();
  int        top      = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
  int        bottom   = top + qRound(blockBoundingRect(block).height());

  while (block.isValid() && top <= e->rect().bottom()) {
        if (block.isVisible() && bottom >= e->rect().top()) {
           QString lineNum = QString::number(blockNum + 1);

           painter.setPen(fgLineNum);
           painter.drawText(0
                          , top
                          , lineNumberArea->width()
                          , fontMetrics().height()
                          , Qt::AlignRight
                          , lineNum);
           }
        block  = block.next();
        top    = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNum;
        }
  }
