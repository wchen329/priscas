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
#ifndef __RUNTIME_CALL_H__
#define __RUNTIME_CALL_H__
#include <vector>
#include "diag_cpu.h"
#include "mem.h"
#include "mb.h"
#include "shell.h"

namespace mipsshell
{
	void Enter_Interactive(int arg);
	void breakpoint(std::vector<std::string> & args, Shell& inst);
	void cycle(std::vector<std::string> & args, Shell& inst);
	void cpuopts(std::vector<std::string> & args, Shell& inst);
	void exit(std::vector<std::string> & args, Shell& inst);
	void help(std::vector<std::string> & args, Shell& inst);
	void mem(std::vector<std::string> & args, Shell& inst);
	void pci(std::vector<std::string> & args, Shell& inst);
	void power(std::vector<std::string> & args, Shell& inst);
	void rst(std::vector<std::string> & args, Shell& inst);
	void run(std::vector<std::string> & args, Shell& inst);
	void sound(std::vector<std::string> & args, Shell& inst);
	void state(std::vector<std::string> & args, Shell& inst);
	void time(std::vector<std::string> & args, Shell& inst);
	void trace(std::vector<std::string> & args, Shell& inst);
	void vga(std::vector<std::string> & args, Shell& inst);
}

#endif
