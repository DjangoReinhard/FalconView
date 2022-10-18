/* 
 * **************************************************************************
 * 
 *  file:       filemodel.cpp
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
#include <filemodel.h>
#include <filesystem>
#include <QDateTime>
#include <QDebug>


FileModel::FileModel(QObject *parent)
 : QAbstractTableModel(parent) {
  }


FileModel::FileModel(const QVector<QFileInfo>& files, QObject *parent)
 : QAbstractTableModel(parent)
 , vFiles(files) {
  }


int FileModel::rowCount(const QModelIndex &parent) const {
  return parent.isValid() ? 0 : vFiles.size();
  }


int FileModel::columnCount(const QModelIndex &parent) const {
  return parent.isValid() ? 0 : 3;
  }


QVariant FileModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  if (index.row() >= vFiles.size() || index.row() < 0)
     return QVariant();
  if (role == Qt::DisplayRole) {
     const QFileInfo& file = vFiles.at(index.row());

     switch (index.column()) {
       case 0: return file.fileName();
       case 1: return file.size();
       case 2: return file.lastModified();
       default: break;
       }
     }
  return QVariant();
  }


QVariant FileModel::headerData(int section, Qt::Orientation orientation, int role) const {
  if (role != Qt::DisplayRole) return QVariant();
  if (orientation == Qt::Horizontal) {
     switch (section) {
       case 0: return tr("Name");
       case 1: return tr("Size");
       case 2: return tr("last modified");
       default: break;
       }
     }
  return QVariant();
  }


Qt::ItemFlags FileModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::ItemIsEnabled;
  return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
  }


QFileInfo FileModel::fileInfo(int row) const  {
  if (row < 0 || row >= vFiles.size()) return QFileInfo();
  return vFiles.at(row);
  }


void FileModel::setupModel(const QString &baseDir) {
  this->beginResetModel();
  vFiles.clear();
  for (auto& dirEntry : std::filesystem::directory_iterator{baseDir.toStdString()}) {
      if (dirEntry.is_directory()) continue;
//      qDebug() << "entry: " << dirEntry.path().c_str();
      vFiles.append(QFileInfo(dirEntry.path().c_str()));
      }
  this->endResetModel();
  }
