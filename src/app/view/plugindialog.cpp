/* 
 * **************************************************************************
 * 
 *  file:       plugindialog.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    9.1.2022 by Django Reinhard
 *  copyright:  (c) 2022 Django Reinhard -  all rights reserved
 * 
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 2 of the License, or 
 *  (at your option) any later version. 
 *   
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details. 
 *   
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * **************************************************************************
 */
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
