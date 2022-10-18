/* 
 * **************************************************************************
 * 
 *  file:       speedstatus.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    19.1.2022 by Django Reinhard
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
#ifndef SPEEDSTATUS_H
#define SPEEDSTATUS_H
#include <abscenterwidget.h>
class QLabel;
class QSlider;


class SpeedStatus : public AbstractCenterWidget
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "PluginPageInterface_iid" FILE "speedInfo.json")
#endif
public:
  SpeedStatus(QWidget* parent = nullptr);
  virtual ~SpeedStatus();

protected:
  virtual void     connectSignals() override;
  virtual QWidget* createContent() override;
  virtual QString  fileName() const override;
  virtual void     patch(void* pk, void* pc, void* pv, void* pu = nullptr, bool flag = false) override;
  virtual void     updateStyles() override;

protected slots:
  // slider callbacks
  void feedChanged(const QVariant& v);
  void fastFeedChanged(const QVariant& v);
  void speedChanged(const QVariant& v);
  // backend callbacks
  void feedRateChanged(const QVariant& v);
  void fastFeedRateChanged(const QVariant& v);
  void speedRateChanged(const QVariant& v);

private:
  bool    isVertical;
  QLabel *cmdFastFeed;
  QLabel *cmdFeed;
  QLabel *cmdSpeed;
  QLabel *curFastFeed;
  QLabel *curFeed;
  QLabel *curSpeed;
  QLabel *fastfeedFactor;
  QLabel *feedFactor;
  QLabel *label;
  QLabel *label_3;
  QLabel *label_9;
  QLabel *speedFactor;
  QSlider *slFastFeed;
  QSlider *slFeed;
  QSlider *slSpeed;
  };
#endif // SPEEDSTATUS_H
