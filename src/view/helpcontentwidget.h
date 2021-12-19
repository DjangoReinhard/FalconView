#ifndef HELPCONTENTWIDGET_H
#define HELPCONTENTWIDGET_H
#include <QTreeWidget>
class QDomElement;


class HelpContentWidget : public QTreeWidget
{
  Q_OBJECT
public:
  explicit HelpContentWidget(QWidget* parent = nullptr);
  virtual ~HelpContentWidget();

  void setFolderIcon(const QIcon& ico);
  void setHelpIcon(const QIcon& ico);
  void setPageIcon(const QIcon& ico);
  void parse(const QByteArray& ba, QMap<QString, QString>& pages);
  void sourceChanged(const QUrl& src);

protected:
  QTreeWidgetItem* createItem(const QDomElement& e, QMap<QString, QString>& pages, QTreeWidgetItem* parent);
  QTreeWidgetItem* processElement(const QDomElement& e, QMap<QString, QString>& pages, QTreeWidgetItem* parent);
  void processChildren(const QDomElement& e, QMap<QString, QString>& pages, QTreeWidgetItem* parentItem = nullptr);
  void processAttributes(const QDomElement& e, QMap<QString, QString>& pages, QTreeWidgetItem* item);
  void checkNode(QTreeWidgetItem* node, const QUrl& src);

private:
  int   level;
  QIcon folderIcon;
  QIcon pageIcon;
  QIcon helpIcon;
  };
#endif // HELPCONTENTWIDGET_H
