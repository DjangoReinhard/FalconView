/* 
 * **************************************************************************
 * 
 *  file:       positionstatus.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    29.1.2022 by Django Reinhard
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
#ifndef POSITIONSTATUS_H
#define POSITIONSTATUS_H
#include <abscenterwidget.h>
#include <axismask.h>
#include <QDockWidget>
#include <QLabel>
#include <QResizeEvent>
namespace Ui {
class PositionForm;
class PositionMain;
}
class NumLabel;
class QString;
class QStackedLayout;


class PositionStatus : public AbstractCenterWidget
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "ViewPluginInterface_iid" FILE "position.json")
#endif
public:
  PositionStatus(QWidget* parent = nullptr);
  PositionStatus(QWidget* parent, QString ledOn, QString ledOff);
  virtual ~PositionStatus();

  void setLedStyles(QString onStyle, QString offStyle);
  void setXHomed(QVariant arg = QVariant(true));
  void setYHomed(QVariant arg = QVariant(true));
  void setZHomed(QVariant arg = QVariant(true));
  void setAHomed(QVariant arg = QVariant(true));
  void setBHomed(QVariant arg = QVariant(true));
  void setCHomed(QVariant arg = QVariant(true));
  void setUHomed(QVariant arg = QVariant(true));
  void setVHomed(QVariant arg = QVariant(true));
  void setWHomed(QVariant arg = QVariant(true));

public slots:
  void setAbsolute(QVariant arg = QVariant(true));
  void setRelative();

protected:
  virtual void updateStyles() override;
  virtual void connectSignals() override;
  virtual QWidget* createContent() override;
  void updatePos();
  void setActive();
  void setStyles(Ui::PositionForm* frm, const QString& s, const QFont& f, int w);
  void connectPos(Ui::PositionForm* frm, const QString& key, const QString& cfgKey);

private:
  Ui::PositionMain* frm;
  Ui::PositionForm* rel;
  Ui::PositionForm* abs;
  Ui::PositionForm* dtg;
  QStackedLayout*   sl;
  QFrame*           frmRel;
  QFrame*           frmAbs;
  bool       absolute;
  AxisMask   axisMask;
  QString    ledOn;
  QString    ledOff;

  static const char* widthPat;
  static const char* a[];
  };

#endif // POSITIONSTATUS_H
