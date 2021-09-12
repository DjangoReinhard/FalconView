#include <maindockable.h>
#include <QFrame>
#include <QStackedLayout>


MainDockable::MainDockable(QWidget* parent)
 : QDockWidget(tr("Main-Dockable"), parent) {
  setObjectName("Main-Dockable");
  QFrame* frame = new QFrame(this);

  layout = new QStackedLayout(frame);
  frame->setLayout(layout);
  setWidget(frame);
  }


int MainDockable::addPage(const QString& name, QWidget* page) {
  if (!page) return -1;
  page->setObjectName(name);

  return layout->addWidget(page);
  }
