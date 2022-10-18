/* 
 * **************************************************************************
 * 
 *  file:       halpin.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    23.1.2022 by Django Reinhard
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
#include "halpin.h"
#include "halsignal.h"
#include <rtapi.h>
#include <hal.h>
#include <hal_priv.h>
#include <QVariant>


HalPin::HalPin(int pin, HalElement* parent)
 : HalElement(parent)
 , sig(nullptr) {
  hal_pin_t* pPin = static_cast<hal_pin_t*>((void*)(hal_shmem_base + pin));
  name = pPin->name;
  if (pPin->signal) sig = new HalSignal(pPin->signal, this);
  p = pPin;
//  hal_type_t  type = HAL_TYPE_UNINITIALIZED;
//  hal_data_u* ptr;
//  bool        conn;

//  if (hal_get_pin_value_by_name(name, &type, &ptr, &conn) == 0) {
//     if (!conn)
//        logOword("%s: no signal connected", name);
//     goto assign;
//     }
//  if (hal_get_signal_value_by_name(name, &type, &ptr, &conn) == 0) {
//     if (!conn)
//        logOword("%s: signal has no writer", name);
//     goto assign;
//     }
//  if (hal_get_param_value_by_name(name, &type, &ptr) == 0) {
//     goto assign;
//     }
//assign:
//  switch (type) {
//    case HAL_BIT:   value = (double) (ptr->b); break;
//    case HAL_U32:   value = (double) (ptr->u); break;
//    case HAL_S32:   value = (double) (ptr->s); break;
//    case HAL_FLOAT: value = (double) (ptr->f); break;
//    default:        value = 0;
//    }
  }


HalPin::~HalPin() {
  }


double HalPin::value() const {
  hal_pin_t*  pin  = static_cast<hal_pin_t*>(p);
  hal_data_u* data = &(pin->dummysig);

  if (pin->signal != 0) return sig->data(1).toDouble();
  return (double) data->f;
  }


QString HalPin::dirName(int pinDir) const {
  if (pinDir == HAL_IN)       return "IN ";
  else if (pinDir == HAL_OUT) return "OUT";
  else if (pinDir == HAL_IO)  return " IO";
  else                        return " ? ";
  }


QVariant HalPin::data(int column) const {
  hal_pin_t* pin = static_cast<hal_pin_t*>(p);

  switch (column) {
    case 0: return name;
    case 1: return typeName(pin->type);
    case 2: return dirName(pin->dir);
    case 3: return sig ? sig->data(0) : "\t- nc - ";
    case 4: return value();
    }
  return QVariant();
  }


int HalPin::next() const {
  return static_cast<hal_pin_t*>(p)->next_ptr;
  }


int HalPin::owner() const {
  return static_cast<hal_pin_t*>(p)->owner_ptr;
  }


QString HalPin::typeName(int pType) const {
  switch (pType) {
    case 0: return " !0! ";
    case 1: return "bit  ";
    case 2: return "float";
    case 3: return "s32  ";
    case 4: return "u32  ";
    case 5: return "port ";
    }
  return "---  unknown  ---";
  }
