/* 
 * **************************************************************************
 * 
 *  file:       tooltable.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    20.1.2022 by Django Reinhard
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
#ifndef TOOLTABLE_H
#define TOOLTABLE_H
#include <QAbstractTableModel>
#include <QListIterator>
#include <QFileInfo>
#include <QString>
#include <QList>
#include <QMap>
#include "toolentry.h"
#if defined(toLine)
# undef toLine
#endif
class QFile;
class QModelIndex;
class LcProperties;

/**
 * @brief The ToolTable class
 * parse and hold tooltable of linuxcnc
 */
class ToolTable : public QAbstractTableModel
{
  Q_OBJECT
public:
  explicit ToolTable(LcProperties& lcProps, const QString& fileName = QString());
  explicit ToolTable(LcProperties& lcProps, QFile& file);
  explicit ToolTable(const ToolTable&& other);
  virtual ~ToolTable();

  ToolTable&       operator = (const ToolTable&& other);
  const ToolEntry& current() const  { return curTool; }
  const ToolEntry* tool(int num) const;
  const ToolEntry* tool4Slot(int num) const;
  QString          fileName() const { return fn; }
  int              entries() const;
  void             dump();
  bool             save();
  void             setCurrent(int lineNum);
  void             setDirty(bool dirty = true);
  void             setLatheMode(bool latheMode)  { this->latheMode = latheMode; }
  QList<ToolEntry*>::Iterator begin()            { return tools.begin(); }
  QList<ToolEntry*>::Iterator end()              { return tools.end();   }
  QList<ToolEntry*>::ConstIterator begin() const { return tools.begin(); }
  QList<ToolEntry*>::ConstIterator end() const   { return tools.end();   }

  // for AbstractTableModel
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

protected:
  void addTool(const ToolEntry& tool);
  void processFile(QFile& file);
  void processLine(int lineNum, const QString& line);

private:
  QMap<int, ToolEntry*> mappedTools;
  QList<ToolEntry*>     tools;
  LcProperties&         lcProperties;
  QFileInfo             toolImageDir;
  ToolEntry             curTool;
  QString               fn;
  bool                  latheMode;
  bool                  dirty;
  };
#endif // TOOLTABLE_H
