/* 
 * **************************************************************************
 * 
 *  file:       LCInter.h
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
#ifndef LCINTER_H
#define LCINTER_H
#include <QObject>
#include <QString>
class InterpBase;
class CanonIF;
class LcProperties;
class LCInterfaceP;
class ToolTable;
class QProcess;
class QTextStream;
class EMC_STAT;
class EMC_TOOL_STAT;


/**
 * @brief The outer shell to linuxCNC interpreter
 */
class LCInterface : public QObject
{
  Q_OBJECT
public:
  explicit LCInterface(CanonIF& cif, LcProperties& lcProperties, ToolTable& toolTable);
  virtual ~LCInterface();

  std::pair<QVector3D, QVector3D> machineLimits() const;
  void parseInline(const QString& fileName);
  void parseExt(const QString& fileName);
  void setupToolTable();

protected:
  void maybeNewLine();
  void maybeNewLine(int seqNum);
  int  readExec(const QString& line);

private:
  LCInterfaceP*  p;
  };
#endif
