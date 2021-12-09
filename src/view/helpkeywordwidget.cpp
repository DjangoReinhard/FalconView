#include <helpkeywordwidget.h>
#include <QDomDocument>
#include <QDomNode>
#include <QDebug>


HelpKeywordWidget::HelpKeywordWidget(QWidget* parent)
 : QListWidget(parent) {
  }


HelpKeywordWidget::~HelpKeywordWidget() {
  }


void HelpKeywordWidget::parse(const QByteArray &ba, QMap<QString, QString>& keyWords) {
  QDomDocument doc;

  doc.setContent(ba);
  QDomNodeList links = doc.elementsByTagName("keywords");

  clear();
  for (int i=0; i < links.count(); ++i) {
      QDomNode link = links.item(i);

//      qDebug() << "\n";
//      qDebug() << "check entry #" << i;
      if (link.isElement()) {
         QDomElement e = link.toElement();

         processChildren(e, keyWords);
         }
      }
  }


void HelpKeywordWidget::processChildren(const QDomElement& e, QMap<QString, QString>& keyWords) {
//  qDebug() << "processChildren ... ";

  for (QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling()) {
      if (n.isElement()) {
//         qDebug() << "child is Element";
         QDomElement      elem = n.toElement();
         QListWidgetItem* item = new QListWidgetItem();
         int              mx   = elem.attributes().count();

         item->setIcon(icon);
         for (int i=0; i < mx; ++i) {
             const QDomNode& n = elem.attributes().item(i);

             if (n.nodeName() == "name")     item->setText(n.nodeValue());
             else if (n.nodeName() == "ref") item->setToolTip(n.nodeValue());
             }
         addItem(item);
         keyWords[item->text()] = item->toolTip();
         }
//      else if (n.isEntity()) qDebug() << "child is Entity";
//      else if (n.isAttr())   qDebug() << "child is Attribute";
//      else if (n.isText())   qDebug() << "child is Text";
      }
  }


void HelpKeywordWidget::setIcon(const QIcon &icon) {
  this->icon = icon;
  }
