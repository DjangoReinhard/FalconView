#include <helpcontentwidget.h>
#include <QDomDocument>
#include <QHeaderView>
#include <QDebug>


HelpContentWidget::HelpContentWidget(QWidget* parent)
 : QTreeWidget(parent) {
  header()->setStretchLastSection(true);
  setHeaderLabel(tr("Title"));
  }


HelpContentWidget::~HelpContentWidget() {
  }


void HelpContentWidget::parse(const QByteArray& ba) {
  QDomDocument doc;

  doc.setContent(ba);
  QDomNodeList links = doc.elementsByTagName("toc");

  level = 0;
  clear();
  for (int i=0; i < links.count(); ++i) {
      QDomNode link = links.item(i);

//      qDebug() << "\n";
//      qDebug() << "check entry #" << i;
      if (link.isElement()) {
         QDomElement e = link.toElement();

         processChildren(e);
         }
      }
  }


void HelpContentWidget::processAttributes(const QDomElement& e, QTreeWidgetItem* item) {
  int mx = e.attributes().count();

//  qDebug() << "processAttributes ...";
  if (mx > 0) {
//     qDebug() << "element has" << mx << "attributes";
     for (int i=0; i < mx; ++i) {
         const QDomNode& n = e.attributes().item(i);

//         qDebug() << "\tattribute:" << n.nodeName() << " => " << n.nodeValue();
         if (n.nodeName() == "title")    item->setText(0, n.nodeValue());
         else if (n.nodeName() == "ref") item->setText(1, n.nodeValue());
         }
     }
//  else qDebug() << "element has NO attributes";
  }


void HelpContentWidget::processChildren(const QDomElement& e, QTreeWidgetItem* parent) {
//  qDebug() << "processChildren ... (level:" << level++ << ")";

  for (QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling()) {
      if (n.isElement()) {
//         qDebug() << "child is Element";
         processElement(n.toElement(), parent);
         }
      }
  --level;
  }


QTreeWidgetItem* HelpContentWidget::createItem(const QDomElement &e, QTreeWidgetItem *parent) {
  QTreeWidgetItem* item;

  if (parent) item = new QTreeWidgetItem(parent);
  else        item = new QTreeWidgetItem(this);
  item->setIcon(0, folderIcon);
  processAttributes(e, item);

  return item;
  }


QTreeWidgetItem* HelpContentWidget::processElement(const QDomElement& e, QTreeWidgetItem* parent) {
//  qDebug() << "processElement - tag:" << e.tagName() << "text:" << e.text();
  QTreeWidgetItem* item = nullptr;

  if (e.tagName() == "section") {
     item = createItem(e, parent);

     processChildren(e, item);
     }
  return item;
  }


void HelpContentWidget::setFolderIcon(const QIcon &ico) {
  folderIcon = ico;
  }


void HelpContentWidget::setHelpIcon(const QIcon &ico) {
  helpIcon = ico;
  }
