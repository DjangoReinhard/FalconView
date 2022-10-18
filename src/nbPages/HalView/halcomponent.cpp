/* 
 * **************************************************************************
 * 
 *  file:       halcomponent.cpp
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
#include "halcomponent.h"
#include <rtapi.h>
#include <hal.h>
#include <hal_priv.h>


HalComponent::HalComponent(int component, HalElement* parent)
 : HalElement(parent) {
  p = static_cast<hal_comp_t*>((void*)(hal_shmem_base + component));
  if (component) name = static_cast<hal_comp_t*>(p)->name;
  else           name = "Root";
  }


HalComponent::~HalComponent() {
  }


int HalComponent::next() const {
  return static_cast<hal_comp_t*>(p)->next_ptr;
  }
