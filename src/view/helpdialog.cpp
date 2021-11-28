#include <helpdialog.h>
#include <helpbrowser.h>
#include <core.h>
#include <QTabWidget>
#include <QSplitter>
#include <QHelpEngine>
#include <QHelpIndexWidget>
#include <QHelpContentWidget>


HelpDialog::HelpDialog(QWidget* parent)
 : QDockWidget(tr("Help"), parent) {
  setObjectName("HelpDialog");
  }


void HelpDialog::init() {
  QHelpEngine* helpEngine    = new QHelpEngine(Core().helpFilename());
  QSplitter*   horizSplitter = new QSplitter(Qt::Horizontal);
  QTabWidget*  tWidget       = new QTabWidget;

  helpEngine->setupData();
  tWidget->setMaximumWidth(200);
  tWidget->addTab(helpEngine->contentWidget(), tr("Contents"));
  tWidget->addTab(helpEngine->indexWidget(),   tr("Index"));

  HelpBrowser* textViewer = new HelpBrowser(helpEngine);

  textViewer->setSource(QUrl("qthelp://de.schwarzrot.falconview.0.1/startup.html"));
  connect(helpEngine->contentWidget(), SIGNAL(linkActivated(QUrl,QString))
        , textViewer, SLOT(setSource(QUrl,QString)));
  connect(helpEngine->indexWidget(), SIGNAL(linkActivated(QUrl,QString))
        , textViewer, SLOT(setSource(QUrl,QString)));

  horizSplitter->insertWidget(0, tWidget);
  horizSplitter->insertWidget(1, textViewer);
  horizSplitter->hide();

  setWidget(horizSplitter);
  hide();
  }
