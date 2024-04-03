#include "systemc.h"

SC_MODULE(FIR16) {
    sc_in<bool> clk;
    sc_in<bool> rst;
	sc_in<sc_uint<32> > x;
	sc_out<sc_uint<32> > y;

    sc_uint<32> acc;
    sc_signal<sc_uint<32> > output_buffer;

    sc_signal<sc_uint<32> > z[16];
    sc_uint<32> bi;

	void fir16();

	SC_CTOR(FIR16) {
        SC_CTHREAD(fir16, clk.pos());
        reset_signal_is(rst, false);
    }
};