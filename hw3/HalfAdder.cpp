#include "HalfAdder.h"

void HalfAdder::add() {
	Sum.write(A ^ B);
	Carry.write(A & B);
}