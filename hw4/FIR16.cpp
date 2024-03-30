#include "FIR16.h"

void FIR16::fir16() {
    bi = 0x00000F0F;
    acc = 0;
    for (int i = 0; i < 16; i++) {
        z[i] = 0;
    }

    while(1) {
        wait();
        acc = x.read() * bi;
        for (int i = 0; i < 16; i++) {
            if (i == 0) z[0] = x.read();
            else        z[i] = z[i-1];
            acc += z[i].read() * bi;
        }

        y.write(acc);
    }
}