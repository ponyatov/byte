#include "byte.hpp"

// @ref main @ linux.cpp

void arg(int argc, char *argv) {
    fprintf(stderr, "arg[%i] = <%s>\n", argc, argv);
}

byte M[Msz];
addr Cp = 0;
addr Ip = 0;
addr R[Rsz];
uint8_t Rp = 0;
addr D[Dsz];
uint8_t Dp = 0;

void nop() {
    if (trace) fprintf(stderr, "nop\n");
}

void halt() {
    if (trace) fprintf(stderr, "halt\n");
    exit(-1);
}

bool trace = true;

std::map<std::string *, addr> label;

addr C(Op op) {
    M[Cp++] = (byte)op;
    return Cp;
}

addr C(int n) {
    *(cell *)&M[Cp] = n;
    Cp += sizeof(cell);
    return Cp;
}

void dump() {
    fprintf(stderr, "M[%.4X]:\n", Cp);
    for (int a = 0; a < Cp; a++) {
        if (a % 0x10 == 0x00) fprintf(stderr, "%.4X: ", a);
        fprintf(stderr, " %02X", M[a]);
        if (a % 0x10 == 0x0F) fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");
}
