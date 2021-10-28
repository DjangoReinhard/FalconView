#ifndef FILEMANAGERCLIENT_H
#define FILEMANAGERCLIENT_H
class QString;


class FileManagerClient
{
public:
  virtual void fileSelected(const QString& filePath) = 0;
  virtual QString pageName() = 0;
  };
#endif // FILEMANAGERCLIENT_H
