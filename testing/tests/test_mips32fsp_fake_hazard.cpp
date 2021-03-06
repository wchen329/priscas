#include <string>
#include <vector>
#include <cstdio>
#include "basic_assert.h"
#include "sc_cpu.h"
#include "mb.h"
#include "shell.h"

void test_mips32fsp_fake_hazard()
{
	using namespace priscas;
	std::string prog_name = "mtshell";
	std::string flag_i = "-i";
	std::string file_name = "asm/fake_hazard.s";
	std::string option_c = "-c";
	std::string cpu_select = "1";
	std::vector<std::string> args;
	args.push_back(prog_name);
	args.push_back(flag_i);
	args.push_back(file_name);
	args.push_back(option_c);
	args.push_back(cpu_select);
	priscas::Shell test_shell;
	test_shell.SetArgs(args);
	test_shell.SetQuiet();
	test_shell.Run();
	mb & test_m = test_shell.GetMotherboard();
	cpu & c = test_m.get_cpu();
	diag_cpu & fsp_cpu = dynamic_cast<diag_cpu&>(c);
	assertEquals(fsp_cpu.get_reg_data($s0).AsInt32(), 100);
	assertEquals(fsp_cpu.get_reg_data($s1).AsInt32(), 50);
	assertEquals(fsp_cpu.get_reg_data($s2).AsInt32(), 100)
	assertEquals(test_shell.GetMotherboard().get_cycles(), 21);
}