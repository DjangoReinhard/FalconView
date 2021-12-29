#include <helpview.h>
#include <helpbrowser.h>
#include <helpengine.h>
#include <helpcontentwidget.h>
#include <helpkeywordwidget.h>
#include <configacc.h>
#include <core.h>
#include <QSplitter>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QDebug>


HelpView::HelpView(QWidget* parent)
 : AbstractCenterWidget(parent)
 , tb(nullptr)
 , sp(nullptr)
 , he(nullptr)
 , cw(nullptr)
 , kw(nullptr) {
  }


QWidget* HelpView::createContent() {
  tb = new HelpBrowser();
  sp = new QSplitter(Qt::Horizontal, this);
  he = new HelpEngine(Core().fileName4("helpFile"), this);
  cw = static_cast<HelpContentWidget*>(he->contentWidget());
  kw = static_cast<HelpKeywordWidget*>(he->keywordWidget());
  HelpBrowser* hb = static_cast<HelpBrowser*>(tb);

  hb->setHelpEngine(he);
  tw = new QTabWidget(sp);
  sp->addWidget(tw);
  sp->addWidget(tb);
  tw->addTab(cw, tr("Content"));
  tw->addTab(kw, tr("Keywords"));
  setLayout(new QVBoxLayout());
  layout()->addWidget(sp);
  cw->expandAll();
  hb->installEventFilter(this);
  tw->installEventFilter(this);
  cw->installEventFilter(this);
  kw->installEventFilter(this);

  return nullptr;
  }


void HelpView::connectSignals() {
  connect(tw, &QTabWidget::currentChanged, this, &HelpView::tabChanged);
  connect(cw, &QTreeWidget::currentItemChanged, this, &HelpView::contentItemChanged);
  connect(kw, &QListWidget::currentItemChanged, this, &HelpView::keywordItemChanged);
  connect(tb, &QTextBrowser::sourceChanged, this, &HelpView::sourceChanged);
  }


void HelpView::updateStyles() {
  }


void HelpView::contentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *) {
  const QString& page = current->data(1, Qt::DisplayRole).toString();

  tb->setSource(page);
  }


void HelpView::tabChanged(int index) {
  qDebug() << "HelpView::tabChanged(" << index << ")";
  }


void HelpView::sourceChanged(const QUrl& src) {
  cw->sourceChanged(src);
  kw->sourceChanged(src);
  }


void HelpView::keywordItemChanged(QListWidgetItem *current, QListWidgetItem *) {
  const QString& page = current->toolTip();

  tb->setSource(page);
  }


void HelpView::help4Keyword(const QString &keyWord) {
  QString document = he->document4Keyword(keyWord);

//  qDebug() << "\tHD: keyword >" << keyWord << "< \tpage:" << document;
  if (!document.isEmpty()) tb->setSource(document);
//  Core().setAppMode(ApplicationMode::Help);
  }


void HelpView::closeEvent(QCloseEvent*) {
  Config cfg;

  cfg.beginGroup(HelpView::className);
  cfg.setValue("state", sp->saveState());
  cfg.setValue("geometry", saveGeometry());
  cfg.endGroup();
  }


bool HelpView::eventFilter(QObject*, QEvent* event) {
  if (event->type() == QEvent::KeyPress) {
     QKeyEvent* e = static_cast<QKeyEvent*>(event);

     switch (e->key()) {
       case Qt::Key_Escape:
            //TODO: switch back
            break;
       }
     }
  return false;
  }


void HelpView::restoreState() {
  Config cfg;

  cfg.beginGroup(HelpView::className);
  sp->restoreState(cfg.value("state").toByteArray());
  restoreGeometry(cfg.value("geometry").toByteArray());
  cfg.endGroup();
  cw->setFocus();
  }

const QString& HelpView::className = "HelpView";
