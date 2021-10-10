#include <mainview.h>
#include <QStackedLayout>


MainView::MainView(QWidget* parent)
 : QWidget(parent) {
  setLayout(new QStackedLayout);
  }


void MainView::activatePage(const QString& name) {
  if (pages.contains(name)) {
     QWidget* w = pages[name];
     QStackedLayout* sl = static_cast<QStackedLayout*>(layout());

     if (sl) {
        sl->setCurrentWidget(w);
        }
     }
  }

void MainView::addPage(const QString& name, QWidget *page) {
  pages.insert(name, page);
  layout()->addWidget(page);
  }
