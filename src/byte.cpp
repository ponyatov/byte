#include "byte.hpp"

// @ref main @ linux.cpp

void arg(int argc, char *argv) {
    fprintf(stderr, "arg[%i] = <%s>\n", argc, argv);
}

void nop() {
    if (trace) fprintf(stderr, "nop\n");
}

void halt() {
    if (trace) fprintf(stderr, "halt\n");
    exit(-1);
}

bool trace = true;
