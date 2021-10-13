#ifndef LCPROPERTIES_H
#define LCPROPERTIES_H
#include <QVariant>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QMap>
class QFile;


/**
 * @brief The LcProperties class
 * process ini-files from linuxcnc
 */
class LcProperties
{
public:
  explicit LcProperties(const QString& fileName = QString());
  explicit LcProperties(const LcProperties&& other);

  LcProperties& operator = (const LcProperties&& other);
  QVariant      value(const QString& groupID, const QString& name);
  QString       fileName() const { return fn.absoluteFilePath(); }
  QString       baseDir() const  { return fn.absoluteDir().path(); }
  void          dump();

protected:
  void processFile(QFile& file);
  void processLine(const QString& line);
  void addGroup(const QString& groupID);
  void addValue(const QString& name, const QVariant& value);

private:
  QMap<QString, QMap<QString, QVariant>> properties;
  QMap<QString, QVariant>*               curMap;
  QFileInfo                              fn;
  };
#endif // LCPROPERTIES_H
