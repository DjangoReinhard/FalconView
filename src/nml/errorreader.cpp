#include <stat_msg.hh>
#include <cmd_msg.hh>
#include <emc_nml.hh>
#include <nml_oi.hh>
#include <sysevent.h>
#include <insulatePose.h>
#include <errorreader.h>


ErrorReader::ErrorReader(QObject *parent)
 : QObject(parent) {
  ec = new NML(emcFormat, "emcError", "xemc", EMC2_DEFAULT_NMLFILE);
  if (!ec || !ec->valid()) {
     delete ec;
     ec = nullptr;
     throw std::system_error(-3, std::system_category(), "ERROR creating error Channel");
     }
  else if (ec->error_type) {
     throw std::runtime_error(QString("ERROR creating error Channel: #%1").arg(ec->error_type).toStdString().c_str());
     }
  }


SysEvent ErrorReader::fetchMessage() {
  if (!ec || !ec->valid()) throw new std::runtime_error("no error channel to read from!");
  NMLTYPE type = ec->read();
  SysEvent::EventType et;
  char error_buffer[LINELEN];

  switch (type) {
    case EMC_OPERATOR_ERROR_TYPE: {
         et = SysEvent::EventType::OperatorError;
         strncpy(error_buffer, ((EMC_OPERATOR_ERROR*)ec->get_address())->error, LINELEN - 1);
         } break;
    case EMC_OPERATOR_TEXT_TYPE: {
         et = SysEvent::EventType::OperatorText;
         strncpy(error_buffer, ((EMC_OPERATOR_TEXT*)ec->get_address())->text, LINELEN - 1);
         } break;
    case EMC_OPERATOR_DISPLAY_TYPE: {
         et = SysEvent::EventType::OperatorDisplay;
         strncpy(error_buffer, ((EMC_OPERATOR_DISPLAY*)ec->get_address())->display, LINELEN - 1);
         } break;
    case NML_ERROR_TYPE: {
         et = SysEvent::EventType::NMLError;
         strncpy(error_buffer, ((NML_ERROR*)ec->get_address())->error, LINELEN - 1);
         } break;
    case NML_TEXT_TYPE: {
         et = SysEvent::EventType::NMLText;
         strncpy(error_buffer, ((NML_TEXT*)ec->get_address())->text, LINELEN - 1);
         } break;
    case NML_DISPLAY_TYPE: {
         et = SysEvent::EventType::NMLDisplay;
         strncpy(error_buffer, ((NML_DISPLAY*)ec->get_address())->display, LINELEN - 1);
         } break;
    default: {
         et = SysEvent::EventType::NMLError;
         sprintf(error_buffer, "unrecognized error %d", type);
         } break;
    }
  return SysEvent(et, QString(error_buffer));
  }
