/* 
 * **************************************************************************
 * 
 *  file:       fixtureedit.h
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
#ifndef FIXTUREEDIT_H
#define FIXTUREEDIT_H
#include <abscenterwidget.h>
#include <ui_Fixture.h>
class QLineEdit;
class AxisMask;


class FixtureEdit : public AbstractCenterWidget
{
public:
  FixtureEdit(const QString& title, int ordinal, const AxisMask& mask, QWidget* parent = nullptr);

  virtual void connectSignals() override;
  virtual void updateStyles()   override;
  virtual void setEnabled(bool enable, QFont* f, QString* s);

protected:
  virtual bool focusNextPrevChild(bool next) override;
  virtual bool eventFilter(QObject *obj, QEvent *event) override;
  virtual QWidget* createContent() override;
  void saveFixture();
  void setupUi(AbstractCenterWidget* parent);

private:
  Ui::FixtureEditorForm* ui;
  int                    ordinal;
  QList<QLineEdit*>      edits;
  const AxisMask&        m;
  friend class FixtureManager;
  };
#endif // FIXTUREEDIT_H
