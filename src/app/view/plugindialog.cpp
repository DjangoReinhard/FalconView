#include <plugindialog.h>
#include <PluginPageInterface.h>
#include <guicore.h>
#include <QDir>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPluginLoader>
#include <QPushButton>
#include <QStringList>
#include <QTreeWidget>
#include <QTreeWidgetItem>


PluginDialog::PluginDialog(const QString&, const QStringList&, QWidget *parent)
 : QDialog(parent)
 , label(new QLabel)
 , treeWidget(new QTreeWidget)
 , okButton(new QPushButton(tr("OK"))) {
  treeWidget->setAlternatingRowColors(true);
  treeWidget->setSelectionMode(QAbstractItemView::NoSelection);
  treeWidget->setColumnCount(2);
  treeWidget->header()->hide();
  okButton->setDefault(true);

  connect(okButton, &QAbstractButton::clicked, this, &QWidget::close);
  QGridLayout *mainLayout = new QGridLayout;

  mainLayout->setColumnStretch(0, 1);
  mainLayout->setColumnStretch(2, 1);
  mainLayout->addWidget(label, 0, 0, 1, 3);
  mainLayout->addWidget(treeWidget, 1, 0, 1, 3);
  mainLayout->addWidget(okButton, 2, 1);
  setLayout(mainLayout);

  interfaceIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirOpenIcon),
                          QIcon::Normal, QIcon::On);
  interfaceIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirClosedIcon),
                          QIcon::Normal, QIcon::Off);
  featureIcon.addPixmap(style()->standardPixmap(QStyle::SP_FileIcon));

  setWindowTitle(tr("Plugin Information"));
  populateTreeWidget();
  }


void PluginDialog::populateTreeWidget() {
  QList<QString> pages = GuiCore().pluggableMainPages();

  for (const QString& p : pages) {
      auto pluginItem = new QTreeWidgetItem(treeWidget);

      pluginItem->setText(0, tr("Page"));
      pluginItem->setText(1, p);
      pluginItem->setIcon(0, interfaceIcon);
      }
  pages = GuiCore().statusInfos();

  for (const QString& p : pages) {
      auto pluginItem = new QTreeWidgetItem(treeWidget);

      pluginItem->setText(0, tr("Info"));
      pluginItem->setText(1, p);
      pluginItem->setIcon(0, featureIcon);
      }
  }
