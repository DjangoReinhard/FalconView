#include <mainview.h>
#include <dynwidget.h>
#include <QAction>
#include <QDebug>
#include <QGridLayout>
//#include <QStackedLayout>


MainView::MainView(QWidget* parent)
 : QWidget(parent) {
  setLayout(new QGridLayout);
  layout()->setContentsMargins(0, 0, 0, 0);
  qDebug() << "mainView has margins:" << layout()->contentsMargins();
  }


QWidget* MainView::page(const QString& name) {
  qDebug() << "request page \"" << name << "\"";

  if (pages.contains(name)) return pages[name];
  return nullptr;
  }


QWidget* MainView::activatePage(const QString& name) {
  qDebug() << "activatePage \""  << name << "\"";

  if (pages.contains(name)) {
     QWidget*     w  = pages[name];
     QGridLayout* gl = qobject_cast<QGridLayout*>(layout());

     if (gl) {
        qDebug() << "ok, found widget. Gonna switch view";
        w->setVisible(true);
        for (auto k = pages.keyBegin(); k != pages.keyEnd(); ++k) {
            if (!k->compare(name)) continue;
            pages[*k]->setVisible(false);
            }
        w->repaint();

        return w;
        }
     }
  return nullptr;
  }


void MainView::addPage(const QString& name, DynWidget *page) {
  pages.insert(name, page);
  QGridLayout* gl = qobject_cast<QGridLayout*>(layout());

  if (gl) {
     page->init();
     gl->addWidget(page, 0, 0);     
     connect(page->viewAction(), &QAction::triggered, this, [=]() {
       activatePage(page->objectName());
       });
     }
  activatePage(name);
  }
