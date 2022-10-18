/* 
 * **************************************************************************
 * 
 *  file:       helpview.h
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
#ifndef HELPVIEW_H
#define HELPVIEW_H
#include <abscenterwidget.h>
class QTreeWidgetItem;
class QListWidgetItem;
class QTextBrowser;
class QTabWidget;
class QSplitter;
class HelpEngine;
class HelpContentWidget;
class HelpKeywordWidget;


class HelpView : public AbstractCenterWidget
{
  Q_OBJECT
public:
  explicit HelpView(QWidget* parent = nullptr);

  void help4Keyword(const QString& keyWord);
  void restoreState();
  void saveState();

  virtual void closeEvent(QCloseEvent* event) override;

protected:
  virtual QWidget* createContent() override;
  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual bool eventFilter(QObject* o, QEvent* e) override;

protected slots:
  void contentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
  void keywordItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
  void sourceChanged(const QUrl &src);
  void tabChanged(int index);

private:
  QTextBrowser*      tb;
  QSplitter*         sp;
  HelpEngine*        he;
  QTabWidget*        tw;
  HelpContentWidget* cw;
  HelpKeywordWidget* kw;
  };
#endif // HELPVIEW_H
