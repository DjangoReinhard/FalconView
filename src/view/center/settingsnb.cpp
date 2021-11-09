#include <settingsnb.h>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QTabBar>
#include <QFont>


SettingsNotebook::SettingsNotebook(QWidget *parent)
 : DynWidget(parent)
 , tw(nullptr) {
  setObjectName(tr("SettingsNotebook"));
  setLayout(new QVBoxLayout);
  setContentsMargins(0, 0, 0, 0);
  tw = new QTabWidget();
  tw->setTabPosition(QTabWidget::TabPosition::South);
  tw->setTabShape(QTabWidget::TabShape::Rounded);
//  tw->tabBar()->setFont(QFont(tw->tabBar()->font().family(), 11));
  QString topStyles("QTabWidget::pane { border-top: 2px solid #C2C7CB; }"
                    "QTabWidget::tab-bar { left: 1px; margin-bottom: -6px; }"
                    "/* "
                    " * Style the tab using the tab sub-control. Note that it reads QTabBar _not_ QTabWidget"
                    " */"
                    "QTabBar::tab {"
                    "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ECF4F9,"
                    "stop: 0.5 #8DADC6, stop: 1.0 #465563);"
                    "border: 2px solid #C4C4C3;"
                    "border-bottom-color: #C2C7CB; /* same as the pane color */"
                    "border-top-left-radius: 6px;"
                    "border-top-right-radius: 10px;"
                    "min-width: 8ex;"
                    "padding-left: 15px;"
                    "padding-right: 15px;"
                    "padding-top: 4px;"
                    "padding-bottom: 6px;"
                    "}"
                    "QTabBar::tab:selected {"
                    "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #CFFEBA, "
                    "stop: 0.5 #22E710, stop: 1.0 #0B490A);"
                    "}"
                    "QTabBar::tab:selected {"
                    "border-color: #9B9B9B;"
                    "font: bold; color: white;"
                    "border-bottom-color: #C2C7CB; /* same as pane color */"
                    "}"
                    "QTabBar::tab:!selected {"
                    "margin-top: 4px; /* make non-selected tabs look smaller */"
                    "margin-right: -4px;"
                    "}"
                    "QTabBar::tab:selected {"
                    "/* expand/overlap to the left and right by 4px */"
                    "margin-left: -4px;"
                    "margin-right: -6px;"
                    "}"
                    "QTabBar::tab:first:selected {"
                    "margin-left: 0; /* the first selected tab has nothing to overlap with on the left */"
                    "}"
                    "QTabBar::tab:last {"
                    "margin-right: 0; /* the last selected tab has nothing to overlap with on the right */"
                    "}"
                    "QTabBar::tab:only-one {"
                    "margin: 0; /* if there is only one tab, we don't want overlapping margins */"
                    "}");
  QString bottomStyles("QTabWidget::pane { border-bottom: 2px solid #C2C7CB; }"
                       "QTabWidget::tab-bar { left: 1px; }"
                       "/* "
                       " * Style the tab using the tab sub-control. Note that it reads QTabBar _not_ QTabWidget"
                       " */"
                       "QTabBar::tab {"
                       "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ECF4F9,"
                       "stop: 0.5 #8DADC6, stop: 1.0 #465563);"
                       "border: 2px solid #C4C4C3;"
                       "border-top-color: #C2C7CB; /* same as the pane color */"
                       "border-bottom-left-radius: 6px;"
                       "border-bottom-right-radius: 10px;"
                       "min-width: 8ex;"
                       "padding-left: 15px;"
                       "padding-right: 15px;"
                       "padding-top: 4px;"
                       "padding-bottom: 6px;"
                       "}"
                       "QTabBar::tab:selected {"
                       "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #CFFEBA, "
                       "stop: 0.5 #22E710, stop: 1.0 #0B490A);"
                       "}"
                       "QTabBar::tab:selected {"
                       "border-color: #9B9B9B;"
                       "font: bold; color: white;"
                       "border-bottom-color: #C2C7CB; /* same as pane color */"
                       "}"
                       "QTabBar::tab:!selected {"
                       "margin-bottom: 4px; /* make non-selected tabs look smaller */"
                       "margin-right: -4px;"
                       "}"
                       "QTabBar::tab:selected {"
                       "/* expand/overlap to the left and right by 4px */"
                       "margin-left: -4px;"
                       "margin-right: -6px;"
                       "}"
                       "QTabBar::tab:first:selected {"
                       "margin-left: 0; /* the first selected tab has nothing to overlap with on the left */"
                       "}"
                       "QTabBar::tab:last {"
                       "margin-right: 0; /* the last selected tab has nothing to overlap with on the right */"
                       "}"
                       "QTabBar::tab:only-one {"
                       "margin: 0; /* if there is only one tab, we don't want overlapping margins */"
                       "}");
  tw->setStyleSheet(bottomStyles);
  layout()->addWidget(tw);
  }


SettingsNotebook::~SettingsNotebook() {
  }


void SettingsNotebook::addPage(DynWidget* page) {
  assert(page);
  page->init();
  tw->addTab(page, page->objectName());
  }


void SettingsNotebook::connectSignals() {
  }


void SettingsNotebook::updateStyles() {
  }
