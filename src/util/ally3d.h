#ifndef ALLY3D_H
#define ALLY3D_H
#include <QObject>
#include <QMap>
#include <AIS_InteractiveObject.hxx>
#include <AIS_ViewCube.hxx>
#include <AIS_Shape.hxx>
class OcctQtViewer;


class Ally3D : public QObject
{
  Q_OBJECT
public:
  explicit Ally3D(OcctQtViewer* view3D, QObject *parent = nullptr);

public slots:
  void showPath(const QMap<long, Handle(AIS_InteractiveObject)>& path);
  void moveCone(double x, double y, double z);
  void showMachineLimits();
  void showWorkLimits();
  void update(const QVariant& line);

private:
  Handle(AIS_Shape) cone;
  OcctQtViewer*     v3D;
  Bnd_Box           workPiece;
  QMap<long, Handle(AIS_InteractiveObject)> workPath;
  QMap<long, Handle(AIS_InteractiveObject)>::iterator lastSeg;
  };
#endif // ALLY3D_H
