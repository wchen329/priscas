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
#ifndef __PHDL_H__
#define __PHDL_H__

/* "Pseudo HDL"
 * This refers to the parallelizable backend portion of the
 * simulator which attempts to mirror the operation of real hardware
 * similar to a Hardware Description Language (HDL).
 * Note that: HiZ and unknown (x) values are not emulated
 *
 * Ultimately, this is supposed to be a parallel graph traversal
 * The graph "we'll call this "RTL" graph is simple a Directed Acyclic Graph
 * with entry points being sequential blocks
 * intermediate nodes being the buses, connections, and combinational blocks in-between,
 * and sequential blocks (or just the an unconnected bus the stop nodes)
 */
#include <algorithm>
#include <queue>
#include "primitives.h"
#include "priscas_global.h"
#include "priscas_osi.h"

namespace priscas
{
	// Forward declaration
	class Node;
	typedef std::shared_ptr<Node> mNode;
	class Drivable;
	typedef Drivable* pDrivable;
	 
	/* Drivable
	 * Elements which derive this within may be driven by a bus connection (or Node).
	 */
	class LINK_DE Drivable
	{
		public:

			/* drive(..)
			 * Drive this drivable with a voltage signal (in the form of bits)
			 *
			 * The driver is the point to the Drivable that which is driving the bus.
			 * In  most cases, it will simply be the caller.
			 */
			virtual void drive(const BW& input) = 0;
	};

	typedef std::shared_ptr<Drivable> mDrivable;

	/* Execution_Synchronized
	 *
	 * Execution synchronized objects 
	 * are those which have explicit execution parents
	 * and must wait for their completion before executing themselves
	 *
	 * This only means "execution synchronized"- this doesn't handle anything specific outside of the pHDL execution engine
	 * necessarily
	 */
	class Execution_Synchronized
	{
		public:

			/* bool ready()
			 * Return if this object is ready to execute/cycle
			 * False if not
			 *
			 * It is ready if the ready count is equal to
			 *
			 */
			bool ready() { return tthresh == tcount; }

			/* execute()
			 * Execute the enclosed block.
			 */
			virtual void execute() = 0;

			/* steal()
			 * Take over execution of this object.
			 * (i.e. climb down the graph chain)
			 */
			void steal() { lock.lock(); tcount = 0; execute(); lock.unlock(); }

			/* declare_parent_ready()
			 * Raise the ready count by one
			 */
			void declare_parent_ready() { lock.lock(); ++tcount; lock.unlock();}

			/* Constructor.
			 * Takes in a single threshhold.
			 */
			Execution_Synchronized(int tthresh) : tthresh(tthresh) {}

		private:
			int tthresh;
			int tcount;
			priscas_osi::mlock lock;
			Execution_Synchronized();

	};

	/* RTLBranch
	 * A RTL branch is supposed to represent dataflow (RTL-ish level) throughout the processor. It is also intended to handle behavioral constructions.
	 * Mainly, it's supposed to be combinational blocks which set the states of sequential logics.
	 * RTL branches are only to be tied to the base clock (which incidentally is also the fastest)
	 *
	 * RTL branches will not execute (cycle) until all parent buses are done being driven.
	 * The 
	 */
	class RTLBranch : public Execution_Synchronized
	{
			public:
				/* cycle()
				 * IMPLEMENTATION: perform operations during which would otherwise happen during a cycle.
				 */
				virtual void cycle() = 0;

				/* execute()
				 * Wrap around cycle().
				 */
				void execute() { cycle(); }

				/* Constructor.
				 * Merely wraps around Execution_Synchronized's constructor
				 */
				RTLBranch(int thresh) : Execution_Synchronized(thresh) {}

	};

	typedef std::shared_ptr<RTLBranch> mRTLBranch;

	/* SequentialBlock
	 * Represents block of sequential logic
	 * that holds state in it
	 *
	 * A sequential block is aimed to have a single clock signal.
	 * If multiple signals are needed, break them into separate blocks.
	 */
	class SequentialBlock
	{

		public:
			/* prologue()
			 * IMPLEMENTATION: perform operations during which would otherwise happen during a cycle.
			 */
			virtual void prologue() = 0;

			/* epilogue()
			 * IMPLEMENTATION: perform operations which occur between cycles (i.e. assign queue STATE CHANGES)
			 */
			virtual void epilogue() = 0;
	};

	typedef std::shared_ptr<SequentialBlock> mSequentialBlock;

	/* Clock
	 * A clock signal which is used to power Sequential Blocks
	 */
	class Clock
	{
		public:

			/* base_cycle()
			 * Advance time one base clock cycle for this clock.
			 */
			void base_cycle();

			/* cycle()
			 * Cycle all connected sequential blocks.
			 * Unless there is a good reason to, use base_cycle instead (which works off of the base clock)
			 */
			virtual void cycle();

			/* connect(...)
			 * Connect a sequential logic block. This will be
			 * controlled by the clock accordingly and will be cycled when "cycle" is called
			 */
			void connect(mSequentialBlock logic)  { this->logics.push_back(logic); }

			/* set_Interval(...)
			 * Sets how many "base clock cycles" to wait before actually "cycling"
			 * It can be also trivially seen that the base clock has an interval of 0.
			 * For example, Clock with interval of 1 will actually activate every 2 base clock cycles.
			 */
			virtual void setInterval(int64_t interval) { this->interval = interval; }
			
			/* set_Offset(...)
			 * Sets clock skew.
			 * The offset is the "head start" of the clock (or how much it is delayed when first inserted).
			 * - A negative offset means that the clock is delayed by the absolute value of that base clock cycles
			 * - A postive offset means that the clock is ahead of the base clock by the offset in base clock cycles. However, the reset signal is assumed to be asserted
			 *   at the beginning, so any state changes which occur before the first cycle of the base clock will not take effect
			 */
			virtual void setOffset(int64_t cyclesleft) { this->cyclesleft = cyclesleft; }

			/* Constructor.
			 * Defaults to a clock matching the base clock.
			 */
			Clock() :
				interval(0),
				cyclesleft(0)
			{}

			/* Constructor.
			 * Takes an interval and offset directly. 
			 */
			Clock(int64_t interval, int64_t offset) :
				interval(interval),
				cyclesleft(offset)
			{}

		private:
			typedef std::vector<mSequentialBlock> SeqmBlkV;
			SeqmBlkV logics;
			int64_t interval;
			int64_t cyclesleft;
	};

	typedef std::vector<Clock> Clock_Vec;

	/* Register_Generic
	 * A generic n bit register
	 * (this will supersede the Reg_32)
	 */
	template<class RegCC> class Register_Generic : protected SequentialBlock, public Drivable
	{
		public:
		
			/* RegCC get_current_state()
			 * Return the current state
			 * (atomic)
			 */
			RegCC& get_current_state() { return current_state; }
			const RegCC& get_current_state() const { return current_state; }

			/* force_current_state(...)
			 * Atomically set the current state.
			 * Unless this is really intended, use set_next_state(...) instead
			 * So it is updated with the clock accordingly
			 * (atomic)
			 */
			void force_current_state(RegCC data_in) { this->current_state = data_in; }

			/* set_next_state(...)
			 * Set the next state.
			 * The next state becomes the current state on the next clock edge.
			 * (NOT atomic)
			 */
			void set_next_state(RegCC data_in) { this->next_state = data_in; dirty = true; }

			/* operator<=
			 * Short hand for set_next_state(...).
			 */
			void operator<=(RegCC data_in) { set_next_state(data_in); }

			/* void drive()
			 * Implicit bus access, which allows this bus to be driven.
			 */
			void drive(const BW& next_state)
			{
				(*this) <= next_state;
			}

			/* RegCC operator*
			 * Short hand for get_current_state()
			 */
			RegCC operator*() { return get_current_state(); }

			/* prologue()
			 * Start the execution chain.
			 */
			void prologue()
			{
				// Prologue and Content
				if(output_connection.get() != nullptr)
				{
					this->output_connection->drive(this->current_state);
				}
			}

			/* epilogue()
			 * Commit state changes queued during the cycle.
			 */
			void epilogue()
			{
				// Epilogue: if "dirty" then update.
				// If not, don't do anything
				// having this allows for implicit feedback setting the state

				if(this->dirty)
					this->current_state = this->next_state;

				dirty = false;
			}

			/* input_bind()
			 * Connect the input of the register to something.
			 * NOTE: Do not connect more than one input, or use <= to a register when that register is fed through a wire
			 * This is obviously like contention, and what can happen is undefined.
			 */
			void input_bind(mDrivable inp) { this->input_connection = inp; }

			/* output_connect()
			 * Connect the output of the register to something
			 * NOTE: This can only be bound to one "drivable". If more outputs are needed, use a Node.
			 */
			void output_bind(mDrivable outp) { this->output_connection = inp; }

			Register_Generic() : dirty(false) {}

		private:

			// Register's State
			RegCC current_state;

			// Register State on Next Update
			RegCC next_state;

			// Input Connection
			mDrivable input_connection;

			// Output Connection
			mDrivable output_connection;

			// Dirty. Does this register have a queued update?
			bool dirty;
	};

	typedef Register_Generic<BW_32> Register_32;
	typedef Register_Generic<BW_16> Register_16;



	class Bus : public Drivable
	{
		public:
			/* drive(...)
			 * Drive the bus with some data.
			 * (atomic)
			 */
			virtual void drive(const BW& input) = 0;

			/* read(...)
			 * Read data off the bus
			 * (atomic)
			 */
			virtual const BW& read() = 0;
	};

	/* Bus_Generic
	 * A generic n bit bus.
	 */
	template<class ContainerT> class Bus_Generic : public Bus
	{
		public:
			/* drive(...)
			 * Drive the bus with some data.
			 * (atomic)
			 */
			virtual void drive(const BW& input)
			{
				// Set the current "voltage data" of the bus to be the input
				//data = input;

				// Drive the connection, if it exists.
				if(connection.get() != nullptr)
				{
					connection->drive(input);
				}
			};

			/* read(...)
			 * Read data off the bus
			 * (atomic)
			 */
			const BW& read() { return data; };

		private:
			ContainerT data;
			mDrivable connection;
	};

	typedef Bus_Generic<BW_32> Bus_32;
	typedef Bus_Generic<BW_16> Bus_16;
	typedef std::vector<Bus> Bus_Vec;

	/* Generic_Mux
	 * (Multiplexor)
	 *
	 * This represents a m:1 mux with storage-class bitwide inputs and outputs.
	 * 
	 * The mux also acts as a synchronization barrier.
	 * The last thread to set an input inherits the execution of the output bus
	 *
	 * If a mux input is not properly fed, deadlock will occur.
	 *
	 * Other threads reaching this point end their job.
	 *
	 */
/*	template<int m, class storage_class> class Generic_Mux : public Execution_Synchronized
	{
		public:
			Generic_Mux() :
			  Execution_Synchronized(m + 1) // m + 1 since there are the n data inputs, but also the select input
			{}

		private:
			mBus input_buses[m];
			mBus output_bus;
			mBus select_bus;
	};
	
	typedef Generic_Mux<2, BW_32> Mux_2_1_32w;
	typedef Generic_Mux<4, BW_32> Mux_4_1_32w;*/

	typedef std::vector<mDrivable> Drivable_Vec;

	/* Node
	 * (Bus connection)
	 * This connects a bus to other buses, sequential logics, or muxes.
	 *
	 *
	 * It represents a node in a logical circuit
	 *
	 * Be aware, that the correctness of this still assumes
	 * that only one bus is driving a node/connection at once
	 */
	class Node : public Drivable
	{
		public:

			/* Drive the connection with data.
			 * A node ought not to drive to the Drivable which is currently driving it.
			 * This drives all connected devices' with the provided data accordingly.
			 */
			void drive(const BW& bin)
			{
				for(Drivable_Vec::iterator at = connected_devices.begin(); at != connected_devices.end(); ++at)
				{
					mDrivable dr = (*at);
				}
			}
		
			/* Connect a new device to this node.
			 */
			void connect(mDrivable new_device) { connected_devices.push_back(new_device); }

		private:
			
			Drivable_Vec connected_devices;
	};

	/* Execution Engine.
	 * The execution engine attempts to parallelize the work occurring within
	 * one clock cycle.
	 *
	 *
	 */
	class pHDL_Execution_Engine
	{

		public:

			/* pHDL_Work_Unit
			 * Each HDL work unit
			 * will execute on one sequential block and trace out the execution path along the graph.
			 * If:
			 *     The Work Unit encounters a path divergence: It will go down one path, and push the other paths back on the the work descriptor list
			 *     The Work Unit encounters a convergence upon two paths: It will attempt to inherit the path. If it fails (probably because the target has dependents it needs) it will relinquish the path.
			 *         this would imply another sequential block goes down this path (the other source branch) so it should not be pushed back on to the work descriptor list
			 *         (except the state update which itself will be pushed back at the lowest priority), and the thread should get
			 *         another work descriptor to work on in the mean time.
			 */
			class pHDL_Work_Unit
			{
				public:
					/* Application operator.
					 * Execute the work unit
					 */
					virtual void operator()() = 0;
			};

			class pHDL_Work_Seq_Unit : public pHDL_Work_Unit
			{
				public:
					/* Execute the work unit which is a sequential block chain in this case
					 */
					virtual void operator()() {this->work->prologue();}

					pHDL_Work_Seq_Unit(mSequentialBlock w) : work(w) {}

				private:
					mSequentialBlock work;
			};

			/* LoadFactor
			 * The amount of load this thread is experiencing.
			 * The higher it is, the more load.
			 * The lower it is, the less load.
			 */
			typedef size_t LoadFactor;

			typedef std::shared_ptr<pHDL_Work_Unit> mpHDL_Work_Unit;
			typedef std::queue<mpHDL_Work_Unit> WorkQueue;

			/* pHDL_EventHandler
			 * A special thread which checks the 
			 *
			 */
			class pHDL_EventHandler : public priscas_osi::UPThread
			{
				public:
					void Work();

					/* Add a work unit to this thread's local work queue.
					 * Adjusts the load factor of the associated thread accordingly. 
					 * (thread-safe)
					 */
					void addWork_ts(mpHDL_Work_Unit work) { wq_lock.lock(); wq.push(work); ++loadFac; wq_lock.unlock();}

					/* The "smallest" pHDL_EventHandler is going to be the
					 * one with the least load.
					 *
					 * Helps with load balancing.
					 *
					 */
					bool operator<(const pHDL_EventHandler& eh_2)
					{
						wq_lock.lock();
						return this->loadFac < eh_2.loadFac;
						wq_lock.unlock();
					}

					pHDL_EventHandler() :
						loadFac(0)
					{
						UPThread::ActivateThread(this);
					}

				private:
					WorkQueue wq;
					priscas_osi::mlock wq_lock;
					LoadFactor loadFac;
			};
			typedef std::shared_ptr<pHDL_EventHandler> mpHDL_EventHandler;

			/* Adds some work to the least occupied thread
			 */
			void Register_Work_Request(mSequentialBlock executable);

			
			typedef std::vector<mpHDL_EventHandler> UPThreadPool;

			pHDL_Execution_Engine(size_t threadcount) :
				tschedind(0)
			{
				threads.resize(threadcount);
				pHDL_EventHandler h;
				h.Execute();
				
				for(size_t tind = 0; tind < threads.size(); ++tind)
				{
					threads[tind] = mpHDL_EventHandler(new pHDL_EventHandler());
					threads[tind] ->Execute();
				}
			}

		private:
			size_t tschedind;
			UPThreadPool threads;
			
	};

	/* Other relavent typedefs
	 * (most corresponding to STL typedefing)
	 */

	/* Vector of Clock
	 */
	typedef std::vector<Clock> Clock_Vec;
}

#endif