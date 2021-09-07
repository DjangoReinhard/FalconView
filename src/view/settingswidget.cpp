#include <settingswidget.h>
#include <QLabel>
#include <QColor>
#include <QFont>
#include <QPushButton>
#include <QColorDialog>
#include <QFontDialog>
#include <QDebug>


SettingsWidget::SettingsWidget(const QString& uiFile, const QString& configFile, QWidget* parent)
 : DynWidget(uiFile, parent)
 , cfg(configFile) {
  initializeWidget();
  }


void SettingsWidget::initializeWidget() {
  labels = new QLabel*[Config::guiSettingEntries];
  labels[0]  = findChild<QLabel*>("actCodesPreview");
  labels[1]  = findChild<QLabel*>("droAbsPreview");
  labels[2]  = findChild<QLabel*>("droDtgPreview");
  labels[3]  = findChild<QLabel*>("droRelPreview");
  labels[4]  = findChild<QLabel*>("droTitlePreview");
  labels[5]  = findChild<QLabel*>("feedPreview");
  labels[6]  = findChild<QLabel*>("filenamePreview");
  labels[7]  = findChild<QLabel*>("gcodePreview");
  labels[8]  = findChild<QLabel*>("speedPreview");
  labels[9]  = findChild<QLabel*>("toolDescPreview");
  labels[10] = findChild<QLabel*>("toolNumPreview");
  labels[11] = findChild<QLabel*>("toolNextPreview");

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

  setupLabels();
  }


void SettingsWidget::setupLabels() {
  ValueManager vm;

  for (int i=0; i < cfg.guiSettingEntries; ++i) {
      connect(vm.getModel("cfgBg" + cfg.guiSettings[i], QColor(Qt::white))
            , &ValueModel::valueChanged
            , this
            , [=](){
                   QString arg = QString("color: #%1; background: #%2;")
                                        .arg(ValueManager().getValue("cfgFg" + cfg.guiSettings[i]).value<QColor>().rgb(), 0, 16)
                                        .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[i]).value<QColor>().rgba(), 0, 16);
                   labels[i]->setStyleSheet(arg);
//                   setLabelStyle(i, arg);
                     });
      connect(vm.getModel("cfgFg" + cfg.guiSettings[i], QColor(Qt::black))
            , &ValueModel::valueChanged
            , this
            , [=](){
                   QString arg = QString("color: #%1; background: #%2;")
                                        .arg(ValueManager().getValue("cfgFg" + cfg.guiSettings[i]).value<QColor>().rgb(), 0, 16)
                                        .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[i]).value<QColor>().rgba(), 0, 16);
                   labels[i]->setStyleSheet(arg);
//                     setLabelStyle(i, arg);
                     });
      connect(vm.getModel("cfgF" + cfg.guiSettings[i], labels[i]->font())
            , &ValueModel::valueChanged
            , this
            , [=](){ labels[i]->setFont(ValueManager().getValue("cfgF" + cfg.guiSettings[i]).value<QFont>()); });
      }
  }


void SettingsWidget::setLabelStyle(int index, const QString &style) {
  labels[index]->setStyleSheet(style);
  }


void SettingsWidget::changeBackgroundColor(int i) {
  const QColor color = QColorDialog::getColor(Qt::white, this, "Select Background Color", QColorDialog::ShowAlphaChannel);

  if (color.isValid()) cfg.setBackground(i, color);
//  refresh();
  }


void SettingsWidget::changeForegroundColor(int i) {
  const QColor color = QColorDialog::getColor(Qt::black, this, "Select Foreground Color");

  if (color.isValid()) cfg.setForeground(i, color);
//  refresh();
  }


void SettingsWidget::changeFont(int i) {
  bool  ok;
  QFont font = QFontDialog::getFont(&ok, QFont(labels[i]->font().family()), this, "Select Font", QFontDialog::ScalableFonts);

  if (ok) cfg.setFont(i, font);
//  refresh();
  }


void SettingsWidget::refresh() {
  for (int i=0; i < 12; ++i) {
      QString style = QString("color: #%1; background: #%2;").arg(cfg.getBackground(i).rgb(),  0, 16)
                                                             .arg(cfg.getForeground(i).rgba(), 0, 16);

      labels[i]->setFont(cfg.getFont(i));
      labels[i]->setStyleSheet(style);
      }
  }


void SettingsWidget::save() {
  cfg.store();
  }
