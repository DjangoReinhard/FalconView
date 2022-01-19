#ifndef POS9_H
#define POS9_H
#include <QObject>
class CANON_POSITION;


class Pos9 : public QObject
{
  Q_OBJECT
public:
  Pos9(QObject *parent = nullptr);
  Pos9(const CANON_POSITION& p);
  Pos9(double x, double y, double z, double a=0, double b=0, double c=0, double u=0, double v=0, double w=0);
  Pos9(const Pos9& other);

  Pos9& operator=(const Pos9& other);

  CANON_POSITION* toCanon();

  double x, y, z, a, b, c, u, v, w;
  };
#endif // POS9_H
