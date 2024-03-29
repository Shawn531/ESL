// timer.h
#include "systemc.h"

SC_MODULE(timer) {
	sc_in<bool> start;
	sc_out<bool> timeout;
	sc_in<bool> clock;

	unsigned int count_value;

	unsigned int count;

	void runtimer();

	timer(sc_module_name name_, unsigned int count_value= 5) :
		  sc_module(name_), count_value(count_value) {
		SC_HAS_PROCESS(timer);
		SC_CTHREAD(runtimer, clock.pos());
		reset_signal_is(start, true);
	}
};