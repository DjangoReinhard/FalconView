#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "axismask.h"
#include "positionwidget.h"
#include "gcodehighlighter.h"
#include <QTimer>
#include <QDockWidget>
#include <QtUiTools/QUiLoader>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include <math.h>


MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent)
 , ui(new Ui::MainWindow)
 , counter(0.0)
 , gh(nullptr) {
  // load widgets from ui-file
  ui->setupUi(this);

  // load docking window
  QFile file("../QtScreen/Position.ui");

  pos = new PositionWidget(file, AxisMask(0x01FF), this);
  pos->setAllowedAreas(Qt::AllDockWidgetAreas);
  addDockWidget(Qt::LeftDockWidgetArea, pos);

  // connect model with view
  connect(&pm.getXAbs(), &ValueModel::valueChanged, pos->getXAbs(), &LabelAdapter::setValue);
  connect(&pm.getYAbs(), &ValueModel::valueChanged, pos->getYAbs(), &LabelAdapter::setValue);
  connect(&pm.getZAbs(), &ValueModel::valueChanged, pos->getZAbs(), &LabelAdapter::setValue);
  connect(&pm.getAAbs(), &ValueModel::valueChanged, pos->getAAbs(), &LabelAdapter::setValue);
  connect(&pm.getBAbs(), &ValueModel::valueChanged, pos->getBAbs(), &LabelAdapter::setValue);
  connect(&pm.getCAbs(), &ValueModel::valueChanged, pos->getCAbs(), &LabelAdapter::setValue);
  connect(&pm.getUAbs(), &ValueModel::valueChanged, pos->getUAbs(), &LabelAdapter::setValue);
  connect(&pm.getVAbs(), &ValueModel::valueChanged, pos->getVAbs(), &LabelAdapter::setValue);
  connect(&pm.getWAbs(), &ValueModel::valueChanged, pos->getWAbs(), &LabelAdapter::setValue);

  connect(&pm.getXRel(), &ValueModel::valueChanged, pos->getXRel(), &LabelAdapter::setValue);
  connect(&pm.getYRel(), &ValueModel::valueChanged, pos->getYRel(), &LabelAdapter::setValue);
  connect(&pm.getZRel(), &ValueModel::valueChanged, pos->getZRel(), &LabelAdapter::setValue);
  connect(&pm.getARel(), &ValueModel::valueChanged, pos->getARel(), &LabelAdapter::setValue);
  connect(&pm.getBRel(), &ValueModel::valueChanged, pos->getBRel(), &LabelAdapter::setValue);
  connect(&pm.getCRel(), &ValueModel::valueChanged, pos->getCRel(), &LabelAdapter::setValue);
  connect(&pm.getURel(), &ValueModel::valueChanged, pos->getURel(), &LabelAdapter::setValue);
  connect(&pm.getVRel(), &ValueModel::valueChanged, pos->getVRel(), &LabelAdapter::setValue);
  connect(&pm.getWRel(), &ValueModel::valueChanged, pos->getWRel(), &LabelAdapter::setValue);

  QAction* aYes = ui->actionoder_doch;
  QAction* aNo  = ui->actionnicht;

  connect(aNo, &QAction::triggered, pos, &PositionWidget::setRelative);
  connect(aYes, &QAction::triggered, pos, &PositionWidget::setAbsolute);
  connect(ui->pbOpen, &QPushButton::clicked, this, &MainWindow::loadFile);

  QFont font;

  font.setFamily("Hack");
  font.setFixedPitch(true);
  font.setPointSize(10);

  ui->tbCode->setFont(font);
  gh = new GCodeHighlighter(ui->tbCode->document());

  // for testing purpose only!
  // start simple timer as base of changes
  QTimer* t = new QTimer(this);

  connect(t, &QTimer::timeout, this, &MainWindow::count);
  t->start(5);

  // test data
  pos->setXHomed();
  pos->setYHomed();
  pos->setZHomed();

  this->setMinimumWidth(1200);
  }


MainWindow::~MainWindow() {
  delete ui;
  delete pos;
  delete gh;
  }


void MainWindow::count() {
  counter.setValue(counter.getValue().toDouble() + 0.001);
  pm.getXRel().setValue(2000 * sin(counter.getValue().toDouble()));
  pm.getYRel().setValue(2000 * cos(counter.getValue().toDouble()));
  pm.getXAbs().setValue(2000 * sin(counter.getValue().toDouble()));
  pm.getYAbs().setValue(2000 * cos(counter.getValue().toDouble()));
  }


void MainWindow::loadFile() {
  QFileDialog fileDialog(this, tr("Open File..."));

  fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
  fileDialog.setFileMode(QFileDialog::ExistingFile);
  fileDialog.setMimeTypeFilters(QStringList() << "text/plain");
  int rv = fileDialog.exec();

  if (rv != QDialog::Accepted) return;
  const QString fn = fileDialog.selectedFiles().first();

  qDebug() << "should load file: [" << fn << "]";
  QFile file(fn);

  if (file.open(QFile::ReadOnly | QFile::Text))
     ui->tbCode->setText(file.readAll());
  }
