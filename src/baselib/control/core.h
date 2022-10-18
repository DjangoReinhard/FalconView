/* 
 * **************************************************************************
 * 
 *  file:       core.h
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
#ifndef CORE_H
#define CORE_H
#include <QString>
#include <applicationmode.h>
class KernelInterface;
class KernelCreator;
class DBConnection;
class DBHelperInterface;
class QLocale;
class QApplication;


class Core
{
public:
  explicit Core();
  explicit Core(QApplication& app, const QString& appName, DBHelperInterface& dbAssist, const QString& group = "SRD");
  virtual ~Core() = default;

  virtual void    riseError(const QString& msg);

  int             axisMask() const;
  DBConnection*   databaseConnection();
  QString         fileName4(const QString& fileID) const;
  bool            isSimulator() const;
  QString         languagePrefix() const;
  QLocale         locale() const;
  bool            move2Backup(const QString& fileName);
  void            setAppMode(ApplicationMode m);
  void            showAllButCenter(bool visible);
  bool            showHelpAtPageChange() const;

  static void     setKernelCreator(KernelCreator* kc);

protected:
  explicit Core(void* p); // for plugins
  static KernelInterface* kernel;
  static KernelCreator*      kc;
  static int                 checked;
  friend class Config;
  friend class AbstractCenterWidget;
  friend class PluginPageFactory;
  };
#endif
