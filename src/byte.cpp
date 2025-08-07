#include "byte.hpp"

// @ref main @ linux.cpp

void arg(int argc, char *argv) {
    fprintf(stderr, "arg[%i] = <%s>\n", argc, argv);
}

byte M[Msz];
addr Cp=0;
addr Ip=0;
addr R[Rsz];
uint8_t Rp=0;
addr D[Dsz];
uint8_t Dp=0;

void nop() {
    if (trace) fprintf(stderr, "nop\n");
}

void halt() {
    if (trace) fprintf(stderr, "halt\n");
    exit(-1);
}

bool trace = true;

std::map<std::string *, addr> label;
