/* 
 * **************************************************************************
 * 
 *  file:       filemodel.h
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
#ifndef FILEMODEL_H
#define FILEMODEL_H
#include <QAbstractTableModel>
#include <QFileInfo>


class FileModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  explicit FileModel(QObject *parent = nullptr);
  FileModel(const QVector<QFileInfo>& contacts, QObject *parent = nullptr);

  int           rowCount(const QModelIndex &parent) const override;
  int           columnCount(const QModelIndex &parent) const override;
  QVariant      data(const QModelIndex &index, int role) const override;
  QVariant      headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QFileInfo     fileInfo(int row) const;
//  const QVector<QFileInfo*> &files() const;
  void          setupModel(const QString& baseDir);

private:
  QVector<QFileInfo> vFiles;
  };
#endif // FILEMODEL_H
