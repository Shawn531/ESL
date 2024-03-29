#ifndef FULLADDER_H
#define FULLADDER_H

#include "systemc.h"
#include "HalfAdder.h"

SC_MODULE(FullAdder) {
	sc_in<bool> A;
	sc_in<bool> B;
    sc_in<bool> Cin;
	sc_out<bool> S;
	sc_out<bool> Cout;
    sc_signal<bool> S_temp;
    sc_signal<bool> C_temp, C_temp1;
    HalfAdder *half_adder1;
    HalfAdder *half_adder2;
	void do_or();

    SC_CTOR(FullAdder) {
        half_adder1 = new HalfAdder("ha1");
        half_adder2 = new HalfAdder("ha2");
        half_adder1->A(A);
        half_adder1->B(B);
        half_adder1->Sum(S_temp);
        half_adder1->Carry(C_temp);

        half_adder2->A(S_temp);
        half_adder2->B(Cin);
        half_adder2->Sum(S);
        half_adder2->Carry(C_temp1);

        SC_METHOD(do_or);
        sensitive << C_temp << C_temp1;
    }
    
    ~FullAdder() {
    delete half_adder1; //free up memory
    delete half_adder2;
    }
};
#endif