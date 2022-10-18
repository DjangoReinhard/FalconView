/* 
 * **************************************************************************
 * 
 *  file:       falconviewdb.h
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
#ifndef FALCONVIEWDB_H
#define FALCONVIEWDB_H
#include <dbhelper.h>
#include <QVariant>
class QSqlTableModel;
class QSqlField;


class FalconViewDB : public QObject, public DBHelperInterface
{
  Q_OBJECT
  Q_INTERFACES(DBHelperInterface)
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "DBHelperInterface_iid" FILE "falconViewD.json")
#endif
public:
  explicit FalconViewDB(QObject* parent = nullptr);
  virtual ~FalconViewDB() = default;
  bool connect(const QString& name);

  virtual DBConnection* createDatabase(const QString& path);
  virtual void          createSampleData(DBConnection& conn);

protected:
  QString        xml2Sql(const QString& name) const;
  QVariant::Type colType4(const QString& columnName) const;
  void           createCategory(QSqlTableModel& model, QSqlField &fId, QSqlField &fProfile, QSqlField &fName, const QString &category);
  void           createToolSampleData(DBConnection& conn);
  void           createSysEventSamples(DBConnection& conn);

private:
  QMap<QString, int> toolCategories;
  };
#endif // FALCONVIEWDB_H
