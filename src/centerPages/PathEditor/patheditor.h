/* 
 * **************************************************************************
 * 
 *  file:       patheditor.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    22.1.2022 by Django Reinhard
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
#ifndef PATHEDITOR_H
#define PATHEDITOR_H
#include <testEdit.h>
#include <CenterPageInterface.h>
class PreViewEditor;
class QSplitter;
class QLineEdit;
class QVariant;
class QPlainTextEdit;
class QPushButton;
class GCodeEditor;
class GCodeHighlighter;


class PathEditor : public TestEdit
{
  Q_OBJECT
  Q_INTERFACES(CenterPageInterface)
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "CenterPageInterface_iid" FILE "pathEditor.json")
#endif
public:
  PathEditor(QWidget* parent = nullptr);

protected:
  virtual void     closeEvent(QCloseEvent* e) override;
  virtual QWidget* createContent() override;
  virtual void     loadFile(const QVariant& fileName) override;
  virtual void     connectSignals() override;
  virtual void     fileUpdated(const QString& fileName) override;
  virtual void     dirtyChanged(bool dirty) override;
  virtual void     showEvent(QShowEvent* e) override;
  virtual void     updateStyles() override;
  virtual QAction* viewAction() override;

private:
  void reallyLoadFile(const QVariant& fileName) override;
  };
#endif // PATHEDITOR_H
