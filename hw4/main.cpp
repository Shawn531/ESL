// main.cpp
#include "FIR16.h"
#include "systemc.h"

int sc_main(int argc, char* argv[]) {
	sc_signal <sc_uint<32> > x, y;
	sc_signal <bool> rst;
	sc_clock clk ("clk", 5, SC_NS, 0.5);

	// instantiation
	FIR16 fir16("fir16");
	fir16.clk(clk);
	fir16.rst(rst);
	fir16.x(x);
	fir16.y(y);
	
	// open and read file 
	std::ifstream ifs("firData");
	if(!ifs.is_open()) {
		cout << "failed to open file... " << endl;
		return (0);
	}

	// trace file creation, with VCD type output
	sc_trace_file *tf = sc_create_vcd_trace_file("RESULT");
	// External signals
	sc_trace(tf, clk, "clk" );
	sc_trace(tf, rst, "rst");
	sc_trace(tf, x, "x");
	sc_trace(tf, y, "y");

	//reset the timer for 3 cycles before it is released for counting
	sc_start(0, SC_NS);
	rst.write(0);
	sc_start(12.5, SC_NS);
	rst.write(1);
	sc_start(2.5, SC_NS);

	for(int i = 0;i < (64 + 18);i++)
	{
		int data;
		if(i < 64)
			ifs >> data;
		else
			data = 0;

		x.write(data);
		cout << "data = " << data << endl;
		sc_start(5, SC_NS);
		cout << "x = " << x << endl
			 << "y = " << y << endl;
	}
	
	ifs.close();

	sc_close_vcd_trace_file(tf);

	return(0);
}