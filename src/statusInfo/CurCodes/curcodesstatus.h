/* 
 * **************************************************************************
 * 
 *  file:       curcodesstatus.h
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
#ifndef CURCODESSTATUS_H
#define CURCODESSTATUS_H
#include <abscenterwidget.h>
class QWidget;
class QLabel;

class CurCodesStatus : public AbstractCenterWidget
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "ViewPluginInterface_iid" FILE "curCodes.json")
#endif
public:
  explicit CurCodesStatus(QWidget* parent = nullptr);
  virtual ~CurCodesStatus() = default;

protected:
  virtual void     connectSignals() override;
  virtual QWidget* createContent() override;
  virtual QString  fileName() const override;
  virtual void     patch(void* pk, void* pc, void* pv, void* pu = nullptr, bool flag = false) override;
  virtual void     updateStyles() override;

private:
  bool     isVertical;
  QLabel** labels;
  };
#endif // CURCODESSTATUS_H
