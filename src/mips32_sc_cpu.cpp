//////////////////////////////////////////////////////////////////////////////
//
//    PRISCAS - Computer architecture simulator
//    Copyright (C) 2019 Winor Chen
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License along
//    with this program; if not, write to the Free Software Foundation, Inc.,
//    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
//////////////////////////////////////////////////////////////////////////////
#include "mips32_sc_cpu.h"

namespace priscas
{

	bool mips32_sc_cpu::cycle()
	{
		++this->comcount;
		return true;
	}

	void mips32_sc_cpu::rst()
	{
/*		for(int i = 0; i < 32; i++)
		{
			this->RegisterFile
		}
		*/
		this->pc.force_current_state(0);
	}

	void mips32_sc_cpu::mem_req_write(byte_8b data, int index)
	{
		this->mm[index % this->mm.get_size()] = data;
	}

	byte_8b mips32_sc_cpu::mem_req_load(int index)
	{
		return this->mm[index % this->mm.get_size()];
	}
}