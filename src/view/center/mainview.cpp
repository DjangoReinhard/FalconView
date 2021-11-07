#include <mainview.h>
#include <dynwidget.h>
#include <core.h>
#include <QAction>
#include <QDebug>
#include <QStackedLayout>


MainView::MainView(QWidget* parent)
 : QWidget(parent) {
  setObjectName(tr("MainView"));
  setLayout(new QStackedLayout);
  layout()->setContentsMargins(0, 0, 0, 0);
  }


QWidget* MainView::page(const QString& name) {
  qDebug() << "MainView: requested page \"" << name << "\"";

  if (pages.contains(name)) return pages[name];
  qDebug() << "MainView: sorry - no page with name >" << name << "<";

  return nullptr;
  }


QWidget* MainView::activatePage(const QString& name) {
  qDebug() << "MainView: activatePage \""  << name << "\"";

  if (pages.contains(name)) {
     QWidget*     w  = pages[name];
     QStackedLayout* l = qobject_cast<QStackedLayout*>(layout());

     if (l) {
        qDebug() << "MainView: ok, found page [" << name << "] - gonna switch view";
        l->setCurrentWidget(w);

        return w;
        }
     qDebug() << "MainView: sorry - no page for name >" << name << "<";
     }
  return nullptr;
  }


void MainView::dump() const {
  for (auto e = pages.constKeyValueBegin(); e != pages.constKeyValueEnd(); e++) {
      qDebug() << "MainView holds page >>" << e->first;
      }
  }


void MainView::addPage(DynWidget *page, const QString& name) {
  QString pageName(name);

  if (pageName.isEmpty()) pageName = page->objectName();
  pages.insert(pageName, page);
  QStackedLayout* l = qobject_cast<QStackedLayout*>(layout());

  if (l) {
     page->init();
     l->addWidget(page);
     connect(page->viewAction(), &QAction::triggered, this, [=]() {
       Core().activatePage(page->objectName());
       });
     }
//  activatePage(pageName);
  }
