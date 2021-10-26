#include <mainview.h>
#include <dynwidget.h>
#include <QAction>
#include <QGridLayout>
//#include <QStackedLayout>


MainView::MainView(QWidget* parent)
 : QWidget(parent) {
  setLayout(new QGridLayout);
  }


void MainView::activatePage(const QString& name) {
  if (pages.contains(name)) {
     QWidget*     w  = pages[name];
     QGridLayout* gl = static_cast<QGridLayout*>(layout());

     if (gl) {
        w->setVisible(true);
        for (auto k = pages.keyBegin(); k != pages.keyEnd(); ++k) {
            if (!k->compare(name)) continue;
            pages[*k]->setVisible(false);
            }
        w->repaint();
        }
     }
  }


void MainView::addPage(const QString& name, DynWidget *page) {
  pages.insert(name, page);
  QGridLayout* gl = static_cast<QGridLayout*>(layout());

  if (gl) {
     gl->addWidget(page, 0, 0);
     connect(page->viewAction(), &QAction::triggered, this, [=]() {
       activatePage(page->objectName());
       });
     }
  activatePage(name);
  }
