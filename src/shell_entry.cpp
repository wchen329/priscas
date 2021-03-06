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
#include <csignal>
#include <string>
#include <vector>
#include "priscas_core.h"

void break_machine(int arg);

priscas::Shell runtime; // Simulator Runtime

/* Main routine for running
 * the pRISCas Shell directly.
 */
int main(int argc, char ** argv)
{
	using namespace priscas;

	Arg_Vec args; // Arguments to Simulator Runtime

	// Simple pass each argument as an argument to the shell.
	for(int carg = 0; carg < argc; carg++)
	{
		args.push_back(UPString(argv[carg]));
	}

	// Set arguments to the ones just built from the passed in argv
	runtime.SetArgs(args);

	// Allow for breaking out of .run (bugged TODO: fix)
	signal(SIGINT, break_machine);

	// Start the simulation
	runtime.Run();

	return 0;
}

/* break_machine
 * Changes the shell back to SIGINT when the signal is received.
 */
void break_machine(int arg)
{
	runtime.modeset_Interactive();
	signal(SIGINT, break_machine); // This has a strange bug in Windows. TODO: fix
}
