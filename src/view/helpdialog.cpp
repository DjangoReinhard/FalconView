#include <helpdialog.h>
#include <helpbrowser.h>
#include <core.h>
#include <QDebug>
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
  QTabWidget*  tControl      = new QTabWidget;

  if (!helpEngine->setupData()) {
    qDebug() << "HelpDialog: failed to setup help engine! helpFile: " << Core().helpFilename();
    delete helpEngine;
    delete horizSplitter;
    delete tControl;
    helpEngine = 0;
    tControl = 0;
    horizSplitter = 0;

    return;
    }
  else qDebug() << "HelpDialog: help engine should work now ...";
  tControl->setMaximumWidth(200);
  tControl->addTab(helpEngine->contentWidget(), tr("Contents"));
  tControl->addTab(helpEngine->indexWidget(),   tr("Index"));

  HelpBrowser* textViewer = new HelpBrowser(helpEngine);

  textViewer->setSource(QUrl("qthelp://de.schwarzrot.falconview.0.1/FalconView/startup.html"));
  connect(helpEngine->contentWidget(), SIGNAL(linkActivated(QUrl))
        , textViewer, SLOT(setSource(QUrl)));
  connect(helpEngine->indexWidget(), SIGNAL(linkActivated(QUrl))
        , textViewer, SLOT(setSource(QUrl)));

  horizSplitter->insertWidget(0, tControl);
  horizSplitter->insertWidget(1, textViewer);
  horizSplitter->hide();

  setWidget(horizSplitter);
//  hide();
  }
