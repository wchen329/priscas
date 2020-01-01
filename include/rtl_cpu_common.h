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
#ifndef __RTL_CPU_COMMON_H__
#define __RTL_CPU_COMMON_H__
#include "phdl.h"

/* Provides some very basic RTLBranch facilities
 *
 */
namespace priscas
{
	/* Basic Single Cycle CPU
	 * RTL "template"
	 *
	 * Since a single cycle CPU is more or less, a single stage pipeline
	 * many can mostly be described in a single RTL branch.
	 *
	 * This specific branch encapsulates a whole Fetch->Decode->Execute sort of sequence
	 * in a single go
	 *
	 * The individual specifics, vary between implementations. fetch(), decode(), and execute() must be reimplemented by derivatives
	 */
	class RTLB_basic_sc : public RTLBranch
	{
		public:
			virtual void cycle();
		protected:
			virtual void fetch() = 0;
			virtual void decode() = 0;
			virtual void execute() = 0;

			/* Constructor.
			 * Merely wraps around RTLBranch's constructor
			 */
			RTLB_basic_sc(int thresh) : RTLBranch(thresh) {}
	};
}

#endif