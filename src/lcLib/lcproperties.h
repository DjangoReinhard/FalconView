/* 
 * **************************************************************************
 * 
 *  file:       lcproperties.h
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
#ifndef LCPROPERTIES_H
#define LCPROPERTIES_H
#include <QVariant>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QMap>
class QFile;


/**
 * @brief The LcProperties class
 * process ini-files from linuxcnc
 */
class LcProperties
{
public:
  explicit LcProperties(const QString& fileName = QString());
  explicit LcProperties(const LcProperties&& other);

  LcProperties& operator = (const LcProperties&& other);
  QVariant      value(const QString& groupID, const QString& name) const;
  QString       fileName() const { return fn.absoluteFilePath(); }
  QString       parameterFileName() const;
  QString       toolTableFileName() const;
  QString       toolImageDir() const;
  QString       getPath(const QString& groupID, const QString& name) const;
  QString       baseDir() const  { return fn.absoluteDir().path(); }
  void          dump();

protected:
  void processFile(QFile& file);
  void processLine(const QString& line);
  void addGroup(const QString& groupID);
  void addValue(const QString& name, const QVariant& value);

private:
  QMap<QString, QMap<QString, QVariant>> properties;
  QMap<QString, QVariant>*               curMap;
  QFileInfo                              fn;
  };
#endif // LCPROPERTIES_H
