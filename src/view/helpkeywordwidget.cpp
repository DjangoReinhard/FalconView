#include <helpkeywordwidget.h>
#include <QCoreApplication>
#include <QDomDocument>
#include <QDomNode>
#include <QUrl>
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
  for (QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling()) {
      if (n.isElement()) {
         QDomElement      elem = n.toElement();
         QListWidgetItem* item = new QListWidgetItem();
         int              mx   = elem.attributes().count();

         item->setIcon(icon);
         for (int i=0; i < mx; ++i) {
             const QDomNode& n = elem.attributes().item(i);

             if (n.nodeName() == "name") {
                QString in(n.nodeValue());
                QString out(QCoreApplication::translate("HelpContentWidget", in.toStdString().c_str(), nullptr));

                qDebug() << "HelpKeywords - in:" << in << "out:" << out;
                item->setText(out);
                }
             else if (n.nodeName() == "ref") item->setToolTip(n.nodeValue());
             }
         addItem(item);
         keyWords[item->text()] = item->toolTip();
         }
      }
  }


void HelpKeywordWidget::setIcon(const QIcon &icon) {
  this->icon = icon;
  }


void HelpKeywordWidget::sourceChanged(const QUrl &src) {
//  int ndx = src.path().lastIndexOf(".html");
//  QString keyWord = src.path().mid(0, ndx);
  int mx = count();

  qDebug() << "HelpKeywordWidget::sourceChanged(" << src << ")"; // -> kw:" << keyWord;
  for (int i=0; i < mx; ++i) {
      QListWidgetItem* item = this->item(i);

//      qDebug() << "item at #" << i << " -> " << item->toolTip();
      if (item->toolTip() == src.path()) {
         this->setCurrentItem(item);
         return;
         }
      }
  }
