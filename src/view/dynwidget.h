#ifndef DYNWIDGET_H
#define DYNWIDGET_H
#include <QFrame>
class MainView;
class SettingsNotebook;
class QString;
class QWidget;
class QAction;
class QFile;


/*! loads widgets from uiFile and allows late initialization at page usage
 */
class DynWidget : public QFrame // QWidget
{
  Q_OBJECT
public:
  DynWidget(QWidget* parent = nullptr) : QFrame(parent), vAction(nullptr) {};

  void         init();
  QAction*     viewAction();

protected:
  DynWidget(const QString& fileName, bool addScrollArea = false, QWidget* parent = nullptr);

  /*! connect signals/slots offline - called by addPage */
  virtual void connectSignals() = 0;
  /*! called by MainView at application shutdown */
  virtual void closeEvent(QCloseEvent *event) override;

  /*! style the child widgets offline - called by addPage */
  virtual void updateStyles()   = 0;
  QWidget*     loadFromUI(QFile& uiFile);
  QWidget*     w;

private:
  QAction*     vAction;
  friend class MainView;
  friend class SettingsNotebook;
  };
#endif // DYNWIDGET_H
