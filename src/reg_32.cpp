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
//   You should have received a copy of the GNU General Public License along
//    with this program; if not, write to the Free Software Foundation, Inc.,
//    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
//////////////////////////////////////////////////////////////////////////////
#include "reg_32.h"
namespace mips_tools
{
	reg_32 operator|(reg_32 r_1, reg_32 r_2)
	{
		reg_32 r_3;
		r_3.set_data(r_1.get_data().AsInt32() | r_2.get_data().AsInt32());
		return r_3;
	}
	reg_32 operator&(reg_32 r_1, reg_32 r_2)
	{
		reg_32 r_3;
		r_3.set_data(r_1.get_data().AsInt32() & r_2.get_data().AsInt32());
		return r_3;
	}

	reg_32 operator^(reg_32 r_1, reg_32 r_2)
	{
		reg_32 r_3;
		r_3.set_data(r_1.get_data().AsInt32() ^ r_2.get_data().AsInt32());
		return r_3;
	}
}
