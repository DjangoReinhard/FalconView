/* 
 * **************************************************************************
 * 
 *  file:       aboutdialog.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    22.1.2022 by Django Reinhard
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
#include <aboutdialog.h>
#include <guicore.h>
#include <occtviewer.h>
#include <QHeaderView>
#include <QTabWidget>
#include <QTreeWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>

#include <Standard_Version.hxx>
#include <qconfig.h>
#include <config.h>

AboutDialog::AboutDialog(QWidget* parent)
 : QDialog(parent) {
  tw = new QTabWidget;

  tw->addTab(new GeneralTab(), tr("General"));
  tw->addTab(new GLInfoTab(),  tr("GL-Info"));
  tw->addTab(new PluginsTab(), tr("Plugins"));

  bb = new QDialogButtonBox(QDialogButtonBox::Ok);
  connect(bb, &QDialogButtonBox::accepted, this, &QDialog::accept);
  QLabel*      l  = new QLabel(tr("<h3>FalconView</h3>"));
  QVBoxLayout* vl = new QVBoxLayout;

  vl->addWidget(l);
  vl->addWidget(tw);
  vl->addWidget(bb);
  setLayout(vl);
  setWindowTitle("About - rednose");
  resize(400,400);
  }


GeneralTab::GeneralTab(QWidget* parent)
 : QWidget(parent) {
  QLabel* l = new QLabel(tr("<h3>FalconView</h3><p>is an application to manage "
                            "machines controlled by linuxCNC.</p>"
                            "<p>FalconView uses external components:<ul>"
                            "<li><a href=\"%1\">linuxCNC v.%2</a></li>"
                            "<li><a href=\"%3\">Open CASCADE Technology v.%4</a></li>"
                            "<li><a href=\"%5\">Qt Toolkit v.%6</a></li></ul></p>")
                         .arg("https://github.com/LinuxCNC/linuxcnc", PACKAGE_VERSION)
                         .arg("https://dev.opencascade.org/release",  OCC_VERSION_STRING_EXT)
                         .arg("https://www.qt.io/download", QLatin1String(QT_VERSION_STR))
                         );
  QVBoxLayout* vl = new QVBoxLayout;

  vl->addWidget(l);
  setLayout(vl);
  }


GLInfoTab::GLInfoTab(QWidget* parent)
 : QWidget(parent) {
  QString glInfo = GuiCore().view3D()->getGlInfo();
  QLabel* l      = new QLabel(tr("GL capabilities: %1")
                             .arg(glInfo)
                              );
  QVBoxLayout* vl = new QVBoxLayout;

  vl->addWidget(l);
  setLayout(vl);
  }


PluginsTab::PluginsTab(QWidget* parent)
 : QWidget(parent)
 , tree(new QTreeWidget) {
  tree->setAlternatingRowColors(true);
  tree->setSelectionMode(QAbstractItemView::NoSelection);
  tree->setColumnCount(1);
  tree->header()->hide();
  QList<QString>   plugins  = GuiCore().pluggableMainPages();
  QTreeWidgetItem* group    = new QTreeWidgetItem(tree);
  QFont            boldFont = group->font(0);
  QTreeWidgetItem* ti;

  boldFont.setBold(true);
  group->setText(0, tr("Center-Pages:"));
  group->setExpanded(true);
  group->setFont(0, boldFont);
  for (const QString& pn : plugins) {
      ti = new QTreeWidgetItem(group);
      ti->setText(0, pn);
      }
  plugins = GuiCore().pluggableNotebookPages();

  group = new QTreeWidgetItem(tree);
  group->setText(0, tr("Notebook-Pages:"));
  group->setExpanded(true);
  group->setFont(0, boldFont);
  for (const QString& pn : plugins) {
      ti = new QTreeWidgetItem(group);
      ti->setText(0, pn);
      }
  plugins = GuiCore().statusInfos();

  group = new QTreeWidgetItem(tree);
  group->setText(0, tr("Status-Infos:"));
  group->setExpanded(true);
  group->setFont(0, boldFont);
  for (const QString& pn : plugins) {
      ti = new QTreeWidgetItem(group);
      ti->setText(0, pn);
      }
  QVBoxLayout* vl = new QVBoxLayout;

  vl->addWidget(tree);
  setLayout(vl);
  }

