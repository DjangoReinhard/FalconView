/* 
 * **************************************************************************
 * 
 *  file:       preferenceseditor.h
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
#ifndef PREFERENCESEDITOR_H
#define PREFERENCESEDITOR_H
#include <abscenterwidget.h>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QCheckBox;
class QPushButton;
class QShowEvent;
class QSpinBox;
QT_END_NAMESPACE


class PreferencesEditor : public AbstractCenterWidget
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "ViewPluginInterface_iid" FILE "prefsEditor.json")
#endif
public:
  PreferencesEditor(QWidget* parent = nullptr);
 ~PreferencesEditor();

  virtual void connectSignals() override;
  virtual void updateStyles() override;

protected:
  virtual QWidget* createContent() override;
  virtual bool eventFilter(QObject *, QEvent *event) override;
  void setupLabels();

protected slots:
  void changeForegroundColor(int i);
  void changeBackgroundColor(int i);
  void changeFont(int i);
  void previewCenterChanged(const QVariant& state);
  void statusInsideChanged(const QVariant& state);
  void statusShowHelpChanged(const QVariant& state);
  void addressChanged(const QString& addr);
  void portChanged(int port);
  virtual void showEvent(QShowEvent* e) override;

private:
  QLineEdit**   labels;
  QPushButton** bgButtons;
  QPushButton** fgButtons;
  QPushButton** fontButtons;
  QLineEdit*    edNetAddress;
  QSpinBox*     spPort;
  QCheckBox*    cbStatesInside;
  QCheckBox*    cbHelp;
  QCheckBox*    cbPreviewCenter;
  int           count;
  };
#endif // PREFERENCESEDITOR_H
