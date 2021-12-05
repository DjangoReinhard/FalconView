#include <mdieditor.h>
#include <QVBoxLayout>
#include <QListWidget>
#include <QScrollArea>
#include <QLineEdit>
#include <QWidget>


MDIEditor::MDIEditor(const QString& file, QWidget* parent)
 : DynCenterWidget(file, MDIEditor::className, false, parent) {
  setObjectName(MDIEditor::className);
  setWindowTitle(tr("MDIEditor"));
  }


MDIEditor::~MDIEditor() {
  }


void MDIEditor::connectSignals() {
  }


void MDIEditor::updateStyles() {
  }

const QString MDIEditor::className = "MDIEditor";
