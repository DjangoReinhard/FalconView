#include <centerview.h>
#include <dynframe.h>
#include <dyncenterwidget.h>
#include <core.h>
#include <QAction>
#include <QStackedLayout>
#include <QDebug>


CenterView::CenterView(QWidget* parent)
 : DynCenterWidget(QString(), "PageStack", false, parent) {
  setObjectName(tr("PageStack"));
  setLayout(new QStackedLayout);
  layout()->setContentsMargins(0, 0, 0, 0);
  }


QWidget* CenterView::createContent() {
  return nullptr;
  }


void CenterView::connectSignals() {
  }


void CenterView::updateStyles() {
  }


DynFrame* CenterView::page(const QString& name) {
//  qDebug() << "CenterView: requested page \"" << name << "\"";

  if (pages.contains(name)) return pages[name];
//  qDebug() << "CenterView: sorry - no page with name >" << name << "<";

  return nullptr;
  }


DynFrame* CenterView::activatePage(const QString& name) {
  qDebug() << "CenterView: activatePage \""  << name << "\"";

  if (pages.contains(name)) {
     DynFrame*       w = pages[name];
     QStackedLayout* l = qobject_cast<QStackedLayout*>(layout());

     if (l) {
        qDebug() << "CenterView: ok, found page [" << name << "] - gonna switch view";
        l->setCurrentWidget(w);
        curPage = name;
        if (w) {
           Core().setWindowTitle(w->name().toStdString().c_str());

           return w;
           }
        }
     }
  qDebug() << "CenterView: sorry - no page for name >" << name << "<";
  dump();

  return nullptr;
  }


QString CenterView::activePage() const {
  return curPage;
  }


void CenterView::dump() const {
  qDebug() << "CenterView contains" << pages.size() << " pages";
  for (auto e = pages.constKeyValueBegin(); e != pages.constKeyValueEnd(); e++) {
      qDebug() << "MainView holds page >>" << e->first;
      }
  }


void CenterView::addPage(DynFrame* page, const QString& name) {
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
  activatePage(pageName);
  }


void CenterView::keyPressEvent(QKeyEvent *e) {
//  qDebug() << "CenterView::keyPressEvent ...";
  pages[curPage]->keyPressEvent(e);
  }


void CenterView::keyReleaseEvent(QKeyEvent *e) {
//  qDebug() << "CenterView::keyReleaseEvent ...";
  pages[curPage]->keyReleaseEvent(e);
  }


void CenterView::windowClosing(QCloseEvent* e) {
  for (auto t = pages.constKeyValueBegin(); t != pages.constKeyValueEnd(); t++) {
      t->second->closeEvent(e);
      }
  }
