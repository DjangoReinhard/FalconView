#ifndef CURCODESDOCKABLE_H
#define CURCODESDOCKABLE_H
#include <dockable.h>
class QWidget;
class QLabel;

class CurCodesDockable : public Dockable
{
  Q_OBJECT
public:
  CurCodesDockable(const QString& fileName, QWidget* parent = nullptr);

protected:
  void connectLabels();

private:
  QLabel* g0;
  QLabel* g1;
  QLabel* g2;
  QLabel* g3;
  QLabel* g4;
  QLabel* g5;
  QLabel* g6;
  QLabel* g7;
  QLabel* g8;
  QLabel* g9;
  QLabel* g10;
  QLabel* g11;
  QLabel* g12;
  QLabel* g13;
  QLabel* g14;
  QLabel* g15;
  QLabel* g16;
  QLabel* m0;
  QLabel* m1;
  QLabel* m2;
  QLabel* m3;
  QLabel* m4;
  QLabel* m5;
  QLabel* m6;
  QLabel* m7;
  QLabel* m8;
  QLabel* m9;
  };
#endif // CURCODESDOCKABLE_H
