/* 
 * **************************************************************************
 * 
 *  file:       kernel.h
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
#ifndef KERNEL_H
#define KERNEL_H
#ifdef REDNOSE
#include <KernelInterface.h>
#include <QObject>
#include <QBasicTimer>
#include <QLocale>
#include <configmgr.h>
class DBHelper;
class DBConnection;
class SysEvent;


class Kernel : public QObject , public virtual KernelInterface
{
  Q_OBJECT
public:
  virtual int            axisMask() const override;
  virtual ConfigManager* config() const override;
  virtual ConfigManager* config() override;
  virtual DBConnection*  databaseConnection() override;
  virtual QString        fileName4(const QString& fileID) const override;
  virtual void           initialize(DBHelper& dbAssist) override;
  virtual bool           isSimulator() const override;
  virtual QLocale        locale() const override;
  virtual void           logSysEvent(const QString& msg) override;
  virtual void           logSysEvent(const SysEvent& se) override;
  virtual void           processAppArgs(const QStringList& args) override;
  virtual QLocale*       setupTranslators() override;
  virtual QString        version() const override;

protected:
  explicit Kernel(QApplication& app, const QString& appName, const QString& groupID);
  virtual ~Kernel() = default;

  bool                simulator;
  QApplication&       app;
  ConfigManager*      cfg;
  QLocale*            curLocale;
  DBConnection*       conn;  
  QString             appName;
  QString             groupID;
  QString             langDir;
  QBasicTimer         timer;

  friend class Core;
  friend class Config;
  friend class KernelCreator;
  };
#endif // KERNEL_H
#endif
