/* 
 * **************************************************************************
 * 
 *  file:       errorreader.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    19.1.2022 by Django Reinhard
 *  copyright:  (c) 2022 Django Reinhard -  all rights reserved
 * 
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 2 of the License, or 
 *  (at your option) any later version. 
 *   
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details. 
 *   
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * **************************************************************************
 */
#include <stat_msg.hh>
#include <cmd_msg.hh>
#include <emc_nml.hh>
#include <nml_oi.hh>
#include <sysevent.h>
#include <config.h>
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


void ErrorReader::check4Error() {
  if (!ec || !ec->valid())
     throw new SysEvent(SysEvent::EventType::SystemError, "no error channel to read from!");
  NMLTYPE type = ec->read();

  if (type) throw fetchMessage(type);
  }


SysEvent* ErrorReader::fetchMessage(int type) {
  if (!ec || !ec->valid()) throw new std::runtime_error("no error channel to read from!");
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
  return new SysEvent(et, QString(error_buffer));
  }
