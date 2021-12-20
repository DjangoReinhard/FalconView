#include <configacc.h>
#include <helpdialog.h>
#include <helpbrowser.h>
#include <helpengine.h>
#include <helpcontentwidget.h>
#include <helpkeywordwidget.h>
#include <core.h>
#include <QPainter>
#include <QBitmap>
#include <QShowEvent>
#include <QTabWidget>
#include <QSplitter>
#include <QDebug>


HelpDialog::HelpDialog(QWidget* parent)
 : QDockWidget(tr("Help"), parent)
 , tb(new HelpBrowser)
 , sp(new QSplitter(Qt::Horizontal, this))
 , he(new HelpEngine(Core().helpFilename(), this))
 , cw(static_cast<HelpContentWidget*>(he->contentWidget()))
 , kw(static_cast<HelpKeywordWidget*>(he->keywordWidget())) {
  setObjectName("HelpDialog");
  HelpBrowser* hb = static_cast<HelpBrowser*>(tb);

  hb->setHelpEngine(he);
  hb->setMinimumWidth(830);
  setMinimumWidth(1100);

  tw = new QTabWidget(sp);
  sp->addWidget(tw);
  sp->addWidget(tb);
  tw->addTab(cw, tr("Content"));
  tw->addTab(kw, tr("Keywords"));
  setWidget(sp);
  cw->expandAll();
  setTitleBarWidget(new HelpTitleBar(this));
  connect(tw, &QTabWidget::currentChanged, this, &HelpDialog::tabChanged);
  connect(cw, &QTreeWidget::currentItemChanged, this, &HelpDialog::contentItemChanged);
  connect(kw, &QListWidget::currentItemChanged, this, &HelpDialog::keywordItemChanged);
  connect(tb, &QTextBrowser::sourceChanged, this, &HelpDialog::sourceChanged);
  }


void HelpDialog::contentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *) {
  const QString& page = current->data(1, Qt::DisplayRole).toString();

  tb->setSource(page);
  }


void HelpDialog::tabChanged(int index) {
  qDebug() << "HelpDialog::tabChanged(" << index << ")";
  }


void HelpDialog::sourceChanged(const QUrl& src) {
  HelpTitleBar* htb = static_cast<HelpTitleBar*>(this->titleBarWidget());
  int           index = tw->currentIndex();

//  qDebug() << "HelpDialog::sourceChanged - #" << index
//           << ":" << tb->documentTitle()
//           << " - src:" << src;

  cw->sourceChanged(src);
  kw->sourceChanged(src);
  if (htb) htb->setTitle(tb->documentTitle());
  }


void HelpDialog::keywordItemChanged(QListWidgetItem *current, QListWidgetItem *) {
  const QString& page = current->toolTip();

  tb->setSource(page);
  }


void HelpDialog::help4Keyword(const QString &keyWord) {
  QString document = he->document4Keyword(keyWord);

//  qDebug() << "\tHD: keyword >" << keyWord << "< \tpage:" << document;
  if (!document.isEmpty()) tb->setSource(document);
  showHelp();
  }


void HelpDialog::keyPressEvent(QKeyEvent* e) {
//  qDebug() << "HelpDLG: pressed key: " << e->key()
//           << "modifiers: "   << e->modifiers()
//           << "event-ts: " << e->timestamp();
  switch (e->key()) {
    case Qt::Key_Escape:
         close();
         break;
    case Qt::Key_Right:
    case Qt::Key_Left:
    case Qt::Key_Up:
    case Qt::Key_Down:
         break;
    default:
         QDockWidget::keyPressEvent(e);
         break;
    }
  }


void HelpDialog::closeEvent(QCloseEvent*) {
  Config cfg;

  cfg.beginGroup(HelpDialog::className);
  cfg.setValue("state", sp->saveState());
  cfg.setValue("geometry", saveGeometry());
  cfg.endGroup();
  }


void HelpDialog::showHelp() {
  if (!isFloating()) setFloating(true);
  QDockWidget::show();  
  Config cfg;

  cfg.beginGroup(HelpDialog::className);
  sp->restoreState(cfg.value("state").toByteArray());
  restoreGeometry(cfg.value("geometry").toByteArray());
  cfg.endGroup();
  raise();
  activateWindow();
  cw->setFocus();
  }


HelpTitleBar::HelpTitleBar(QWidget *parent)
 : QWidget(parent)
 , titleBar(new Ui::HelpTitle) {
  titleBar->setupUi(this);
  layout()->setContentsMargins(0, 0, 0, 0);
  setStyleSheet("background: #4D565E;");
  }


QSize HelpTitleBar::minimumSizeHint() const {
  return QSize(1100, 40);
  }


void HelpTitleBar::setTitle(const QString &title) {
//  qDebug() << "Help - Titlebar::setTitle(" << title << ")";
  this->titleBar->title->setText(title);
  }


void HelpTitleBar::mouseReleaseEvent(QMouseEvent* e) {
  QPoint       pos  = e->pos();
  QRect        rect = this->rect();
  QDockWidget* dw   = qobject_cast<QDockWidget*>(parentWidget());
  Q_ASSERT(dw);

  const int buttonRight = 5;
  const int buttonWidth = 32;
  int right  = rect.right() - pos.x();
  int button = (right - buttonRight)/buttonWidth;

  switch (button) {
    case 0:
         e->accept();
         dw->close();
         break;
    default:
         e->ignore();
         break;
    }
  }


const QString& HelpDialog::className = "HelpDialog";
