#ifndef HALFADDER_H
#define HALFADDER_H
#include "systemc.h"

SC_MODULE(HalfAdder) {
	sc_in<bool> A;
	sc_in<bool> B;
	sc_out<bool> Sum;
	sc_out<bool> Carry;


	void add();


	SC_CTOR(HalfAdder) {
		SC_METHOD(add);
		sensitive << A << B;
	}
};
#endif