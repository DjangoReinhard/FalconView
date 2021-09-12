#ifndef LCPROPERTIES_H
#define LCPROPERTIES_H
#include <QVariant>
#include <QMap>
class QString;
class QFile;


class LcProperties
{
public:
  explicit LcProperties(const QString& fileName = QString());
  explicit LcProperties(const LcProperties&& other);

  LcProperties& operator = (const LcProperties&& other);
  QVariant value(const QString& groupID, const QString& name);
  void     dump();

protected:
  void processFile(QFile& file);
  void processLine(const QString& line);
  void addGroup(const QString& groupID);
  void addValue(const QString& name, const QVariant& value);

private:
  QMap<QString, QMap<QString, QVariant>> properties;
  QMap<QString, QVariant>*               curMap;
  };
#endif // LCPROPERTIES_H
