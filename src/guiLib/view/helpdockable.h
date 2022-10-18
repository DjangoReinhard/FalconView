/* 
 * **************************************************************************
 * 
 *  file:       helpdockable.h
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
#ifndef HELPDOCKABLE_H
#define HELPDOCKABLE_H
//#include <ui_HelpTitle.h>
#include <QDockWidget>
//#include <QPixmap>
class HelpView;
//class QSplitter;
//class QTextBrowser;
//class QTabWidget;
//class HelpContentWidget;
//class HelpKeywordWidget;
//class QTreeWidgetItem;
//class QListWidgetItem;

namespace Ui {
  class HelpTitle;
}


class HelpDockable : public QDockWidget
{
  Q_OBJECT
public:
  HelpDockable(HelpView* view, QWidget* parent = nullptr);

  void showHelp();
  void help4Keyword(const QString& keyWord);

protected:
  void closeEvent(QCloseEvent* event) override;

//  void contentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
//  void keywordItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
  void keyPressEvent(QKeyEvent* event) override;
//  void sourceChanged(const QUrl &src);
//  void tabChanged(int index);

//private:
//  QTextBrowser*      tb;
//  QSplitter*         sp;
//  HelpEngine*        he;
//  QTabWidget*        tw;
//  HelpContentWidget* cw;
//  HelpKeywordWidget* kw;
//  static const QString& className;
  HelpView* hv;
  };


class HelpTitleBar : public QWidget
{
  Q_OBJECT
public:
  explicit HelpTitleBar(QWidget* parent = nullptr);

  QSize sizeHint() const override { return minimumSizeHint(); }
  QSize minimumSizeHint() const override;
  void  setTitle(const QString& title);

protected:
  void mouseReleaseEvent(QMouseEvent* event) override;

private:
  Ui::HelpTitle* titleBar;
  };
#endif // HELPDOCKABLE_H
