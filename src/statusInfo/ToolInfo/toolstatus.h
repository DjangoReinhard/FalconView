/* 
 * **************************************************************************
 * 
 *  file:       toolstatus.h
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
#ifndef TOOLSTATUS_H
#define TOOLSTATUS_H
#include <abscenterwidget.h>
class QVariant;
class QLabel;


class ToolStatus : public AbstractCenterWidget
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "PluginPageInterface_iid" FILE "toolInfo.json")
#endif
public:
  explicit ToolStatus(QWidget* parent = nullptr);
  virtual ~ToolStatus();

protected:
  virtual QWidget* createContent() override;
  virtual void updateStyles() override;
  virtual void connectSignals() override;

protected slots:
  void toolChanged(const QVariant& toolNum);

private:
  bool    isInPreview;
  QLabel* curTool;
  QLabel* nxtTool;
  QLabel* tDesc;
  QLabel* tLen;
  QLabel* tRad;
  QLabel* tPic;
  };
#endif // TOOLSTATUS_H
