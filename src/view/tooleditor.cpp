#include <tooleditor.h>
#include <toolmodel.h>
#include <dbconnection.h>
#include <ui_ToolEditor.h>
#include <QDebug>
#include <QComboBox>
#include <QSqlError>
#include <QSqlRecord>


ToolEditor::ToolEditor(QWidget *parent)
 : QWidget(parent)
 , ui(new Ui::Form)
 , model(new QSqlQueryModel) {
  if (!DBConnection("toolTable").connect()) {
     throw new QSqlError("failed to open database!");
     }
  model->setQuery("select id, name from Category");
  dumpModel();
  ui->setupUi(this);
  }


void ToolEditor::dumpModel() {
  for (int i=0; i < model->rowCount(); ++i) {
      qDebug() << "category #" << i << " with id: " << model->record(i).value("id") << "->"
                                                    << model->record(i).value("name");
      }
  }


void ToolEditor::getChanges(QSqlRecord& r) {
  QAbstractItemModel* m = ui->cbType->model();
  int    idx = ui->cbType->currentIndex();
  int    iv;
  bool   ok;
  double dv;
  double lenTool = 0;
  QVariant   v0 = m->data(m->index(idx, 0));
  QVariant   v1 = m->data(m->index(idx, 1));

  qDebug() << "category at #" << idx << "v0" << v0 << "v1" << v1;

  if (toolId < 0) {                         // neg. toolId signals new record
     iv = ui->toolNum->text().toInt(&ok);   // so we need to read tool-number
     if (ok) r.setValue("num", iv);
     }
  iv = v0.toInt(&ok);
  if (ok) r.setValue("type", iv);
  iv = ui->eFlutes->text().toInt(&ok);
  if (ok) r.setValue("flutes", iv);
  dv = ui->eLenCut->text().toDouble(&ok);
  if (ok) r.setValue("lenCut", dv);
  dv = ui->eLenFree->text().toDouble(&ok);
  if (ok) {
     r.setValue("lenFree", dv);
     lenTool += dv;
     }
  dv = ui->eDiaTip->text().toDouble(&ok);
  if (ok) r.setValue("diaTip", dv);
  dv = ui->eAngMaxRamp->text().toDouble(&ok);
  if (ok) r.setValue("angMaxRamp", dv);
  dv = ui->eAngCut->text().toDouble(&ok);
  if (ok) r.setValue("angCut", dv);
  dv = ui->eLenFlute->text().toDouble(&ok);
  if (ok) r.setValue("lenFlute", dv);
  dv = ui->eLoad->text().toDouble(&ok);
  if (ok) r.setValue("load", dv);
  dv = ui->eAngSlope->text().toDouble(&ok);
  if (ok) r.setValue("angSlope", dv);
  dv = ui->eDiaColl->text().toDouble(&ok);
  if (ok) r.setValue("diaColl", dv);
  dv = ui->eAngHelix->text().toDouble(&ok);
  if (ok) r.setValue("angHelix", dv);
  dv = ui->eLenColl->text().toDouble(&ok);
  if (ok) {
     r.setValue("lenColl", dv);
     lenTool += dv;
     }
  dv = ui->eDiaFlute->text().toDouble(&ok);
  if (ok) r.setValue("diaFlute", dv);
  dv = ui->eLenTool->text().toDouble(&ok);
  if (ok) r.setValue("lenTool", dv);
  dv = ui->eDiaShank->text().toDouble(&ok);
  r.setValue("diaShank", dv);
  r.setValue("lenTool", lenTool);

  r.setValue("name",     ui->eName->text());
  r.setValue("partCode", ui->ePartCode->text());
  r.setValue("material", ui->eMaterial->text());
  r.setValue("coating",  ui->eCoating->text());

  r.setValue("comment",  ui->eComment->document()->toPlainText());
  }


void ToolEditor::changeEvent(QEvent* e) {
  if (e->type() == QEvent::EnabledChange && this->isEnabled()) {
     ui->eName->setFocus();
     }
  }


void ToolEditor::selectCBEntry(QComboBox* cb, const QString& name) {
  for (int i=0; i < cb->count(); ++i) {
      qDebug() << "cb-entry: " << cb->itemText(i) << " <> name:" << name;
      if (!cb->itemText(i).compare(name)) cb->setCurrentIndex(i);
      }
  }


void ToolEditor::setModel(const QSqlRecord& r) {
  qDebug() << "ToolEditor::setModel() - tool #" << r.value("num") << " " << r.value("name");

  toolId = r.value("id").isNull() ? -1 : r.value("id").toInt();
  ui->toolNum->setText(r.value("num").toString());
  ui->cbType->setModel(model);
  ui->cbType->setModelColumn(1);
  ui->cbType->setCurrentIndex(r.value("type").toInt() - 1);
  ui->eComment->setPlainText(r.value("comment").toString());
  ui->eLenCut->setText(r.value("lenCut").toString());
  ui->eLenFree->setText(r.value("lenFree").toString());
  ui->eDiaTip->setText(r.value("diaTip").toString());
  ui->eAngMaxRamp->setText(r.value("angMaxRamp").toString());
  ui->eAngCut->setText(r.value("angCut").toString());
  ui->eLenFlute->setText(r.value("lenFlute").toString());
  ui->eFlutes->setText(r.value("flutes").toString());
  ui->eLoad->setText(r.value("load").toString());
  ui->eAngSlope->setText(r.value("angSlope").toString());
  ui->eDiaColl->setText(r.value("diaColl").toString());
  ui->eAngHelix->setText(r.value("angHelix").toString());
  ui->eLenColl->setText(r.value("lenColl").toString());
  ui->eDiaFlute->setText(r.value("diaFlute").toString());
  ui->eLenTool->setText(r.value("lenTool").toString());
  ui->eName->setText(r.value("name").toString());
  ui->ePartCode->setText(r.value("partCode").toString());
  ui->eDiaShank->setText(r.value("diaShank").toString());
  ui->eMaterial->setText(r.value("material").toString());
  ui->eCoating->setText(r.value("coating").toString());
  }
