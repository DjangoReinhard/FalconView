/* 
 * **************************************************************************
 * 
 *  file:       sysevent.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    3.1.2022 by Django Reinhard
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
#ifndef SYSEVENT_H
#define SYSEVENT_H
#include <QObject>

#define HAVE_DATETIME

class SysEvent : public QObject
{
  Q_OBJECT
public:
  enum EventType {
    No_Error
  , OperatorError
  , OperatorText
  , OperatorDisplay
  , SystemError
  , NMLError
  , NMLText
  , NMLDisplay
  , NMLEvent
    };
  static QString toString(EventType t);

  explicit SysEvent(EventType et = No_Error);
  explicit SysEvent(const QString& what, EventType et = SystemError);
  explicit SysEvent(EventType et, const QString& what, QObject *parent = nullptr);
#ifdef HAVE_DATETIME
  explicit SysEvent(EventType et, const QString& what, const QDateTime& when);
#endif
  explicit SysEvent(const SysEvent& o);

  SysEvent& operator=(const SysEvent& o);

  EventType      type() const { return et; }
  long           when() const { return ts; }
  const QString& what() const { return msg; }

private:
  EventType et;
  long      ts;
  QString   msg;
  };
#endif // SYSEVENT_H
