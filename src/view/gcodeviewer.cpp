#include <gcodeviewer.h>
#include <valuemanager.h>
#include <QVariant>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocument>
#include <QDebug>
#include <cmath>


GCodeViewer::GCodeViewer(QWidget* parent)
 : GCodeEditor(parent) {
//  setReadOnly(true);
  this->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  ValueManager vm;

  connect(vm.getModel("curLine", 0), &ValueModel::valueChanged, this, &GCodeViewer::setCurrentLine);
//  connect(vm.getModel("fileName", " "), &ValueModel::valueChanged, this, &GCodeEditor::loadFile);
  }


GCodeViewer::~GCodeViewer() {
  }


void GCodeViewer::setCurrentLine(QVariant line) {
  QTextDocument* d  = document();
  QTextBlock     b0 = d->findBlockByLineNumber(fmax(0, line.toInt() - 2));
  QTextBlock     b1 = d->findBlockByLineNumber(line.toInt() - 1);
  QTextCursor    c0(b0);
  QTextCursor    c1(b1);

  qDebug() << "GCV::setCurrentLine(" << line << ")";
  moveCursor(QTextCursor::End);
  setTextCursor(c0);
  setTextCursor(c1);
  }
