#ifndef ALLY3D_H
#define ALLY3D_H
#include <QObject>
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
  void showPath(const QList<Handle(AIS_InteractiveObject)>& path);
  void moveCone(double x, double y, double z);
  void showMachineLimits();
  void showWorkLimits();

private:
  Handle(AIS_Shape)    cone;
  OcctQtViewer*        v3D;
  Bnd_Box              workPiece;
  };
#endif // ALLY3D_H
