#include <pweditor.h>
#include <valuemanager.h>
#include <config.h>
#include <gcodeeditor.h>
#include <gcodehighlighter.h>
#include <QSplitter>
#include <QLabel>
#include <QVariant>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QPushButton>


PreViewEditor::PreViewEditor(const QString& fileName, QWidget* parent)
 : DynWidget(parent) {
  this->setStyleSheet("background: 0xFF0000;");
  setLayout(new QHBoxLayout);
  spV = new QSplitter(Qt::Vertical);
  QLabel* dummy = new QLabel(tr("Platzhalter"));

  dummy->setTextFormat(Qt::MarkdownText);
  dummy->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
  dummy->setWordWrap(true);
  dummy->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard
                               | Qt::LinksAccessibleByMouse
                               | Qt::TextBrowserInteraction
                               | Qt::TextSelectableByKeyboard
                               | Qt::TextSelectableByMouse);
  QWidget* w = loadFromUI(fileName);

//  dummy->setMargin(25);
  spV->addWidget(dummy);
  spV->addWidget(w);
  fn     = w->findChild<QLineEdit*>("fileName");
  pbOpen = w->findChild<QPushButton*>("pbOpen");
  pbSave = w->findChild<QPushButton*>("pbSave");
  QGridLayout* gl = w->findChild<QGridLayout*>("gridLayout");
  QWidget* placeHolder = w->findChild<QWidget*>("widget");

  ed     = new GCodeEditor(this);
  gh     = new GCodeHighlighter(ed->document());
  gl->addWidget(ed, 1, 0, 1, 3);
  placeHolder->hide();
  layout()->addWidget(spV);
  connectSignals();
  updateStyles();
  }


void PreViewEditor::connectSignals() {
    ValueManager vm;
    Config       cfg;

    connect(vm.getModel("fileName", " "), &ValueModel::valueChanged, this, &PreViewEditor::loadFile);
    connect(vm.getModel(QString("cfgBg" + cfg.guiSettings[6]), QColor(Qt::white))
          , &ValueModel::valueChanged
          , fn
          , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                        .arg(ValueManager().getValue("cfgFg" + cfg.guiSettings[6]).value<QColor>().rgb(), 0, 16)
                                        .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[6]).value<QColor>().rgba(), 0, 16);
                   fn->setStyleSheet(arg);
                   });
    connect(vm.getModel(QString("cfgFg" + cfg.guiSettings[6]), QColor(Qt::black))
          , &ValueModel::valueChanged
          , fn
          , [=](){ QString arg = QString("color: #%1; background: #%2;")
                                        .arg(ValueManager().getValue("cfgFg" + cfg.guiSettings[6]).value<QColor>().rgb(), 0, 16)
                                        .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[6]).value<QColor>().rgba(), 0, 16);
                   fn->setStyleSheet(arg);
                   });
    connect(vm.getModel(QString("cfgF" + cfg.guiSettings[6]), fn->font())
          , &ValueModel::valueChanged
          , fn
          , [=](){ fn->setFont(ValueManager().getValue("cfgF" + cfg.guiSettings[6]).value<QFont>());
                   });

    connect(vm.getModel(QString("cfgBg" + cfg.guiSettings[7]), QColor(Qt::white))
          , &ValueModel::valueChanged
          , ed
          , [=](){ QString arg = QString("background: #%2;")
                                        .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[7]).value<QColor>().rgba(), 0, 16);
                   ed->setStyleSheet(arg);
                   });
    connect(vm.getModel(QString("cfgF" + cfg.guiSettings[7]), ed->font())
          , &ValueModel::valueChanged
          , ed
          , [=](){ ed->setFont(ValueManager().getValue("cfgF" + cfg.guiSettings[7]).value<QFont>());
                   });
  }


void PreViewEditor::loadFile(const QVariant& fileName) {
  ed->loadFile(fileName);
  fn->setText(fileName.toString());
  }


void PreViewEditor::updateStyles() {
    ValueManager vm;
    Config       cfg;

    fn->setStyleSheet(QString("color: #%1; background: #%2;")
                                   .arg(ValueManager().getValue("cfgFg" + cfg.guiSettings[6]).value<QColor>().rgb(), 0, 16)
                                   .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[6]).value<QColor>().rgba(), 0, 16));
    fn->setFont(vm.getValue("cfgF"  + cfg.guiSettings[6]).value<QFont>());
    ed->setStyleSheet(QString("background: #%2;")
                                 .arg(ValueManager().getValue("cfgBg" + cfg.guiSettings[7]).value<QColor>().rgba(), 0, 16));
    ed->setFont(vm.getValue("cfgF"  + cfg.guiSettings[7]).value<QFont>());
  }
