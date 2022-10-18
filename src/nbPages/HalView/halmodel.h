/* 
 * **************************************************************************
 * 
 *  file:       halmodel.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    23.1.2022 by Django Reinhard
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
#ifndef HALMODEL_H
#define HALMODEL_H
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
class HalElement;


class HalModel : public QAbstractItemModel
{
  Q_OBJECT
public:
  explicit HalModel(QObject *parent = nullptr);
  ~HalModel();

  QVariant      data(const QModelIndex& index, int role) const override;
  QVariant      headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  QModelIndex   index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
  QModelIndex   parent(const QModelIndex& index) const override;
  Qt::ItemFlags flags(const QModelIndex&index) const override;
//  HalElement*   root() const;
  HalElement*   getItem(const QModelIndex& index) const;
  int           rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int           columnCount(const QModelIndex& parent = QModelIndex()) const override;
//  bool          insertDirectory(const QModelIndex& parentIdx, HalElement* entry);
//  bool          setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
  void          setupModelData(HalElement* parent);
  void          processPins(int component, HalElement*);

  HalElement*   root;
  QString       name;
  int           compID;
  };
#endif // HALMODEL_H
