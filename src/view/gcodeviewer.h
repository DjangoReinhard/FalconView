#ifndef GCODEVIEWER_H
#define GCODEVIEWER_H

#include "gcodeeditor.h"

class GCodeViewer : public GCodeEditor
{
  Q_OBJECT
public:
  GCodeViewer(QWidget* parent = nullptr);

private slots:
  void setCurrentLine(QVariant line);
  };
#endif // GCODEVIEWER_H
