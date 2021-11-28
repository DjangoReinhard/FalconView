#include <preferenceseditor.h>
#include <configacc.h>
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


PreferencesEditor::PreferencesEditor(const QString& fileName, QWidget* parent)
 : DynCenterWidget(fileName, tr("SettingsEditor"), true, parent)
 , count(Config().numGuiElements()) {
  setWindowTitle(PreferencesEditor::className);
  setObjectName(PreferencesEditor::className);
  }


PreferencesEditor::~PreferencesEditor() {
  }


QWidget* PreferencesEditor::createContent() {
  QWidget* rv = DynCenterWidget::createContent();

  labels      = new QLineEdit*[count];
  bgButtons   = new QPushButton*[count];
  fgButtons   = new QPushButton*[count];
  fontButtons = new QPushButton*[count];

  cbStatesInside = findChild<QCheckBox*>("cbStatesInside");
  for (int i=0; i < count; ++i) {
      labels[i]      = findChild<QLineEdit*>(QString("l")      + Config().nameOf(static_cast<Config::GuiElem>(i)));
      bgButtons[i]   = findChild<QPushButton*>(QString("bg")   + Config().nameOf(static_cast<Config::GuiElem>(i)));
      fgButtons[i]   = findChild<QPushButton*>(QString("fg")   + Config().nameOf(static_cast<Config::GuiElem>(i)));
      fontButtons[i] = findChild<QPushButton*>(QString("font") + Config().nameOf(static_cast<Config::GuiElem>(i)));
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
     cbStatesInside->setChecked(Config().value("statusInPreview").toBool());
     connect(cbStatesInside, &QCheckBox::stateChanged, this, &PreferencesEditor::statusInsideChanged);
     }
  }


void PreferencesEditor::updateStyles() {
  setupLabels();
  }


void PreferencesEditor::showEvent(QShowEvent* e) {
  if (e->type() == QEvent::Show && labels[0]) {
     labels[0]->setFocus();
     }
  }


void PreferencesEditor::setupLabels() {
  ValueManager vm;
  Config cfg;
  QString keyBg, keyFg, keyF;
  QColor colBg;
  QColor colFg;
  QFont font;

  for (int i=0; i < count; ++i) {
      keyBg = QString("cfgBg") + cfg.nameOf(static_cast<Config::GuiElem>(i));
      colBg = cfg.value(keyBg, QColor(204, 205, 206)).value<QColor>();
      keyFg = QString("cfgFg") + cfg.nameOf(static_cast<Config::GuiElem>(i));
      colFg = cfg.value(keyFg, QColor(Qt::black)).value<QColor>();
      keyF  = QString("cfgF") + cfg.nameOf(static_cast<Config::GuiElem>(i));
      font  = cfg.value(keyF, QFont("Hack", 12)).value<QFont>();
      vm.setValue(keyBg, colBg);
      vm.setValue(keyFg, colFg);
      vm.setValue(keyF,  font);

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

      QString ss = QString("color: #%1; background: #%2;")
                          .arg(ValueManager().getValue("cfgFg" + cfg.nameOf(static_cast<Config::GuiElem>(i))).value<QColor>().rgb(), 0, 16)
                          .arg(ValueManager().getValue("cfgBg" + cfg.nameOf(static_cast<Config::GuiElem>(i))).value<QColor>().rgba(), 0, 16);
//      qDebug() << cfg.nameOf(static_cast<Config::GuiElem>(i)) << " => " << ss << " <= ";
      labels[i]->setStyleSheet(ss);
      labels[i]->setFont(font);
      }
  }


void PreferencesEditor::changeBackgroundColor(int i) {
  const QColor oc    = Config().getBackground(static_cast<Config::GuiElem>(i));
  const QColor color = QColorDialog::getColor(oc
                                            , this
                                            , "Select Background Color"
                                            , QColorDialog::ShowAlphaChannel);

  if (color.isValid()) Config().setBackground(static_cast<Config::GuiElem>(i), color);
  }


void PreferencesEditor::changeForegroundColor(int i) {
  const QColor oc    = Config().getForeground(static_cast<Config::GuiElem>(i));
  const QColor color = QColorDialog::getColor(oc
                                            , this
                                            , "Select Foreground Color");

  if (color.isValid()) Config().setForeground(static_cast<Config::GuiElem>(i), color);
  }


void PreferencesEditor::changeFont(int i) {
  bool  ok;
  QFont of   = Config().getFont(static_cast<Config::GuiElem>(i));
  QFont font = QFontDialog::getFont(&ok
                                  , of
                                  , this
                                  , "Select Font"
                                  , QFontDialog::ScalableFonts);

  if (ok) Config().setFont(static_cast<Config::GuiElem>(i), font);
  }


void PreferencesEditor::statusInsideChanged(QVariant state) {
  qDebug() << "PE::statusInsideChanged(" << (state.toBool() ? "TRUE" : "FALSE") << ")";
  QMessageBox::information(this
                         , tr("QMessageBox::information()")
                         , tr("for this change to take effect, "
                              "the application must be restarted."));
  Config().setValue("statusInPreview", state.toBool());
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


const QString& PreferencesEditor::className = "PreferencesEditor";
