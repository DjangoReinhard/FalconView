/* 
 * **************************************************************************
 * 
 *  file:       helpbrowser.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    19.1.2022 by Django Reinhard
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
#include "helpbrowser.h"
#include <helpengine.h>
#include <QDebug>


HelpBrowser::HelpBrowser(QWidget* parent)
 : QTextBrowser(parent)
 , engine(nullptr) {
  document()->setDefaultStyleSheet(defaultStyles);
  }


HelpBrowser::~HelpBrowser() {
  }


QVariant HelpBrowser::loadResource(int, const QUrl& link) {
  // all files for help system are inside the helpfile, so
  // don't need to use type of url ...
  return engine->fileData(link.path());
  }


void HelpBrowser::setHelpEngine(HelpEngine *he) {
  engine = he;
  }

const QString HelpBrowser::defaultStyles("table, th, td {"
                                           "border-width: 1px;"
                                           "border-color: #CCCCCC;"
                                           "border-collapse: collapse;"
                                         "}"
                                         "img {vertical-align: middle; }"
                                         "th, td {"
                                           "padding: 15px;"
                                         "}");
