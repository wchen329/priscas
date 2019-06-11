#include "sc_cpu.h"
#include "mmem.h"
#include "mt_exception.h"

namespace mips_tools
{

	bool sc_cpu::cycle()
	{
		format fm;
		
		// Fetch
		BW_32 inst_word = 0;
		BW_32 inst_word_addr = this -> pc.get_data();
		this -> pc.set_data((inst_word_addr + 4) % this->mm.get_size());
		BW_32_T inst_part = BW_32_T(
			this->mem_req_load(inst_word_addr),
			this->mem_req_load(inst_word_addr + 1),
			this->mem_req_load(inst_word_addr + 2),
			this->mem_req_load(inst_word_addr + 3)
		);
		inst_word = inst_part.as_BW_32(); // change

		// Decode

		opcode op; 
		int rs; 
		int rt;
		int rd;
		funct func;
		BW_32 shamt;
		BW_32 imm;
		mips_decoding_unit_32 decoding_unit;
		decoding_unit.decode(	inst_word,
								fm,
								op,
								rs,
								rt,
								rd,
								func,
								shamt,
								imm		);

		bool reg_we = true; // find write enable
		int r_write = 0;

		// Execute
		BW_32 reg_wdata = 0;
		BW_32 branch_addr = imm << 2;

		// find correct format based on opcode
		switch(fm)
		{
			case R:
				
				// Eventually replace these with template functions
				switch(func)
				{
					case ADD:
						reg_wdata = (this->registers[rs] + this->registers[rt]).get_data();
						r_write = rd;
						break;
					case JR:
						this->pc.set_data(this->registers[rs].get_data());
						break;
					case OR:
						reg_wdata = (this->registers[rs] | this->registers[rt]).get_data();
						r_write = rd;
						break;
					case NOR:
						reg_wdata = ~(this->registers[rs] | this->registers[rt]).get_data();
						r_write = rd;
						break;
					case AND: 
						reg_wdata = (this->registers[rs] & this->registers[rt]).get_data();
						r_write = rd;
						break;
					case SLL:
						reg_wdata = this->registers[rs].get_data() << shamt;
						r_write = rd;
						break;
					case SRL:
						reg_wdata = this->registers[rs].get_data() >> shamt;
						reg_wdata = (reg_wdata & ((1 << (32 - shamt)) - 1)); // make it a logical shift
						r_write = rd;
						break;
					case SLT:
						reg_wdata = this->registers[rs].get_data() < this->registers[rt].get_data() ? 1 : 0;
						r_write = rd;
						break;
					case SLTU:
						reg_wdata = this->registers[rs].get_data() < this->registers[rt].get_data() ? 1 : 0;
						r_write = rd;
						break;

					case SUB:
						reg_wdata = (this->registers[rs] - this->registers[rt]).get_data();
						r_write = rd;
						break;
				}

				break;
				
			case I:
				switch(op)
				{
					case ADDI:
						reg_wdata = this->registers[rs].get_data() + imm;
						r_write = rt;
						break;
					case BEQ:
						reg_we = false;
						if(this->registers[rs].get_data() == this->registers[rt].get_data())
						{
							BW_32 curr_pc = this->get_PC();
							this->pc.set_data(curr_pc + branch_addr);
						}

						break;
					case BNE:
						reg_we = false;
						if(this->registers[rs].get_data() != this->registers[rt].get_data())
						{
							BW_32 curr_pc = this->get_PC();
							this->pc.set_data(curr_pc + branch_addr);
						}
						break;
					case ORI:
						reg_wdata = this->registers[rs].get_data() | imm;
						r_write = rt;
						break;
					case ANDI:
						reg_wdata = this->registers[rs].get_data() & imm;
						r_write = rt;
						break;
					case XORI:
						reg_wdata = this->registers[rs].get_data() ^ imm;
						r_write = rt;
						break;
					case LBU:
						{
						char l_word_p_1 = this->mem_req_load(imm + this->registers[rs].get_data());
						char load_write = 0;
						load_write += l_word_p_1;
						reg_wdata = load_write;
						r_write = rt;
						}
						break;
					case LHU:
						{
						char l_word_p_1 = this->mem_req_load(imm + this->registers[rs].get_data());
						char l_word_p_2 = this->mem_req_load(imm + this->registers[rs].get_data() + 1);
						char load_write = 0;
						load_write += l_word_p_1;
						load_write += (l_word_p_2 << 8);
						reg_wdata = load_write;
						r_write = rt;
						}
						break;
					case LW:
						{
						char l_word_p_1 = this->mem_req_load(imm + this->registers[rs].get_data());
						char l_word_p_2 = this->mem_req_load(imm + this->registers[rs].get_data() + 1);
						char l_word_p_3 = this->mem_req_load(imm + this->registers[rs].get_data() + 2);
						char l_word_p_4 = this->mem_req_load(imm + this->registers[rs].get_data() + 3);
						BW_32 load_write = 0;
						load_write += l_word_p_1;
						load_write += (l_word_p_2 << 8);
						load_write += (l_word_p_3 << 16);
						load_write += (l_word_p_4 << 24);
						reg_wdata = load_write;
						r_write = rt;
						}
						break;
					case SB:
						{
						char s_word_p_1 = (this->registers[rt].get_data() & ((1 << 8) - 1));
						this->mem_req_write(s_word_p_1, this->registers[rs].get_data() + imm);
						reg_we = false;
						}
						break;
					case SLTI:
						reg_wdata = this->registers[rs].get_data() < imm ? 1 : 0;
						r_write = rt;
						break;
					case SLTIU:
						reg_wdata = this->registers[rs].get_data() < imm ? 1 : 0;
						r_write = rt;
						break;
					case SH:
						{
						char s_word_p_1 = (this->registers[rt].get_data() & ((1 << 8) - 1));
						char s_word_p_2 = ((this->registers[rt].get_data() & ((1 << 16) - 1)) - s_word_p_1) >> 8;
						this->mem_req_write(s_word_p_1, this->registers[rs].get_data() + imm);
						this->mem_req_write(s_word_p_2, this->registers[rs].get_data() + 1 + imm);
						reg_we = false;
						}
						break;
					case SW:
						{
						char s_word_p_1 = (this->registers[rt].get_data() & ((1 << 8) - 1));
						char s_word_p_2 = ((this->registers[rt].get_data() >> 8) & ((1 << 8) - 1) );
						char s_word_p_3 = ((this->registers[rt].get_data() >> 16) & ((1 << 8) - 1) );
						char s_word_p_4 = ((this->registers[rt].get_data() >> 24) & ((1 << 8) - 1) );
						this->mem_req_write(s_word_p_1, this->registers[rs].get_data() + imm);
						this->mem_req_write(s_word_p_2, this->registers[rs].get_data() + 1 + imm);
						this->mem_req_write(s_word_p_3, this->registers[rs].get_data() + 2 + imm);
						this->mem_req_write(s_word_p_4, this->registers[rs].get_data() + 3 + imm);
						reg_we = false;
						}
						break;
				}
				break;

				case J:
				{
					BW_32 jump_mask = ~((1 << 28) - 1);

					switch(op)
					{
						case JUMP:
							pc.set_data((pc.get_data() & jump_mask) | (imm << 2));
							break;
						case JAL:
							this->registers[31].set_data(pc.get_data() + 4); // Add 4, since it has already been incremented once
							pc.set_data((pc.get_data() & jump_mask) | (imm << 2));
							break;
					}
				}
				break;
		}

		// Write Back
		if(reg_we && r_write != 0)
		{
			this->registers[r_write].set_data(reg_wdata);
		}
		

		return true;
	}

	BW_32 sc_cpu::encode(int rs, int rt, int rd, int funct, int imm_shamt_jaddr, opcode op)
	{
		return generic_mips32_encode(rs, rt, rd, funct, imm_shamt_jaddr, op);
	}

	void sc_cpu::rst()
	{
		for(int i = 0; i < 32; i++)
		{
			this->registers[i].set_data(0);
		}

		this->pc.set_data(0);
	}

	void sc_cpu::mem_req_write(char data, int index)
	{
		this->mm[index % this->mm.get_size()] = data;
	}

	char sc_cpu::mem_req_load(int index)
	{
		return this->mm[index % this->mm.get_size()];
	}

	void sc_cpu::ghost_cycle()
	{
		this->pc.set_data(this->pc.get_data() + 4);
	}
}