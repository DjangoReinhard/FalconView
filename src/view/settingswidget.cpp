#include <settingswidget.h>
#include <QLabel>
#include <QColor>
#include <QFont>
#include <QPushButton>
#include <QColorDialog>
#include <QFontDialog>
#include <QDebug>


SettingsWidget::SettingsWidget(const QString& fileName, QWidget* parent)
 : DynWidget(fileName, parent) {
  initializeWidget();
  }


void SettingsWidget::initializeWidget() {
  settings[0].lbl  = findChild<QLabel*>("actCodesPreview");
  settings[1].lbl  = findChild<QLabel*>("droAbsPreview");
  settings[2].lbl  = findChild<QLabel*>("droDtgPreview");
  settings[3].lbl  = findChild<QLabel*>("droRelPreview");
  settings[4].lbl  = findChild<QLabel*>("droTitlePreview");
  settings[5].lbl  = findChild<QLabel*>("feedPreview");
  settings[6].lbl  = findChild<QLabel*>("filenamePreview");
  settings[7].lbl  = findChild<QLabel*>("gcodePreview");
  settings[8].lbl  = findChild<QLabel*>("speedPreview");
  settings[9].lbl  = findChild<QLabel*>("toolDescPreview");
  settings[10].lbl = findChild<QLabel*>("toolNumPreview");
  settings[11].lbl = findChild<QLabel*>("toolNextPreview");
  for (int i=0; i < 12; ++i) settings[i].bg = Qt::white;

  bgActCodes   = findChild<QPushButton*>("bgActCodes");
  bgDroAbs     = findChild<QPushButton*>("bgDroAbs");
  bgDroDtg     = findChild<QPushButton*>("bgDroDtg");
  bgDroRel     = findChild<QPushButton*>("bgDroRel");
  bgDroTitle   = findChild<QPushButton*>("bgDroTitle");
  bgFeed       = findChild<QPushButton*>("bgFeed");
  bgFilename   = findChild<QPushButton*>("bgFilename");
  bgGCode      = findChild<QPushButton*>("bgGCode");
  bgSpeed      = findChild<QPushButton*>("bgSpeed");
  bgToolDesc   = findChild<QPushButton*>("bgToolDesc");
  bgToolNum    = findChild<QPushButton*>("bgToolNum");
  bgToolNext   = findChild<QPushButton*>("bgToolNext");

  fgActCodes   = findChild<QPushButton*>("fgActCodes");
  fgDroAbs     = findChild<QPushButton*>("fgDroAbs");
  fgDroDtg     = findChild<QPushButton*>("fgDroDtg");
  fgDroRel     = findChild<QPushButton*>("fgDroRel");
  fgDroTitle   = findChild<QPushButton*>("fgDroTitle");
  fgFeed       = findChild<QPushButton*>("fgFeed");
  fgFilename   = findChild<QPushButton*>("fgFilename");
  fgGCode      = findChild<QPushButton*>("fgGCode");
  fgSpeed      = findChild<QPushButton*>("fgSpeed");
  fgToolDesc   = findChild<QPushButton*>("fgToolDesc");
  fgToolNum    = findChild<QPushButton*>("fgToolNum");
  fgToolNext   = findChild<QPushButton*>("fgToolNext");

  fontActCodes = findChild<QPushButton*>("fontActCodes");
  fontDroAbs   = findChild<QPushButton*>("fontDroAbs");
  fontDroDtg   = findChild<QPushButton*>("fontDroDtg");
  fontDroRel   = findChild<QPushButton*>("fontDroRel");
  fontDroTitle = findChild<QPushButton*>("fontDroTitle");
  fontFeed     = findChild<QPushButton*>("fontFeed");
  fontFilename = findChild<QPushButton*>("fontFilename");
  fontGCode    = findChild<QPushButton*>("fontGCode");
  fontSpeed    = findChild<QPushButton*>("fontSpeed");
  fontToolDesc = findChild<QPushButton*>("fontToolDesc");
  fontToolNum  = findChild<QPushButton*>("fontToolNum");
  fontToolNext = findChild<QPushButton*>("fontToolNext");

  connect(bgActCodes, &QPushButton::pressed, this, [=](){ changeBackgroundColor(0); });
  connect(bgDroAbs,   &QPushButton::pressed, this, [=](){ changeBackgroundColor(1); });
  connect(bgDroDtg,   &QPushButton::pressed, this, [=](){ changeBackgroundColor(2); });
  connect(bgDroRel,   &QPushButton::pressed, this, [=](){ changeBackgroundColor(3); });
  connect(bgDroTitle, &QPushButton::pressed, this, [=](){ changeBackgroundColor(4); });
  connect(bgFeed,     &QPushButton::pressed, this, [=](){ changeBackgroundColor(5); });
  connect(bgFilename, &QPushButton::pressed, this, [=](){ changeBackgroundColor(6); });
  connect(bgGCode,    &QPushButton::pressed, this, [=](){ changeBackgroundColor(7); });
  connect(bgSpeed,    &QPushButton::pressed, this, [=](){ changeBackgroundColor(8); });
  connect(bgToolDesc, &QPushButton::pressed, this, [=](){ changeBackgroundColor(9); });
  connect(bgToolNum,  &QPushButton::pressed, this, [=](){ changeBackgroundColor(10); });
  connect(bgToolNext, &QPushButton::pressed, this, [=](){ changeBackgroundColor(11); });

  connect(fgActCodes, &QPushButton::pressed, this, [=](){ changeForegroundColor(0); });
  connect(fgDroAbs,   &QPushButton::pressed, this, [=](){ changeForegroundColor(1); });
  connect(fgDroDtg,   &QPushButton::pressed, this, [=](){ changeForegroundColor(2); });
  connect(fgDroRel,   &QPushButton::pressed, this, [=](){ changeForegroundColor(3); });
  connect(fgDroTitle, &QPushButton::pressed, this, [=](){ changeForegroundColor(4); });
  connect(fgFeed,     &QPushButton::pressed, this, [=](){ changeForegroundColor(5); });
  connect(fgFilename, &QPushButton::pressed, this, [=](){ changeForegroundColor(6); });
  connect(fgGCode,    &QPushButton::pressed, this, [=](){ changeForegroundColor(7); });
  connect(fgSpeed,    &QPushButton::pressed, this, [=](){ changeForegroundColor(8); });
  connect(fgToolDesc, &QPushButton::pressed, this, [=](){ changeForegroundColor(9); });
  connect(fgToolNum,  &QPushButton::pressed, this, [=](){ changeForegroundColor(10); });
  connect(fgToolNext, &QPushButton::pressed, this, [=](){ changeForegroundColor(11); });

  connect(fontActCodes, &QPushButton::pressed, this, [=](){ changeFont(0); });
  connect(fontDroAbs,   &QPushButton::pressed, this, [=](){ changeFont(1); });
  connect(fontDroDtg,   &QPushButton::pressed, this, [=](){ changeFont(2); });
  connect(fontDroRel,   &QPushButton::pressed, this, [=](){ changeFont(3); });
  connect(fontDroTitle, &QPushButton::pressed, this, [=](){ changeFont(4); });
  connect(fontFeed,     &QPushButton::pressed, this, [=](){ changeFont(5); });
  connect(fontFilename, &QPushButton::pressed, this, [=](){ changeFont(6); });
  connect(fontGCode,    &QPushButton::pressed, this, [=](){ changeFont(7); });
  connect(fontSpeed,    &QPushButton::pressed, this, [=](){ changeFont(8); });
  connect(fontToolDesc, &QPushButton::pressed, this, [=](){ changeFont(9); });
  connect(fontToolNum,  &QPushButton::pressed, this, [=](){ changeFont(10); });
  connect(fontToolNext, &QPushButton::pressed, this, [=](){ changeFont(11); });
  }


void SettingsWidget::changeBackgroundColor(int i) {
  const QColor color = QColorDialog::getColor(Qt::white, this, "Select Background Color", QColorDialog::ShowAlphaChannel);

  if (color.isValid()) settings[i].bg = color;
  refresh();
  }


void SettingsWidget::changeForegroundColor(int i) {
  const QColor color = QColorDialog::getColor(Qt::black, this, "Select Foreground Color");

  if (color.isValid()) settings[i].fg = color;
  refresh();
  }


void SettingsWidget::changeFont(int i) {
  bool  ok;
  QFont font = QFontDialog::getFont(&ok, QFont(settings[i].lbl->text()), this, "Select Font", QFontDialog::ScalableFonts);

  if (ok) settings[i].f = font;
  refresh();
  }


void SettingsWidget::refresh() {
  for (int i=0; i < 12; ++i) {
      QString style = QString("color: #%1; background: #%2;").arg(settings[i].fg.rgb(),  0, 16)
                                                             .arg(settings[i].bg.rgba(), 0, 16);

      settings[i].lbl->setFont(settings[i].f);
      settings[i].lbl->setStyleSheet(style);
      }
  }


/*
 entry:  "actual Codes"
    fg:  "#ff000000"
    bg:  "#fff3f4f5"
     f:  "Sans Serif,9,-1,5,50,0,0,0,0,0"
 entry:  "DRO abs 123,999"
    fg:  "#ff0000ff"
    bg:  "#ffddeeff"
     f:  "Hack,20,-1,5,50,0,0,0,0,0,Regular"
 entry:  "DRO dtg 123,999"
    fg:  "#ffffaa00"
    bg:  "#ffffffdd"
     f:  "Hack,20,-1,5,50,1,0,0,0,0,Italic"
 entry:  "DRO rel 123,999"
    fg:  "#ff00aa00"
    bg:  "#ffddffdd"
     f:  "Hack,20,-1,5,50,0,0,0,0,0,Regular"
 entry:  "DRO Axis: X Y Z"
    fg:  "#ff000000"
    bg:  "#ffffffff"
     f:  "Hack,20,-1,5,75,0,0,0,0,0,Bold"
 entry:  "Feed Info"
    fg:  "#ff000000"
    bg:  "#fff3f4f5"
     f:  "Hack,14,-1,5,50,0,0,0,0,0,Regular"
 entry:  "Filename"
    fg:  "#ff000000"
    bg:  "#fff3f4f5"
     f:  "Sans Serif,9,-1,5,50,0,0,0,0,0"
 entry:  "GCode Editor"
    fg:  "#ff000000"
    bg:  "#ffffffdd"
     f:  "Hack,12,-1,5,50,0,0,0,0,0,Regular"
 entry:  "Speed Info"
    fg:  "#ff000000"
    bg:  "#fff3f4f5"
     f:  "Hack,14,-1,5,50,0,0,0,0,0,Regular"
 entry:  "Tool Description"
    fg:  "#ff000000"
    bg:  "#fff3f4f5"
     f:  "Sans Serif,9,-1,5,50,0,0,0,0,0"
 entry:  "Tool number"
    fg:  "#ff000000"
    bg:  "#ffffffff"
     f:  "Hack,24,-1,5,75,0,0,0,0,0,Bold"
 entry:  "next Toolnum"
    fg:  "#ff000000"
    bg:  "#fff3f4f5"
     f:  "Hack,14,-1,5,50,0,0,0,0,0,Regular"
 */
void SettingsWidget::save() {
  for (int i=0; i < 12; ++i) {
      qDebug() << " entry: " << settings[i].lbl->text();
      qDebug() << "    fg: " << QString("#%1").arg(settings[i].fg.rgb(), 0, 16);
      qDebug() << "    bg: " << QString("#%1").arg(settings[i].bg.rgba(), 0, 16);
      qDebug() << "     f: " << settings[i].f.key();
      }
  }
