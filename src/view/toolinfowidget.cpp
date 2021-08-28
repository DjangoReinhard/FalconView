#include "toolinfowidget.h"
#include "labeladapter.h"
#include <QUiLoader>
#include <QFile>
#include <QLabel>
#include <QResizeEvent>
#include <QDebug>


ToolInfoWidget::ToolInfoWidget(QFile& uiDesc, QWidget* parent)
 : QDockWidget(tr("ToolInfo"), parent)
 , tlCur(nullptr)
 , tlDesc(nullptr)
 , tlLen(nullptr)
 , tlRad(nullptr)
 , tlNext(nullptr)
 , height(-1) {
  initializeWidget(uiDesc);
  }


ToolInfoWidget::~ToolInfoWidget() {
  delete tlCur;
  delete tlDesc;
  delete tlLen;
  delete tlRad;
  delete tlNext;
  }


void ToolInfoWidget::initializeWidget(QFile &uiDesc) {
  QUiLoader loader;
  QWidget*  w = loader.load(&uiDesc, this);

  uiDesc.close();
  setWidget(w);

  tlCur  = new LabelAdapter(findChild<QLabel*>("curToolNum"));
  tlDesc = new LabelAdapter(findChild<QLabel*>("toolDesc"));
  tlLen  = new LabelAdapter(findChild<QLabel*>("toolLen"));
  tlRad  = new LabelAdapter(findChild<QLabel*>("toolRadius"));
  tlNext = new LabelAdapter(findChild<QLabel*>("nextToolNum"));
  }


void ToolInfoWidget::resizeEvent(QResizeEvent* /* e */) {
    /*
  int h = e->size().height();

  if (h == height) return;
  height = h;
  QSize size = widget()->size();
  int ns = int((double)size.height() / 5.8);
  int cs = tlCur->label()->font().pointSize();

  qDebug() << "TI: widget size: " << size.width() << "x" << size.height();
  qDebug() << "current font size: " << cs << "\tnew size: " << ns;
/ *
  QFont font(tlCur->label()->font().family(), ns, QFont::Bold);

  tlCur->label()->setFont(font);
  */
  }
