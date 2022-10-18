/* 
 * **************************************************************************
 * 
 *  file:       core.cpp
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
#include <core.h>
#include <kernelcreator.h>
#include <KernelInterface.h>
#include <configacc.h>
#include <configmgr.h>
#include <sysevent.h>
#include <syseventmodel.h>

#include <QApplication>
#include <QFileInfo>
#include <QDebug>

#include <cassert>


Core::Core(QApplication& app, const QString& appName, DBHelperInterface& dbAssist, const QString& group) {
  if (!kernel) {
     assert(kc);
     kernel = kc->kernel(app, appName, group);
     kernel->initialize(dbAssist);
     }
  }


Core::Core() {
  assert(kernel);
  }


// dumb, but plugins have their own copy of statics :(
Core::Core(void* pFromOuterAdressSpace) {
  if (!kernel) kernel = (KernelInterface*)pFromOuterAdressSpace;
  assert(kernel);
  }


int Core::axisMask() const {
  return kernel->axisMask();
  }


DBConnection* Core::databaseConnection() {
  return kernel->databaseConnection();
  }


QString Core::fileName4(const QString &fileID) const {
  return kernel->fileName4(fileID);
  }


void Core::setKernelCreator(KernelCreator* kc) {
  Core::kc = kc;
  }


bool Core::isSimulator() const {
  return kernel->isSimulator();
  }


QLocale Core::locale() const {
  return kernel->locale();
  }


bool Core::move2Backup(const QString& fileName) {
  QString   backupPat(fileName);
  QFileInfo fi(fileName);
  QString   extension(QString(".%1").arg(fi.completeSuffix()));

  backupPat.replace(extension, ".bak%1");
  QFileInfo check(backupPat.arg(""));

  if (check.exists()) {
     QFile last(backupPat.arg(9));

     if (last.exists()) last.remove();
     for (int i=8; i > 0; --i) {
         QFile tmp(backupPat.arg(i));

         if (tmp.exists()) tmp.rename(backupPat.arg(i+1));
         }
     QFile tmp(check.absoluteFilePath());

     tmp.rename(backupPat.arg(1));
     }
  QFile file(fileName);

  return file.rename(check.absoluteFilePath());
  }


void Core::setAppMode(ApplicationMode m) {
  ValueManager().setValue("appMode", m);
  }


QString Core::languagePrefix() const {
  return kernel->locale().name().mid(0, 2);
  }


void Core::riseError(const QString &msg) {
  ValueManager().setValue("errorActive", true);
  SysEvent se(msg);

  kernel->logSysEvent(se);
  }


void Core::showAllButCenter(bool visible) {
  ValueManager().setValue("showAllButCenter", visible);
  }


bool Core::showHelpAtPageChange() const {
  return kernel->config()->value("showHelpAtPageChange").toBool();
  }

KernelInterface* Core::kernel  = nullptr;
KernelCreator*   Core::kc      = nullptr;
int              Core::checked = -1;
