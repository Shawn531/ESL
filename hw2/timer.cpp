// timer.cpp
#include "timer.h"

void timer::runtimer() {
	count = count_value;
	timeout = false;
	cout << "Timer: start detected " << endl;
	while(1) {
		wait();
		if (count > 0) {
			count--;
			timeout = false;
		} else {
			timeout = true;
		}
	}
}