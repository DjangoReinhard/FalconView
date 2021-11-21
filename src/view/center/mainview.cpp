#include <mainview.h>
#define WANT_STACKED_LAYOUT
#include <dynwidget.h>
#include <core.h>
#include <QAction>
#include <QDebug>
#ifdef WANT_STACKED_LAYOUT
# include <QStackedLayout>
#else
# include <QGridLayout>
#endif


MainView::MainView(QWidget* parent)
 : QWidget(parent) {
  setObjectName(tr("MainView"));
#ifdef WANT_STACKED_LAYOUT
  setLayout(new QStackedLayout);
#else
  setLayout(new QGridLayout);
#endif
  layout()->setContentsMargins(0, 0, 0, 0);
  }


QWidget* MainView::page(const QString& name) {
//  qDebug() << "MainView: requested page \"" << name << "\"";

  if (pages.contains(name)) return pages[name];
//  qDebug() << "MainView: sorry - no page with name >" << name << "<";

  return nullptr;
  }


QWidget* MainView::activatePage(const QString& name) {
//  qDebug() << "MainView: activatePage \""  << name << "\"";

  if (pages.contains(name)) {
     QWidget*     w  = pages[name];
#ifdef WANT_STACKED_LAYOUT
     QStackedLayout* l = qobject_cast<QStackedLayout*>(layout());
#else
     QGridLayout*    l = qobject_cast<QGridLayout*>(layout());
#endif

     if (l) {
//        qDebug() << "MainView: ok, found page [" << name << "] - gonna switch view";
#ifdef WANT_STACKED_LAYOUT
        l->setCurrentWidget(w);
#else
        w->setVisible(true);
        for (auto k = pages.keyBegin(); k != pages.keyEnd(); ++k) {
            if (!k->compare(name)) continue;
            pages[*k]->setVisible(false);
            }
        w->repaint();
#endif
        curPage = name;

        return w;
        }
     qDebug() << "MainView: sorry - no page for name >" << name << "<";
     }
  return nullptr;
  }


const QString& MainView::activePage() const {
  return curPage;
  }


void MainView::dump() const {
//  for (auto e = pages.constKeyValueBegin(); e != pages.constKeyValueEnd(); e++) {
//      qDebug() << "MainView holds page >>" << e->first;
//      }
  }


void MainView::addPage(DynWidget *page, const QString& name) {
  QString pageName(name);

  if (pageName.isEmpty()) pageName = page->objectName();
  pages.insert(pageName, page);
#ifdef WANT_STACKED_LAYOUT
  QStackedLayout* l = qobject_cast<QStackedLayout*>(layout());
#else
  QGridLayout*    l = qobject_cast<QGridLayout*>(layout());
#endif

  if (l) {
     page->init();
     l->addWidget(page
#ifndef WANT_STACKED_LAYOUT
                , 0, 0
#endif
                 );
     connect(page->viewAction(), &QAction::triggered, this, [=]() {
       Core().activatePage(page->objectName());
       });
     }
  activatePage(pageName);
  }


void MainView::windowClosing(QCloseEvent* e) {
  for (auto t = pages.constKeyValueBegin(); t != pages.constKeyValueEnd(); t++) {
      t->second->closeEvent(e);
      }
  }
