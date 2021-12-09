#ifndef DYNCENTERWIDGET_H
#define DYNCENTERWIDGET_H
#include <QWidget>
class CenterView;
class SettingsNotebook;
class QString;
class QWidget;
class QAction;
class QFile;


/*! loads widgets from uiFile and allows late initialization at page usage
 */
class DynCenterWidget : public QWidget
{
  Q_OBJECT
public:
  void     initialize();  // offline initialization!
  QAction* viewAction();

  // called by central widget stack
  virtual void closeEvent(QCloseEvent* e) override;
  virtual void keyPressEvent(QKeyEvent* e) override;
  virtual void keyReleaseEvent(QKeyEvent* e) override;
  virtual void showEvent(QShowEvent* e) override;

signals:
  void dataChanged(DynCenterWidget* w, const QVariant& changed);

protected:
  DynCenterWidget(const QString& fileName, const QString& name, bool addScrollArea = false, QWidget* parent = nullptr);

  virtual QWidget* createContent();  // default: load content from given filename
  virtual void connectSignals() = 0; // called by initialize
  virtual void updateStyles()   = 0; // called by initialize

private:
  QAction*     vAction;
  QString      fileName;
  bool         addScrollArea;
  };
#endif // DYNCENTERWIDGET_H
