#include <helpcontentwidget.h>
#include <QDomDocument>
#include <QHeaderView>
#include <QUrl>
#include <QDebug>


HelpContentWidget::HelpContentWidget(QWidget* parent)
 : QTreeWidget(parent) {
  header()->setStretchLastSection(true);
  setHeaderLabel(tr("Title"));
  }


HelpContentWidget::~HelpContentWidget() {
  }


void HelpContentWidget::parse(const QByteArray& ba, QMap<QString, QString>& pages) {
  QDomDocument doc;

  doc.setContent(ba);
  QDomNodeList links = doc.elementsByTagName("toc");

  level = 0;
  clear();
  for (int i=0; i < links.count(); ++i) {
      QDomNode link = links.item(i);

      if (link.isElement()) {
         QDomElement e = link.toElement();

         processChildren(e, pages);
         }
      }
  }


void HelpContentWidget::processAttributes(const QDomElement& e, QMap<QString, QString>& pages, QTreeWidgetItem* item) {
  int mx = e.attributes().count();

  if (mx > 0) {
     for (int i=0; i < mx; ++i) {
         const QDomNode& n = e.attributes().item(i);

         if (n.nodeName() == "title")    item->setText(0, tr(n.nodeValue().toStdString().c_str()));
         else if (n.nodeName() == "ref") item->setText(1, n.nodeValue());
         }
     pages[item->text(1)] = item->text(0);
     }
  }


void HelpContentWidget::processChildren(const QDomElement& e, QMap<QString, QString>& pages, QTreeWidgetItem* parent) {
  ++level;
  for (QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling()) {
      if (n.isElement()) processElement(n.toElement(), pages, parent);
      }
  --level;
  }


QTreeWidgetItem* HelpContentWidget::createItem(const QDomElement &e, QMap<QString, QString>& pages, QTreeWidgetItem *parent) {
  QTreeWidgetItem* item;

  if (parent) item = new QTreeWidgetItem(parent);
  else        item = new QTreeWidgetItem(this);
  item->setIcon(0, folderIcon);
  processAttributes(e, pages, item);

  return item;
  }


QTreeWidgetItem* HelpContentWidget::processElement(const QDomElement& e, QMap<QString, QString>& pages, QTreeWidgetItem* parent) {
  QTreeWidgetItem* item = nullptr;

  if (e.tagName() == "section") {
     item = createItem(e, pages, parent);

     processChildren(e, pages, item);
     }
  return item;
  }


void HelpContentWidget::setFolderIcon(const QIcon &ico) {
  folderIcon = ico;
  }


void HelpContentWidget::setHelpIcon(const QIcon &ico) {
  helpIcon = ico;
  }


void HelpContentWidget::sourceChanged(const QUrl &src) {
//  qDebug() << "HelpContentWidget::sourceChanged(" << src << ")";

  QTreeWidgetItem* node = this->invisibleRootItem();

  checkNode(node, src);
  }


void HelpContentWidget::checkNode(QTreeWidgetItem *node, const QUrl& src) {
  int mx = node->childCount();

  //  qDebug() << "node:" << node->text(1);
  if (node->text(1) == src.path()) {
     setCurrentItem(node);
     return;
     }
  for (int i=0; i < mx; ++i) {
      checkNode(node->child(i), src);
      }
  }
