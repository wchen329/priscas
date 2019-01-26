#define _CRT_SECURE_NO_WARNINGS	// for MSVC
#include <cstdio>
#include <cstdlib>

/* Shell for MIPS Tools
 *
 * The shell has two modes: Interative Mode and Batch Mode
 *
 * Passing in a file as an argument allows for that instruction to be batched.
 *
 * wchen329
 */
int main(int argc, char ** argv)
{
	FILE * inst_file;

	// First get the active file in which to get instructions from
	if(argc >= 2)
	{
		inst_file = fopen(argv[1], "r");
	}

	else
	{
		inst_file = stdin;
		fprintf(stdout, "MIPS Tools 1.0\n");
		fprintf(stdout, "Starting in interactive mode...\n");
		fprintf(stdout, "-----------------------------------\n");
		fprintf(stdout, "- System calls used with $ prefix -\n");
		fprintf(stdout, "- Otherwise interpreted as instr. -\n");
		fprintf(stdout, "-----------------------------------\n");
	}

	while(true)
	{
		char buf[100];
		fprintf(stdout, ">> ");
		fgets(buf, 100, inst_file);
	}

	fclose(inst_file);
	return 0;
}