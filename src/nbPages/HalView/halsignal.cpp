/* 
 * **************************************************************************
 * 
 *  file:       halsignal.cpp
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
#include "halsignal.h"
#include <rtapi.h>
#include <hal.h>
#include <hal_priv.h>
#include <QVariant>


HalSignal::HalSignal(int signal, HalElement* parent)
 : HalElement(parent) {
  if (signal) {
     p = static_cast<hal_sig_t*>((void*)(hal_shmem_base + signal));
     name = static_cast<hal_sig_t*>(p)->name;
     }
  }


HalSignal::~HalSignal() {
  }


QVariant HalSignal::data(int column) const {
  if (!column) return name;
  hal_sig_t* pSig = static_cast<hal_sig_t*>(p);
  hal_data_u* pData = (hal_data_u *) SHMPTR(pSig->data_ptr);

  return (double) pData->f;
  }


int HalSignal::next() const {
  return static_cast<hal_sig_t*>(p)->next_ptr;
  }
