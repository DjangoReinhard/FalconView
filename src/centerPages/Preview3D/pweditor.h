/* 
 * **************************************************************************
 * 
 *  file:       pweditor.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    27.1.2022 by Django Reinhard
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
#ifndef PWEDITOR_H
#define PWEDITOR_H
#include <testEdit.h>
#include <GCodeViewerInterface.h>
class QAction;
class QSplitter;
class QLineEdit;
class QVariant;
class QPlainTextEdit;
class QTextBlock;
class QPushButton;
class OcctQtViewer;
class GCodeEditor;
class GCodeHighlighter;


class PreViewEditor : public TestEdit, public GCodeViewerInterface
{
  Q_OBJECT
  Q_INTERFACES(GCodeViewerInterface)
  Q_INTERFACES(CenterPageInterface)
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "GCodeViewerInterface_iid" FILE "preview3D.json")
#endif
public:
  PreViewEditor(QWidget* parent = nullptr);

  virtual QString currentRow() const override;
  virtual long    curLine() const override;

public slots:
  void setCurrentLine(const QVariant& line);
  void nextEditorLine();
  void prevEditorLine();

protected:
  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual void showEvent(QShowEvent *event) override;
  virtual void closeEvent(QCloseEvent*) override;
  virtual bool eventFilter(QObject*, QEvent* e) override;
  virtual QWidget* createContent() override;
  virtual void patch(void* pk, void* pc, void* pv, void* pu = nullptr, bool flag = false) override;
  virtual QAction* viewAction() override;

protected slots:
  void setEditorLine(const QVariant& line);

private:
  QSplitter*        spV;
  QWidget*          frame;
  OcctQtViewer*     view3D;
  bool              previewIsCenter;
  };
#endif // PWEDITOR_H
