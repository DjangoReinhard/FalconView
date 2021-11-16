#ifndef DIRENTRY_H
#define DIRENTRY_H
#include <QVariant>


class DirEntry
{
public:
  DirEntry(const QString& name, const QString& path, DirEntry* parent = nullptr);
  ~DirEntry();

  void     appendChild(DirEntry* child);

  DirEntry* child(int row);
  int       childCount() const;
  int       childNumber() const;
  int       columnCount() const;
  QVariant  data(int column) const;
  QString   path() const;
  int       row() const;
  DirEntry* parent();
  void      setData(int column, const QVariant& value);

private:
  QVector<DirEntry*> children;
  QVariant           itemData;
  QString            filePath;
  DirEntry*          parentItem;
  };
#endif // DIRENTRY_H
