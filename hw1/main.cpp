// main.cpp
#include "timer.h"
#include "systemc.h"


int sc_main(int argc, char* argv[]) {
	sc_signal <bool> TIMEOUT, START;
	sc_clock CLOCK ("clock", 10, SC_NS, 0.5);

	timer tm("timer");
	tm.timeout(TIMEOUT);
	tm.start(START);
	tm.clock(CLOCK);

	// trace file creation with VCD
	sc_trace_file *tf ;
	tf = sc_create_vcd_trace_file("RESULT");
	// External signals
	sc_trace(tf, CLOCK, "clock");
	sc_trace(tf, TIMEOUT, "timeout");
	sc_trace(tf, START, "start");
	sc_trace(tf, tm.count, "count");

    // reset the timer for 3 cycle(30ns)
	START.write(1);
	sc_start(30,SC_NS);
	START.write(0);

	/* start to simulate */

	// during counting reset the timer before count reaches 0
	sc_start(60,SC_NS);
	START.write(1);
	sc_start(10,SC_NS);
	START.write(0);

	// during counting reset the timer after count reaches 0
	sc_start(30,SC_NS);
	START.write(1);
	sc_start(10,SC_NS);
	START.write(0);

	sc_start(40,SC_NS);
	START.write(1);
	sc_start(10,SC_NS);
	START.write(0);

	sc_start(110,SC_NS);
	START.write(1);

	sc_close_vcd_trace_file(tf);

	return(0);
}