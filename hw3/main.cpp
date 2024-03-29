// main.cpp
#include "FullAdder.h"
#include "HalfAdder.h"
#include "systemc.h"


int sc_main(int argc, char* argv[]) {
	sc_signal <bool> HA, HB, HSum, HCarry;
	sc_signal <bool> FA, FB, FCin, FS, FCout, FS_temp, FC_temp, FC_temp1;
	sc_clock CLOCK ("clock", 10, SC_NS, 0.5);

	HalfAdder half_adder("half_adder");
    half_adder.A(HA);
    half_adder.B(HB);
    half_adder.Sum(HSum);
    half_adder.Carry(HCarry);

	FullAdder full_adder("full_adder");
	full_adder.A(FA);
	full_adder.B(FB);
	full_adder.Cin(FCin);
	full_adder.S(FS);
	full_adder.Cout(FCout);


	// trace file creation with VCD
	sc_trace_file *tf ;
	tf = sc_create_vcd_trace_file("RESULT");
	sc_trace(tf, CLOCK, "clock");
	// External signals
	sc_trace(tf, HA, "Half_adder_A");
	sc_trace(tf, HB, "Half_adder_B");
	sc_trace(tf, HSum, "Half_adder_Sum");
	sc_trace(tf, HCarry, "Half_adder_Carry");

	sc_trace(tf, FA, "Full_adder_A");
	sc_trace(tf, FB, "Full_adder_B");
	sc_trace(tf, FCin, "Full_adder_Cin");
	sc_trace(tf, FS, "Full_adder_S");
	sc_trace(tf, FCout, "Full_adder_Cout");

	// write some pattern
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			HA.write(i);
			HB.write(j);
			sc_start(10, SC_NS);
		}
	}

	HA.write(0);
	HB.write(0);

	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 2; j++) {
			for(int k = 0; k < 2; k++) {
				FA.write(k);
				FB.write(j);
				FCin.write(i);
				sc_start(10, SC_NS);
			}
		}
	}

	sc_close_vcd_trace_file(tf);

	return(0);
}