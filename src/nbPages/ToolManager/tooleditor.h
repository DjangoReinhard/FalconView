/* 
 * **************************************************************************
 * 
 *  file:       tooleditor.h
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
#ifndef TOOLEDITOR_H
#define TOOLEDITOR_H
#include <QWidget>
class QComboBox;
class QSqlRecord;
class QSqlQueryModel;
class ToolCategoryModel;
class ToolModel;

QT_BEGIN_NAMESPACE
namespace Ui { class ToolEditorForm; }
QT_END_NAMESPACE


class ToolEditor : public QWidget
{
  Q_OBJECT
public:
  explicit ToolEditor(const QString& langPrefix, QWidget *parent = nullptr);

  void getChanges(QSqlRecord& r);
  void setModel(const QSqlRecord& r);
  void setRow2Edit(int row);

protected:
  void selectCBEntry(QComboBox* cb, const QString& name);
  virtual void changeEvent(QEvent *event) override;
  virtual bool focusNextPrevChild(bool next) override;
  virtual void resizeEvent(QResizeEvent *event) override;
  void dumpModel();
  void setupTabOrder();

  Ui::ToolEditorForm* ui;
  QSqlQueryModel*     model;
  int                 toolId;
  int                 edCount;
  QWidget**           tabOrder;
  };
#endif // TOOLEDITOR_H
