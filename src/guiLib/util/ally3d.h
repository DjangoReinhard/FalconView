#ifndef ALLY3D_H
#define ALLY3D_H
#include <QObject>
#include <QMap>
//#include <AIS_InteractiveObject.hxx>
#include <AIS_ViewCube.hxx>
#include <AIS_Shape.hxx>
class OcctQtViewer;
class GraphicElement;
class GraphicFactory;


class Ally3D : public QObject
{
  Q_OBJECT
public:
  explicit Ally3D(QObject *parent = nullptr);

  void setOcctViewer(OcctQtViewer* view3D);
  void setTraverseColor(const QColor& c);
  void setFeedColor(const QColor& c);
  void setLimitsColor(const QColor& c);
  void setCurSegColor(const QColor& c);
  void setOldSegColor(const QColor& c);
  void setWorkPieceColor(const QColor& c);

public slots:
  void showPath(const QMap<long, GraphicElement*>& path);
  void moveCone(double x, double y, double z);
  void showMachineLimits();
  void showWorkLimits();

protected slots:
  void update(const QVariant& line);
  void highlight(const QVariant& line);

private:
  Handle(AIS_Shape) cone;
  OcctQtViewer*     v3D;
  GraphicFactory*   facGraph;
  Bnd_Box           workPiece;
//  Quantity_Color    lastColor;
  Quantity_Color    colTraverse;
  Quantity_Color    colFeed;
  Quantity_Color    colLimits;
  Quantity_Color    colCurSeg;
  Quantity_Color    colOldSeg;
  Quantity_Color    colWorkPiece;
  QMap<long, GraphicElement*> workPath;
  QMap<long, GraphicElement*>::iterator lastSeg;
  };
#endif // ALLY3D_H
