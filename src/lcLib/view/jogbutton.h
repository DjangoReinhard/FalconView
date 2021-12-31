#ifndef JOGBUTTON_H
#define JOGBUTTON_H
#include <QToolButton>


class JogButton : public QToolButton
{
  Q_OBJECT
public:
  explicit JogButton(QWidget* parent = nullptr);
  virtual ~JogButton();

  void init(JogButton* counterPart);

public slots:
  void pressed();
  void released();
  void toggled(bool checked);

private:
  JogButton* counterPart;
  QIcon      icoActive;
  QIcon      icoDefault;
  };

#endif // JOGBUTTON_H
