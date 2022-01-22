#include "preferenceseditor.h"
#include <configacc.h>
#include <valuemanager.h>
#include <QLineEdit>
#include <QColor>
#include <QFont>
#include <QShowEvent>
#include <QCheckBox>
#include <QPushButton>
#include <QMessageBox>
#include <QColorDialog>
#include <QFontDialog>
#include <QDebug>


PreferencesEditor::PreferencesEditor(QWidget* parent)
 : AbstractCenterWidget(":Settings.ui", true, parent)
 , labels(nullptr)
 , bgButtons(nullptr)
 , fontButtons(nullptr)
 , cbStatesInside(nullptr)
 , cbHelp(nullptr)
 , cbPreviewCenter(nullptr)
 , count(0) {
  setWindowTitle("PreferencesEditor");
  setObjectName(tr("PreferencesEditor"));

  }


PreferencesEditor::~PreferencesEditor() {
  }


QWidget* PreferencesEditor::createContent() {
  QWidget* rv = AbstractCenterWidget::createContent();

  count       = cfg->numGuiElements();
  labels      = new QLineEdit*[count];
  bgButtons   = new QPushButton*[count];
  fgButtons   = new QPushButton*[count];
  fontButtons = new QPushButton*[count];

  cbStatesInside  = findChild<QCheckBox*>("cbStatesInside");
  cbHelp          = findChild<QCheckBox*>("cbHelp");
  cbPreviewCenter = findChild<QCheckBox*>("cbPreviewCenter");
  for (int i=0; i < count; ++i) {
      labels[i]      = findChild<QLineEdit*>(QString("l")      + cfg->nameOf(static_cast<Config::GuiElem>(i)));
      bgButtons[i]   = findChild<QPushButton*>(QString("bg")   + cfg->nameOf(static_cast<Config::GuiElem>(i)));
      fgButtons[i]   = findChild<QPushButton*>(QString("fg")   + cfg->nameOf(static_cast<Config::GuiElem>(i)));
      fontButtons[i] = findChild<QPushButton*>(QString("font") + cfg->nameOf(static_cast<Config::GuiElem>(i)));
      if (labels[i]) labels[i]->installEventFilter(this);
      }
  return rv;
  }


void PreferencesEditor::connectSignals() {
  for (int i=0; i < count; ++i) {
      if (bgButtons[i])   connect(bgButtons[i],   &QPushButton::pressed, this, [=](){ changeBackgroundColor(i); });
      if (fgButtons[i])   connect(fgButtons[i],   &QPushButton::pressed, this, [=](){ changeForegroundColor(i); });
      if (fontButtons[i]) connect(fontButtons[i], &QPushButton::pressed, this, [=](){ changeFont(i); });
      }
  if (cbStatesInside) {
     cbStatesInside->setChecked(cfg->value("statusInPreview").toBool());
     connect(cbStatesInside, &QCheckBox::stateChanged, this, &PreferencesEditor::statusInsideChanged);
     }
  if (cbHelp) {
     cbHelp->setChecked(cfg->value("showHelpAtPageChange").toBool());
     connect(cbHelp, &QCheckBox::stateChanged, this, &PreferencesEditor::statusShowHelpChanged);
     }
  if (cbPreviewCenter) {
     cbPreviewCenter->setChecked(cfg->value("previewIsCenter").toBool());
     connect(cbPreviewCenter, &QCheckBox::stateChanged, this, &PreferencesEditor::previewCenterChanged);
     }
  }


void PreferencesEditor::updateStyles() {
  setupLabels();
  }


void PreferencesEditor::showEvent(QShowEvent* e) {
  AbstractCenterWidget::showEvent(e);
  if (e->type() == QEvent::Show && labels[0]) {
     labels[0]->setFocus();
     }
  }


void PreferencesEditor::setupLabels() {
  QString keyBg, keyFg, keyF;
  QColor colBg;
  QColor colFg;
  QFont font;

  for (int i=0; i < count; ++i) {
      keyBg = QString("cfgBg") + cfg->nameOf(static_cast<Config::GuiElem>(i));
      colBg = cfg->value(keyBg, QColor(204, 205, 206)).value<QColor>();
      keyFg = QString("cfgFg") + cfg->nameOf(static_cast<Config::GuiElem>(i));
      colFg = cfg->value(keyFg, QColor(Qt::black)).value<QColor>();
      keyF  = QString("cfgF") + cfg->nameOf(static_cast<Config::GuiElem>(i));
      font  = cfg->value(keyF, QFont("Hack", 12)).value<QFont>();
      vm->setValue(keyBg, colBg);
      vm->setValue(keyFg, colFg);
      vm->setValue(keyF,  font);

      connect(vm->getModel(keyBg, colBg)
            , &ValueModel::valueChanged
            , labels[i]
            , [=](){
                   QString arg = QString("color: #%1; background: #%2;")
                                        .arg(vm->getValue("cfgFg" + cfg->nameOf(static_cast<Config::GuiElem>(i))).value<QColor>().rgb(), 0, 16)
                                        .arg(vm->getValue("cfgBg" + cfg->nameOf(static_cast<Config::GuiElem>(i))).value<QColor>().rgba(), 0, 16);
                   labels[i]->setStyleSheet(arg);
                     });
      connect(vm->getModel(keyFg, QColor(Qt::black))
            , &ValueModel::valueChanged
            , labels[i]
            , [=](){
                   QString arg = QString("color: #%1; background: #%2;")
                                        .arg(vm->getValue("cfgFg" + cfg->nameOf(static_cast<Config::GuiElem>(i))).value<QColor>().rgb(), 0, 16)
                                        .arg(vm->getValue("cfgBg" + cfg->nameOf(static_cast<Config::GuiElem>(i))).value<QColor>().rgba(), 0, 16);
                   labels[i]->setStyleSheet(arg);
                     });
      connect(vm->getModel("cfgF" + cfg->nameOf(static_cast<Config::GuiElem>(i)), labels[i]->font())
            , &ValueModel::valueChanged
            , labels[i]
            , [=](){ labels[i]->setFont(vm->getValue("cfgF" + cfg->nameOf(static_cast<Config::GuiElem>(i))).value<QFont>()); });

      QString ss = QString("color: #%1; background: #%2;")
                          .arg(vm->getValue("cfgFg" + cfg->nameOf(static_cast<Config::GuiElem>(i))).value<QColor>().rgb(), 0, 16)
                          .arg(vm->getValue("cfgBg" + cfg->nameOf(static_cast<Config::GuiElem>(i))).value<QColor>().rgba(), 0, 16);
      labels[i]->setStyleSheet(ss);
      labels[i]->setFont(font);
      }
  }


void PreferencesEditor::changeBackgroundColor(int i) {
  const QColor oc    = cfg->getBackground(static_cast<Config::GuiElem>(i));
  const QColor color = QColorDialog::getColor(oc
                                            , this
                                            , "Select Background Color"
                                            , QColorDialog::ShowAlphaChannel);

  if (color.isValid()) cfg->setBackground(static_cast<Config::GuiElem>(i), color);
  }


void PreferencesEditor::changeForegroundColor(int i) {
  const QColor oc    = cfg->getForeground(static_cast<Config::GuiElem>(i));
  const QColor color = QColorDialog::getColor(oc
                                            , this
                                            , "Select Foreground Color");

  if (color.isValid()) cfg->setForeground(static_cast<Config::GuiElem>(i), color);
  }


void PreferencesEditor::changeFont(int i) {
  bool  ok;
  QFont of   = cfg->getFont(static_cast<Config::GuiElem>(i));
  QFont font = QFontDialog::getFont(&ok
                                  , of
                                  , this
                                  , "Select Font"
                                  , QFontDialog::ScalableFonts);

  if (ok) cfg->setFont(static_cast<Config::GuiElem>(i), font);
  }


void PreferencesEditor::statusInsideChanged(const QVariant& state) {
  qDebug() << "PE::statusInsideChanged(" << (state.toBool() ? "TRUE" : "FALSE") << ")";
  QMessageBox::information(this
                         , tr("QMessageBox::information()")
                         , tr("for this change to take effect, "
                              "the application must be restarted."));
  cfg->setValue("statusInPreview", state.toBool());
  }


void PreferencesEditor::statusShowHelpChanged(const QVariant& state) {
  bool showHelp = state.toBool();

  qDebug() << "PE::statusShowHelpChanged(" << (showHelp ? "TRUE" : "FALSE") << ")";
  if (!showHelp) {
     QMessageBox::information(this
                            , tr("QMessageBox::information()")
                            , tr("You can rise help window at any "
                                 "time hitting [F1] key."));
     }
  cfg->setValue("showHelpAtPageChange", state.toBool());
  }


void PreferencesEditor::previewCenterChanged(const QVariant& state) {
  bool previewIsCenter = state.toBool();

  qDebug() << "PE::previewCenterChanged(" << (previewIsCenter ? "TRUE" : "FALSE") << ")";
  QMessageBox::information(this
                         , tr("QMessageBox::information()")
                         , tr("for this change to take effect, "
                              "the application must be restarted."));
  cfg->setValue("previewIsCenter", state.toBool());
  }


bool PreferencesEditor::eventFilter(QObject* l, QEvent* event) {
  if (event->type() == QEvent::KeyPress) {
    QKeyEvent* e = static_cast<QKeyEvent*>(event);

    if (!e) return false;
    switch (e->key()) {
      case Qt::Key_B:
      case Qt::Key_F:
      case Qt::Key_C:
           if (e->modifiers() == Qt::AltModifier) {
              int idGuiElem = -1;

              for (int i=0; i < count; ++i) {
                  if (l == labels[i]) {
                     idGuiElem = i;
                     break;
                     }
                  }
              if (idGuiElem < 0) return false;
              switch (e->key()) {
                case Qt::Key_B: bgButtons[idGuiElem]->click(); break;
                case Qt::Key_F: fontButtons[idGuiElem]->click(); break;
                case Qt::Key_C: fgButtons[idGuiElem]->click(); break;
                default: return false;
                }
              return true;
              }
      default: break;
      }
    }
  return false;
  }
