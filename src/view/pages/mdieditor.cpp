#include <mdieditor.h>
#include <configacc.h>
#include <QListWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <QDebug>
#include <cmath>


MDIEditor::MDIEditor(const QString& file, QWidget* parent)
 : DynCenterWidget(file, MDIEditor::className, false, parent) {
  setObjectName(MDIEditor::className);
  setWindowTitle(tr("MDIEditor"));
  }


MDIEditor::~MDIEditor() {
  }


void MDIEditor::append(const QString &command) {
  int  mx    = history->count();
  bool found = false;

  for (int i = 0; i < mx; ++i) {
      if (history->item(i)->text() == command) {
         found = true;
         break;
         }
      }
  if (!found) history->addItem(command);
  cmd->clear();
  }


void MDIEditor::closeEvent(QCloseEvent*) {
  Config cfg;
  QStringList sl;
  int mx = history->count();

  for (int i = fmax(0, mx - 50); i < mx; ++i)
      sl.append(history->item(i)->text());

  cfg.beginGroup(MDIEditor::className);
  cfg.setValue("history", sl);
  cfg.endGroup();
  }

QString MDIEditor::command() const {
  return cmd->text().toUpper().replace(",", ".");
  }


QWidget* MDIEditor::createContent() {
  QWidget* rv = DynCenterWidget::createContent();

  history = rv->findChild<QListWidget*>("history");
  cmd     = rv->findChild<QLineEdit*>("command");
  Config cfg;

  history->installEventFilter(this);
  cmd->installEventFilter(this);
  cfg.beginGroup(MDIEditor::className);
  QStringList sl = cfg.value("history").toStringList();
  cfg.endGroup();

  for (const QString& s : sl) {
      qDebug() << "history command: " << s;

      history->addItem(s);
      }
  if (history->count() < 1) createTestData();

  return rv;
  }


void MDIEditor::createTestData() {
  for (int i=0; !testData[i].isEmpty(); ++i) {
      history->addItem(testData[i]);
      }
  }


void MDIEditor::connectSignals() {
  connect(history->selectionModel(), &QItemSelectionModel::currentChanged, this, &MDIEditor::currentChanged);
  }


void MDIEditor::currentChanged(const QModelIndex& current, const QModelIndex&) {
//  qDebug() << "currentChanged" << current;
  cmd->setText(history->item(current.row())->text());
  }


bool MDIEditor::eventFilter(QObject*, QEvent* event) {
  if (event->type() == QEvent::KeyPress) {
     QKeyEvent* e = static_cast<QKeyEvent*>(event);

     switch (e->key()) {
       case Qt::Key_Up:
            history->setCurrentRow(history->currentRow() > 0
                                 ? history->currentRow() - 1 : 0);
            return true;
       case Qt::Key_Down:
            history->setCurrentRow(history->currentRow() < (history->count() - 1)
                                 ? history->currentRow() + 1 : history->count() - 1);
            return true;
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            return true;
       }
     }
  return false;
  }


void MDIEditor::showEvent(QShowEvent* e) {
  if (e->type() == QEvent::Show) cmd->setFocus();
  }


void MDIEditor::updateStyles() {
  }

const QString MDIEditor::className = "MDIEditor";
const QString MDIEditor::testData[] = {
  "T1 M6"
, "S400 M3"
, "F100"
, "G21 G40 G80"
, "T3 M6"
, "T6 M6"
, "G0 G90 G54 X0 Y0"
, ""
  };
