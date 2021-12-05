#ifndef MDIEDITOR_H
#define MDIEDITOR_H

#include <dyncenterwidget.h>

class MDIEditor : public DynCenterWidget
{
  Q_OBJECT
public:
  static const QString className;
  explicit MDIEditor(const QString& file, QWidget* parent = nullptr);
  virtual ~MDIEditor();

  virtual void connectSignals() override;
  virtual void updateStyles() override;

private:
  };
#endif // MDIEDITOR_H
