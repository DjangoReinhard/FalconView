/* 
 * **************************************************************************
 * 
 *  file:       jogview.h
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
#ifndef JOGVIEW_H
#define JOGVIEW_H
#include <abscenterwidget.h>
#include <CenterPageInterface.h>
#include <ui_Jog.h>

class JogView : public AbstractCenterWidget, public CenterPageInterface
{
  Q_OBJECT
  Q_INTERFACES(CenterPageInterface)
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "CenterPageInterface_iid" FILE "jogView.json")
#endif
public:
  explicit JogView(QWidget* parent = nullptr);
  virtual ~JogView();

protected:
  virtual void     closeEvent(QCloseEvent* e) override;
  virtual QWidget* createContent() override;
  virtual void     connectSignals() override;
  virtual void     updateStyles() override;
  virtual void     keyPressEvent(QKeyEvent* event) override;
  virtual bool     eventFilter(QObject* src, QEvent* event) override;
  virtual void     setupUi(AbstractCenterWidget* parent);
  virtual void     showEvent(QShowEvent* e) override;
  virtual QAction* viewAction() override;
  void incStepSize();
  void decStepSize();
  void jog(QWidget* o, int axis, int step);
  void singleStep(bool singleStep);
  void setStepSize();
  void jogVelChanged();
  void stepSizeChanged(const QVariant& stepSize);
  void sliderChanged(const QVariant& v);

private:
  Ui::JogForm*         ui;
  QList<QRadioButton*> rbl;
  double               stepSize;
  double               jogSpeed;
  double               defSpeed;
  double               maxSpeed;
  };
#endif // JOGVIEW_H
