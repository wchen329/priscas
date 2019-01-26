/* Interface for the single cycle CPU implementation
 */

#ifndef __SC_CPU_H__
#define __SC_CPU_H__
#include "cpu.h"
#include "reg_32.h"
#include "primitives.h"

namespace mips_tools
{

	class sc_cpu : cpu
	{
		public:
			void rst(); // async reset
			bool cycle();
			BW_32 get_reg_data(int index) {return this->registers[index].get_data();}

		private:
			static const int REG_COUNT = 32;
			reg_32 registers[REG_COUNT];
			reg_32 pc;
	};
}
#endif