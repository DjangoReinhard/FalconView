#ifndef GCODEVIEWER_H
#define GCODEVIEWER_H

#include "gcodeeditor.h"

class GCodeViewer : public GCodeEditor
{
  Q_OBJECT
public:
  explicit GCodeViewer(QWidget* parent = nullptr);
  virtual ~GCodeViewer();

private slots:
  void setCurrentLine(QVariant line);
  };
#endif // GCODEVIEWER_H
