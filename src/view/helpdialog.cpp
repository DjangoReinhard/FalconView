#include <configacc.h>
#include <helpdialog.h>
#include <htmlbrowser.h>
#include <helpengine.h>
#include <helpcontentwidget.h>
#include <helpkeywordwidget.h>
#include <core.h>
#include <QDebug>
#include <QPainter>
#include <QBitmap>
#include <QShowEvent>
#include <QTabWidget>
#include <QSplitter>


HelpDialog::HelpDialog(QWidget* parent)
 : QDockWidget(tr("Help"), parent)
 , sp(new QSplitter(Qt::Horizontal, this))
 , he(new HelpEngine(Core().helpFilename(), this))
 , tb(new HTMLBrowser(*he))
 , cw(static_cast<HelpContentWidget*>(he->contentWidget()))
 , kw(static_cast<HelpKeywordWidget*>(he->keywordWidget())) {
  setObjectName("HelpDialog");
  tb->setMinimumWidth(830);
  setMinimumWidth(1100);
  QTabWidget* tw = new QTabWidget(sp);

  sp->addWidget(tw);
  sp->addWidget(tb);
  tw->addTab(cw, tr("Content"));
  tw->addTab(kw, tr("Keywords"));
  setWidget(sp);
  cw->expandAll();
  setTitleBarWidget(new HelpTitleBar(this));
  connect(cw, &QTreeWidget::currentItemChanged, this, &HelpDialog::contentItemChanged);
  connect(kw, &QListWidget::currentItemChanged, this, &HelpDialog::keywordItemChanged);
  }


void HelpDialog::contentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *) {
  const QString& page = current->data(1, Qt::DisplayRole).toString();

  tb->setSource(page);
  }


void HelpDialog::keywordItemChanged(QListWidgetItem *current, QListWidgetItem *) {
  const QString& page = current->toolTip();

  tb->setSource(page);
  }


void HelpDialog::keyPressEvent(QKeyEvent* e) {
  qDebug() << "HelpDLG: pressed key: " << e->key()
           << "modifiers: "   << e->modifiers()
           << "event-ts: " << e->timestamp();
  switch (e->key()) {
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
 , title(new Ui::HelpTitle) {
  title->setupUi(this);
  layout()->setContentsMargins(0, 0, 0, 0);
  setStyleSheet("background: #4D565E;");
  }


QSize HelpTitleBar::minimumSizeHint() const {
  return QSize(1100, 40);
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
