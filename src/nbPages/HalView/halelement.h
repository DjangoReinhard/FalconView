#ifndef HALELEMENT_H
#define HALELEMENT_H
#include <QObject>


class HalElement : public QObject
{
  Q_OBJECT
public:
  explicit HalElement(HalElement* parent = nullptr);
  virtual ~HalElement();

  void             appendChild(HalElement* child);
  HalElement*      child(int row);
  int              childCount() const;
  int              childNumber();
//  int              columnCount() const;
  virtual QVariant data(int column) const;
  virtual int      next() const = 0;
  void             setData(int column, const QVariant& value);

protected:
  QVector<HalElement*> children;
  QString              name;
  void*                p;
  };
#endif // HALELEMENT_H
