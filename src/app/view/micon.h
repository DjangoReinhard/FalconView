#ifndef MICON_H
#define MICON_H
#include <QIcon>


class MIcon : public QIcon
{
public:
  MIcon(const QString& stdFileName, const QString& selFileName);
  MIcon(const QString& normalFile, const QString& activeFile, const QString& selectedFile);
  static void setDisabledFileName(const QString& fileName);

protected:
  static QString disabledFileName;
  };
#endif // MICON_H
