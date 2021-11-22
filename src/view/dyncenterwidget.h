#ifndef DYNCENTERWIDGET_H
#define DYNCENTERWIDGET_H
#include <QWidget>
class MainView;
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
  void     initialize();
  QAction* viewAction();

  /*! called by central widget stack */
  virtual void closeEvent(QCloseEvent* e);

protected:
  DynCenterWidget(const QString& fileName, const QString& name, bool addScrollArea = false, QWidget* parent = nullptr);

  /*! default is: load content from given filename - will be called from initialize */
  virtual QWidget* createContent();

  /*! connect signals/slots offline - called by addPage */
  virtual void connectSignals() = 0;

  /*! style the child widgets offline - called by addPage */
  virtual void updateStyles()   = 0;

private:
  QAction*     vAction;
  QString      fileName;
  bool         addScrollArea;
//  friend class SettingsNotebook;
  };
#endif // DYNCENTERWIDGET_H
