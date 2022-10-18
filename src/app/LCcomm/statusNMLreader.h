/* 
 * **************************************************************************
 * 
 *  file:       statusreader.h
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
#ifndef STATUSNMLREADER_H
#define STATUSNMLREADER_H
#include <QObject>
#include <abstractstatusreader.h>
class RCS_STAT_CHANNEL;
class EMC_STAT;
class ErrorReader;
class LCStatus;


class StatusNmlReader : public AbstractStatusReader
{
  Q_OBJECT
public:
  explicit StatusNmlReader(QObject* parent = nullptr);

  virtual bool isActive() const;
  virtual void read();
  virtual const LCStatus& status() const { return *lcStatus; }

private:
  RCS_STAT_CHANNEL*   cStatus;
  EMC_STAT*           emcStatus;
  ErrorReader*        errReader;
  LCStatus*           lcStatus;
  };

#endif // STATUSNMLREADER_H
