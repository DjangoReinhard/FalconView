#include <splitwidget.h>
#include <QSplitter>


SplitWidget::SplitWidget(Qt::Orientation orientation, QWidget* parent)
 : QFrame(parent)
 , divider(nullptr) {
  divider = new QSplitter(orientation, this);
  }
