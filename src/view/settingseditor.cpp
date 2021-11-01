#include <settingseditor.h>
#include <configacc.h>
#include <QLabel>
#include <QColor>
#include <QFont>
#include <QPushButton>
#include <QColorDialog>
#include <QFontDialog>
#include <QDebug>


SettingsEditor::SettingsEditor(const QString& fileName, QWidget* parent)
 : DynWidget(fileName, parent) {
  setObjectName("SettingsWidget");
  initializeWidget();
  }


SettingsEditor::~SettingsEditor() {
  //delete labels;    
  }


void SettingsEditor::initializeWidget() {
  labels      = new QLabel*[Config().numGuiElements()];
  bgButtons   = new QPushButton*[Config().numGuiElements()];
  fgButtons   = new QPushButton*[Config().numGuiElements()];
  fontButtons = new QPushButton*[Config().numGuiElements()];

  for (int i=0; i < Config().numGuiElements(); ++i) {
      labels[i]      = findChild<QLabel*>(QString("l")         + Config().nameOf(static_cast<Config::GuiElem>(i)));
      bgButtons[i]   = findChild<QPushButton*>(QString("bg")   + Config().nameOf(static_cast<Config::GuiElem>(i)));
      fgButtons[i]   = findChild<QPushButton*>(QString("fg")   + Config().nameOf(static_cast<Config::GuiElem>(i)));
      fontButtons[i] = findChild<QPushButton*>(QString("font") + Config().nameOf(static_cast<Config::GuiElem>(i)));
      }
  }


void SettingsEditor::connectSignals() {
  for (int i=0; i < Config().numGuiElements(); ++i) {
      connect(bgButtons[i],   &QPushButton::pressed, this, [=](){ changeBackgroundColor(i); });
      connect(fgButtons[i],   &QPushButton::pressed, this, [=](){ changeForegroundColor(i); });
      if (fontButtons[i]) connect(fontButtons[i], &QPushButton::pressed, this, [=](){ changeFont(i); });
      }
  }


void SettingsEditor::updateStyles() {
  setupLabels();
  }


void SettingsEditor::setupLabels() {
  ValueManager vm;
  Config cfg;
  QString keyBg, keyFg, keyF;
  QColor colBg;
  QColor colFg;
  QFont font;

  for (int i=0; i < cfg.numGuiElements(); ++i) {
      keyBg = QString("cfgBg") + cfg.nameOf(static_cast<Config::GuiElem>(i));
      colBg = cfg.value(keyBg, QColor(Qt::white)).value<QColor>();
      keyFg = QString("cfgFg") + cfg.nameOf(static_cast<Config::GuiElem>(i));
      colFg = cfg.value(keyFg, QColor(Qt::black)).value<QColor>();
      keyF  = QString("cfgF") + cfg.nameOf(static_cast<Config::GuiElem>(i));
      font  = cfg.value(keyF, QFont("Hack", 12)).value<QFont>();

      connect(vm.getModel(keyBg, colBg)
            , &ValueModel::valueChanged
            , labels[i]
            , [=](){
                   QString arg = QString("color: #%1; background: #%2;")
                                        .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(static_cast<Config::GuiElem>(i))).value<QColor>().rgb(), 0, 16)
                                        .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(static_cast<Config::GuiElem>(i))).value<QColor>().rgba(), 0, 16);
                   labels[i]->setStyleSheet(arg);
                     });
      connect(vm.getModel(keyFg, QColor(Qt::black))
            , &ValueModel::valueChanged
            , labels[i]
            , [=](){
                   QString arg = QString("color: #%1; background: #%2;")
                                        .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(static_cast<Config::GuiElem>(i))).value<QColor>().rgb(), 0, 16)
                                        .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(static_cast<Config::GuiElem>(i))).value<QColor>().rgba(), 0, 16);
                   labels[i]->setStyleSheet(arg);
                     });
      connect(vm.getModel("cfgF" + cfg.nameOf(static_cast<Config::GuiElem>(i)), labels[i]->font())
            , &ValueModel::valueChanged
            , labels[i]
            , [=](){ labels[i]->setFont(ValueManager().getValue("cfgF" + cfg.nameOf(static_cast<Config::GuiElem>(i))).value<QFont>()); });

      labels[i]->setStyleSheet(QString("color: #%1; background: #%2;")
                               .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(static_cast<Config::GuiElem>(i))).value<QColor>().rgb(), 0, 16)
                               .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(static_cast<Config::GuiElem>(i))).value<QColor>().rgba(), 0, 16));
      labels[i]->setFont(font);
      }
  }


void SettingsEditor::changeBackgroundColor(int i) {
  const QColor oc    = Config().getBackground(static_cast<Config::GuiElem>(i));
  const QColor color = QColorDialog::getColor(oc
                                            , this
                                            , "Select Background Color"
                                            , QColorDialog::ShowAlphaChannel);

  if (color.isValid()) Config().setBackground(static_cast<Config::GuiElem>(i), color);
  }


void SettingsEditor::changeForegroundColor(int i) {
  const QColor oc    = Config().getForeground(static_cast<Config::GuiElem>(i));
  const QColor color = QColorDialog::getColor(oc
                                            , this
                                            , "Select Foreground Color");

  if (color.isValid()) Config().setForeground(static_cast<Config::GuiElem>(i), color);
  }


void SettingsEditor::changeFont(int i) {
  bool  ok;
  QFont of   = Config().getFont(static_cast<Config::GuiElem>(i));
  QFont font = QFontDialog::getFont(&ok
                                  , of
                                  , this
                                  , "Select Font"
                                  , QFontDialog::ScalableFonts);

  if (ok) Config().setFont(static_cast<Config::GuiElem>(i), font);
  }
