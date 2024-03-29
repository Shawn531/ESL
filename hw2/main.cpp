// main.cpp
#include "timer.h"
#include "systemc.h"


int sc_main(int argc, char* argv[]) {
	sc_signal <bool> TIMEOUT, START;
	sc_signal <bool> TIMEOUT1, START1;
	sc_signal <bool> TIMEOUT2, START2;
	sc_clock CLOCK ("clock", 10, SC_NS, 0.5);

	timer tm("timer");
	tm.timeout(TIMEOUT);
	tm.start(START);
	tm.clock(CLOCK);

	timer tm1("timer1", 4);
	tm1.timeout(TIMEOUT1);
	tm1.start(START);
	tm1.clock(CLOCK);

	timer tm2("timer2", 6);
	tm2.timeout(TIMEOUT2);
	tm2.start(START);
	tm2.clock(CLOCK);


	// trace file creation with VCD
	sc_trace_file *tf ;
	tf = sc_create_vcd_trace_file("RESULT");
	// External signals
	sc_trace(tf, CLOCK, "clock");
	sc_trace(tf, TIMEOUT, "timeout");
	sc_trace(tf, START, "start");
	sc_trace(tf, tm.count, "count");

	sc_trace(tf, TIMEOUT1, "timeout1");
	sc_trace(tf, tm1.count, "count1");

	sc_trace(tf, TIMEOUT2, "timeout2");
	sc_trace(tf, tm2.count, "count2");


    // reset the timer for 3 cycle(30ns)
	START.write(1);
	sc_start(30,SC_NS);
	START.write(0);

	/* start to simulate */

	// during counting reset the timer before count reaches 0
	sc_start(65,SC_NS);
	START.write(1);
	sc_start(15,SC_NS);
	START.write(0);

	// during counting reset the timer after count reaches 0
	sc_start(35,SC_NS);
	START.write(1);
	sc_start(15,SC_NS);
	START.write(0);

	sc_start(55,SC_NS);
	START.write(1);
	sc_start(15,SC_NS);
	START.write(0);

	sc_start(70,SC_NS);
	START.write(1);

	sc_close_vcd_trace_file(tf);

	return(0);
}