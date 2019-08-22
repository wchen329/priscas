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
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <string>
#include <memory>
#include "branding.h"
#include "cpu.h"
#include "diag_cpu.h"
#include "mb.h"
#include "mt_exception.h"
#include "mtsstream.h"
#include "osi.h"
#include "interpret.h"
#include "runtime_call.h"
#include "shell.h"
#include "states.h"

namespace priscas
{
	/* A mapping from a string into a directive function pointer (must be a member of Shell)
	 */
	typedef std::pair<std::string, void(*)(std::vector<std::string> &, Shell&)> directive_pair;

	/* Shell for MIPS Tools
	 *
	 * The shell has two modes: Interative Mode and Batch Mode
	 *
	 * Passing in a file as an argument allows for that instruction to be batched.
	 *
	 * wchen329
	 */
	void Shell::Run()
	{
		size_t argc = args.size();
		priscas::cpu_t cp = priscas::STANDARD;
		int mem_width = 16;

		std::string app_brand = branding::APPLICATION_NAME + " " + branding::APPLICATION_VERSION + " " + branding::APPLICATION_DBG;

		if(!isQuiet)
		{
			std::string header = 
			app_brand + priscas_io::newLine +
			branding::APPLICATION_DESC + priscas_io::newLine;
			
			WriteToOutput(header);
		}

		priscas::HighLevelType t = priscas::getTypeGeneric<long>();

		// First get the active file in which to get instructions from
		if(argc >= 2)
		{
			for(size_t i = 1; i < argc; i++)
			{
				if(args[i] == "-h")
				{
					WriteToOutput(("Usage options:\n"));
					WriteToOutput(("-h (show this message)\n"));
					WriteToOutput(("-i [file] (execute a text file with by assembling and running the program)\n"));
					WriteToOutput(("-m [width] (specify a memory bit width; the total memory available will be 2^[width]\n"));
					//WriteToOutput(( "-a (active assembler mode, requires the -i option):\n"));
					WriteToOutput(("-c (select a CPU type 0: for single cycle (default) or 1: for Five Stage Pipeline)\n"));
					return;
				}

				/*if(args[i] == "-a")
				{
					if(!isQuiet) WriteToOutput(("Assembler mode ENABLED.\n"));
					priscas::ASM_MODE = true;
					priscas::INTERACTIVE = false;
				}*/

				if(args[i] == "-i")
				{
					priscas::INTERACTIVE = false;
					priscas::HAS_INPUT = true;
					if((i+1) < argc)
					{
						inst_file = fopen(args[i+1].c_str(), "r");
						priscas::INPUT_SPECIFIED = true;
					}
				}

				if(args[i] == "-WIN32_SHELL")
				{
					priscas::INTERACTIVE = false;
					priscas::HAS_INPUT = true;
					inst_file = stdin;
					priscas::INPUT_SPECIFIED = true;
					priscas::WIN_32_GUI = true;
				}

				if(args[i] == "-m")
				{
					if((i+1) < argc) mem_width = atoi(args[i+1].c_str());
				}

				if(args[i] == "-c")
				{
					if((i+1) < argc) cp = static_cast<priscas::cpu_t>(atoi(args[i+1].c_str()));
				}
			}
		}

		if(priscas::HAS_INPUT)
		{
			if(!priscas::WIN_32_GUI)
			{
				if(!isQuiet) WriteToOutput(("Starting in machine mode...\n"));
				priscas::INTERACTIVE = false;
			}

			if(!priscas::INPUT_SPECIFIED)
			{
				WriteToError(("Error: An input file is required (specified through -i [input file] ) in order to run in batch mode.\n"));
				::exit(1);
			}

			if(inst_file == NULL)
			{
				WriteToError(("Error: The file specified cannot be opened or doesn't exist.\n"));
				::exit(1);
			}
		}

		else
		{
			priscas::INTERACTIVE = true;
			inst_file = stdin;
			if(!isQuiet) WriteToOutput(("Starting in interactive mode...\n"));
			if(!isQuiet) WriteToOutput(("Tip: system directives are preceded by a . (for example .help)\n"));
		}

		if(mem_width <= 0)
		{
			WriteToError(("Error: An error occurred when trying to read memory width (must be larger than 0 and a natural number)."));
			::exit(1);
		}

		if(mem_width > 32)
		{
			
			WriteToError(("Error: Memory size specified is too large (must be less than or equal to 20 bits wide)"));
			::exit(1);
		}

		if(!isQuiet) WriteToOutput(("CPU Type: "));
		switch(cp)
		{
			case priscas::STANDARD:
				if(!isQuiet) WriteToOutput(("Single Cycle\n"));
				break;
			case priscas::FIVE_P:
				if(!isQuiet) WriteToOutput(("Five Stage Pipeline\n"));
				break;
			default:
				if(!isQuiet) WriteToOutput(("Invalid CPU type detected. Exiting...\n"));
				::exit(1);
		}

		this->motherboard = new priscas::mb(cp, mem_width, priscas::SUSPEND);
		motherboard->reset();
		priscas::mb * MB_IN_PTR = motherboard;

		if(!isQuiet)
		{
			std::string msg = 
			(std::string( "Main Memory size: " + priscas_io::StrTypes::SizeToStr(motherboard->get_mmem_size()) + " bytes\n"));
			WriteToOutput(msg);
		}

		/* Actual Execution Portion
		 */


		/* First, if an input file was specified
		 * (1) collect file symbols
		 * (2) map it to memory assemble that file first
		 */
		if(INPUT_SPECIFIED)
		{
			std::vector<std::string> lines;

			uint32_t equiv_pc = 0;
			char input_f_stream[255];
			memset(input_f_stream, 0, sizeof(input_f_stream));
			unsigned long line_number = 0;
			try
			{
				while(fgets(input_f_stream, 254, inst_file) != NULL)
				{
					line_number++;
					std::string current_line = std::string(input_f_stream);
					std::vector<std::string> parts = chop_string(current_line);
	
					// Remove strings that are just whitespace
					if(parts.empty())
						continue;

					// Symbol assignment: add the symbol to symbol table
					
					if(parts[0][parts[0].size() - 1] == ':')
					{
						this->jump_syms.insert(parts[0].substr(0, parts[0].size() - 1), equiv_pc);
						continue;
					}

					if(parts[0][0] == '.')
					{
						this->directive_syms.insert(current_line, equiv_pc);
						continue;
					}

					this->line_number_to_PC.insert(std::pair<unsigned long, unsigned long>(line_number, equiv_pc));
					this->PC_to_line_number.insert(std::pair<unsigned long, unsigned long>(equiv_pc, line_number));
					this->PC_to_line_string.insert((std::pair<unsigned long, std::string>(equiv_pc, current_line)));
					equiv_pc = equiv_pc + 4;
					lines.push_back(current_line);		
				}
			}
			catch(priscas::mt_exception& e)
			{
				WriteToOutput("An error has occurred when writing debugging symbols and assigning directives:\n\t");
				WriteToOutput(e.get_err().c_str());
				return;
			}

			// Add pre-declared program breakpoints, if any
			while(!this->queued_prog_breakpoints.empty())
			{
				this->add_program_breakpoint(this->queued_prog_breakpoints.front());
				this->queued_prog_breakpoints.pop();
			}

			priscas::BW_32 asm_pc = 0;

			// Now assemble the rest
			for(size_t itr = 0; itr < lines.size(); itr++)
			{
				std::vector<std::string> asm_args = chop_string(lines[itr]);
				priscas::diag_cpu & dcpu = dynamic_cast<priscas::diag_cpu&>(motherboard->get_cpu());
				priscas::ISA& dcpuisa = dcpu.get_ISA();
				std::shared_ptr<priscas::BW> inst;
				try
				{
					inst = dcpuisa.assemble(asm_args, asm_pc, jump_syms);
				}

				catch(priscas::mt_exception& e)
				{
					WriteToError(("An error occurred while assembling the program.\n"));
					std::string msg_1 = 
						(std::string("Error information: ") + std::string(e.get_err()));
					WriteToError(msg_1);
					WriteToError(("Line of error:\n"));
					std::string msg_2 = 
						(std::string("\t") + lines[itr] + std::string("\n"));
					WriteToError(msg_2);
					return;
				}

				priscas::BW_32& thirty_two = dynamic_cast<priscas::BW_32&>(*inst);
				motherboard->DMA_write(thirty_two.b_0(), asm_pc.AsUInt32());
				motherboard->DMA_write(thirty_two.b_1(), asm_pc.AsUInt32() + 1);
				motherboard->DMA_write(thirty_two.b_2(), asm_pc.AsUInt32() + 2);
				motherboard->DMA_write(thirty_two.b_3(), asm_pc.AsUInt32() + 3);
				asm_pc.AsUInt32() += 4;
			}
			
			this->state = SLEEPING;
		}

		inst_file = stdin;

		while(this->state != KILLED)
		{

		/* Second, execute.
		 * To execute:
		 * - If the PC can be debugged, then just run it. Ignore "debugging" symbols.
		 * - If the PC can be debugged, then for every PC, execute the runtime directive associated with the PC BEFORE the instruction is fetched
		 *   then run the CPU a cycle, and repeat.
		 * If no input file was specified, then it starts in interactive / debugging mode
		 *
		 */

		if(priscas::INTERACTIVE)
		{
			WriteToOutput((">> "));
		}

		if(priscas::INTERACTIVE || priscas::ASM_MODE)
		{
			priscas::diag_cpu & dcpu = dynamic_cast<priscas::diag_cpu&>(motherboard->get_cpu());
			std::string& val = this->ReadFromInput();
			
			if(val.size() == 0)
			{
				continue;
			}

			if(val[0] == '.')
			{
				try
				{
					std::vector<std::string> chopped = chop_string(val);
					execute_runtime_directive(chopped);
				}
				catch(priscas::mt_exception & e)
				{
					WriteToError(e.get_err());
				}

				continue;
			}

			std::vector<std::string> asm_args = chop_string(val);
			priscas::ISA & dcpuisa = dcpu.get_ISA();
			priscas::BW_32 asm_pc = dcpu.get_PC();
			std::shared_ptr<priscas::BW> inst;
			
			try
			{
				inst = dcpuisa.assemble(asm_args, asm_pc, jump_syms);
			}

			catch(priscas::mt_exception& e)
			{
				WriteToError(("An error occurred while assembling the inputted instruction.\n"));
				std::string msg = (std::string("Error information: ") + std::string(e.get_err()));
				WriteToError(msg);
				WriteToError(priscas_io::newLine.c_str());

				continue;
			}

			priscas::BW_32& thirty_two = dynamic_cast<priscas::BW_32&>(*inst);
			motherboard->DMA_write(thirty_two.b_0(), asm_pc.AsUInt32());
			motherboard->DMA_write(thirty_two.b_1(), asm_pc.AsUInt32() + 1);
			motherboard->DMA_write(thirty_two.b_2(), asm_pc.AsUInt32() + 2);
			motherboard->DMA_write(thirty_two.b_3(), asm_pc.AsUInt32() + 3);
			motherboard->step();
		}

		if(!priscas::INTERACTIVE && !priscas::ASM_MODE)
		{

			signal(SIGINT, priscas::Enter_Interactive);
			while(this->state != KILLED && !priscas::SUSPEND)
			{
				priscas::diag_cpu & dcpu = dynamic_cast<priscas::diag_cpu&>(motherboard->get_cpu());
				priscas::BW_32 dpc = dcpu.get_PC();
				
				if(this->directive_syms.has(dpc.AsUInt32()))
				{
					std::vector<std::string> cmds = this->directive_syms.lookup_from_PC(dpc.AsUInt32());
					
					for(size_t cmdcount = 0; cmdcount < cmds.size(); cmdcount++)
					{
						std::vector<std::string> chopped = chop_string(cmds[cmdcount]);
						execute_runtime_directive(chopped);
					}
				}

				motherboard->step();

				if(this->has_prog_break_at(dcpu.get_PC().AsUInt32()))
				{
					priscas::SUSPEND = true;
					priscas::INTERACTIVE = true;
					unsigned long line_number = this->PC_to_line_number.at(dcpu.get_PC().AsUInt32());
					std::string line_str = this->PC_to_line_string.at(dcpu.get_PC().AsUInt32());

					std::string o = (std::string("Breakpoint at line ") + priscas_io::StrTypes::UInt32ToStr(line_number) + std::string(" hit.\n"));
					WriteToOutput(o);
					std::string p = (std::string("line ") + priscas_io::StrTypes::UInt32ToStr(line_number) + std::string(":\n\t") + line_str + std::string("\n"));
					WriteToOutput(p);
				}

				if(this->has_ma_break_at(motherboard->get_cycles()))
				{
					priscas::SUSPEND = true;
					priscas::INTERACTIVE = true;
					std::string o = (std::string("Breakpoint at cycle " + priscas_io::StrTypes::UInt32ToStr(motherboard->get_cycles()) + " hit.\n"));
					WriteToOutput(o);
				}
			}
		}
	}
		if(!this->isQuiet)
			WriteToOutput(("Simulation terminating...\n"));
		delete priscas::mtsstream::asmout;
}

	/* Takes an input string and breaks that string into a vector of several
	 * based off of whitespace and tab delineators
	 * Also removes comments
	 * "Also acknowledges " " and ' ' and \ all used for escaping
	 */
	std::vector<std::string> chop_string(std::string & input)
	{
		std::string commentless_input;
		size_t real_end = input.size();
		for(size_t cind = 0; cind < input.size(); cind++)
		{
			if(input[cind] == '#')
			{
				real_end = cind;
				break;
			}
		}

		commentless_input = input.substr(0, real_end);

		std::vector<std::string> str_vec;
		
		std::string built_string = "";

		bool has_escaped = false;
		bool in_quotes = false;

		// Use a linear search
		for(size_t ind = 0; ind < commentless_input.size(); ind++)
		{
			// If no escaping, then perform syntactical checks
			if(!has_escaped)
			{
				// First acknowledge escaping
				if(commentless_input[ind] == '\\')
				{
					has_escaped = true;
					continue;
				}

				// Detect quotations
				if(commentless_input[ind] == '\"' || commentless_input[ind] == '\'')
				{
					in_quotes = !in_quotes;
					continue;
				}

				// Now if not quoted as well, then a comma, whitespace, tab, or newline delineates that argument is done parsing
				if(!in_quotes)
				{
					if(commentless_input[ind] == ',' ||  commentless_input[ind] == ' ' || commentless_input[ind] == '\t' || commentless_input[ind] == '\n' || commentless_input[ind] == '\r')
					{
						// Check: do not add empty strings
						if(built_string != "")
						{
							str_vec.push_back(built_string);
							built_string = "";
						}

						continue;
					}
				}
			}

			built_string += commentless_input[ind];
			has_escaped = false; // no matter what, escaping only escapes one...
		}

		if(has_escaped || in_quotes)
		{
			throw priscas::mt_bad_escape();
		}

		if(built_string != "")
			str_vec.push_back(built_string);

		return str_vec;
	}

	// Set up list of runtime directives
	Shell::Shell() : motherboard(nullptr), isQuiet(false), inst_file(nullptr), tw_error(&priscas_io::null_tstream),
		tw_output(&priscas_io::null_tstream), tw_input(&priscas_io::null_tstream), NoConsoleOutput(false)
	{
		this->state = EMBRYO;

		// Set up jump table for runtime directives
		this->directives.insert(directive_pair(".breakpoint", priscas::breakpoint));
		this->directives.insert(directive_pair(".cycle", priscas::cycle));
		this->directives.insert(directive_pair(".exit", priscas::exit));
		this->directives.insert(directive_pair(".help", priscas::help));
		this->directives.insert(directive_pair(".mem", priscas::mem));
		this->directives.insert(directive_pair(".pci", priscas::pci));
		this->directives.insert(directive_pair(".cpuopts", priscas::cpuopts));
		this->directives.insert(directive_pair(".power", priscas::power));
		this->directives.insert(directive_pair(".rst", priscas::rst));
		this->directives.insert(directive_pair(".run", priscas::run));
		this->directives.insert(directive_pair(".sound", priscas::sound));
		this->directives.insert(directive_pair(".state", priscas::state));
		this->directives.insert(directive_pair(".trace", priscas::trace));
		this->directives.insert(directive_pair(".time", priscas::time));
		this->directives.insert(directive_pair(".vga", priscas::vga));
	}

	void Shell::declare_program_breakpoint(unsigned long line)
	{
		this->queued_prog_breakpoints.push(line);
	}

	void Shell::add_program_breakpoint(unsigned long line)
	{
		if(this->line_number_to_PC.count(line) > 0)
		{
			unsigned long line_pc = this->line_number_to_PC.at(line);
			this->program_breakpoints.insert(std::pair<unsigned long, unsigned long>(line_pc, line));
			std::string o = (std::string("Breakpoint set at line ") + priscas_io::StrTypes::UInt32ToStr(line) + std::string("d\n"));
			WriteToOutput(o);
		}

		else
		{
			WriteToError(("Invalid line number. The line number may not be associated with an instruction or may not be in the file.\n"));
		}
	}

	void Shell::WriteToError(std::string& e)
	{
		if(!NoConsoleOutput)
		{
			fprintf(stderr, e.c_str());
		}

		*tw_error << e;
	}

	void Shell::WriteToError(const char* e)
	{
		if(!NoConsoleOutput)
		{
			fprintf(stderr, e);
		}

		std::string err = std::string(e);

		*tw_error << err;

	}

	void Shell::WriteToOutput(std::string& o)
	{
		if(!NoConsoleOutput)
		{
			fprintf(stdout, o.c_str());
		}

		*tw_output << o;
	}

	void Shell::WriteToOutput(const char* o)
	{
		if(!NoConsoleOutput)
		{
			fprintf(stdout, o);
		}

		std::string out = std::string(o);
		*tw_output << out;
	}

	std::string& Shell::ReadFromInput()
	{
		this->rd_buffer.clear();

		bool QUOTES = false;
		bool ESCAPED = false;

		if(!NoConsoleOutput)
		{
			char in;
			while((in = fgetc(stdin)) != EOF)
			{
				if(in == '\\' && !QUOTES && !ESCAPED)
				{
					ESCAPED = true;
					continue;
				}

				if(in == '\"')
				{
					QUOTES = (!QUOTES);
				}

				if((in == '\n' || in == '\r' ) && !ESCAPED && !QUOTES)
				{
					this->rd_buffer += in;
					break;
				}

				this->rd_buffer += in;
				ESCAPED = false;
			}
		}


		do
		{
			*tw_input >> rd_buffer;
			osi::sleep(10);
		} while(rd_buffer == "" && priscas::INTERACTIVE);

		return this->rd_buffer;
	}

	std::vector<priscas::NameValueStringPair> scan_for_values(std::vector<std::string>& input)
	{
		std::vector<priscas::NameValueStringPair> vals;

		for(size_t sind = 0; sind < input.size(); sind++)
		{
			std::string& indc = input[sind];
			size_t substr_where = indc.find_first_of('=');

			// Case: not found, then just use the whole string as the name, with an empty value
			if(substr_where == -1)
			{
				std::string first = input[sind];
				std::string second = "";
				priscas::NameValueStringPair nv(first, second);
				vals.push_back(nv);
			}

			// Case: empty name. This is an error
			else if(substr_where == 0)
			{
				throw priscas::mt_invalid_cpu_opt("Option specifier (lvalue of = may not be blank) requires name");
			}

			// Case: there is at least one equal sign
			else
			{
				// Use the first equal sign
				size_t last_where = indc.find_last_of('=');

				std::string first = indc.substr(0, substr_where);
				std::string second = indc.substr(substr_where + 1, indc.size());
				priscas::NameValueStringPair nv(first, second);
				vals.push_back(nv);
			}
		}

		return vals;
	}
}
