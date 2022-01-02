#include <pagestack.h>
#include <centerpage.h>
#include <abscenterwidget.h>
#include <guicore.h>
#include <QAction>
#include <QStackedLayout>
#include <QDebug>


PageStack::PageStack(QWidget* parent)
 : AbstractCenterWidget(parent) {
  setObjectName(tr("PageStack"));
  setLayout(new QStackedLayout);
  layout()->setContentsMargins(0, 0, 0, 0);
  }


QWidget* PageStack::createContent() {
  return nullptr;
  }


void PageStack::connectSignals() {
  }


void PageStack::updateStyles() {
  }


CenterPage* PageStack::page(const QString& name) {
//  qDebug() << "CenterView: requested page \"" << name << "\"";

  if (pagePool.contains(name)) return pagePool[name];
//  qDebug() << "CenterView: sorry - no page with name >" << name << "<";

  return nullptr;
  }


CenterPage* PageStack::activatePage(const QString& name) {
  qDebug() << "CenterView: activatePage \""  << name << "\"";

  if (pagePool.contains(name)) {
     CenterPage*     w = pagePool[name];
     QStackedLayout* l = qobject_cast<QStackedLayout*>(layout());

     if (l) {
        qDebug() << "CenterView: ok, found page [" << name << "] - gonna switch view";
        l->setCurrentWidget(w);
        curPage = name;
        if (w) {
           GuiCore().setWindowTitle(w->name().toStdString().c_str());

           return w;
           }
        }
     }
  qDebug() << "CenterView: sorry - no page for name >" << name << "<";
  dump();

  return nullptr;
  }


QString PageStack::activePage() const {
  return curPage;
  }


void PageStack::dump() const {
  qDebug() << "CenterView contains" << pagePool.size() << " pages";
  for (auto e = pagePool.constKeyValueBegin(); e != pagePool.constKeyValueEnd(); e++) {
      qDebug() << "MainView holds page >>" << e->first;
      }
  }


void PageStack::addPage(CenterPage* page, const QString& name) {
  QString pageName(name);

  if (pageName.isEmpty()) pageName = page->objectName();
  pagePool.insert(pageName, page);
  QStackedLayout* l = qobject_cast<QStackedLayout*>(layout());

  if (l) {
     l->addWidget(page);
     connect(page->viewAction(), &QAction::triggered, this, [=]() {
       GuiCore().activatePage(page->objectName());
       });
     }
  activatePage(pageName);
  }


QList<QString> PageStack::pages() const {
  return pagePool.keys();
  }


void PageStack::windowClosing(QCloseEvent* e) {
  for (auto t = pagePool.constKeyValueBegin(); t != pagePool.constKeyValueEnd(); t++) {
      t->second->closeEvent(e);
      }
  }
