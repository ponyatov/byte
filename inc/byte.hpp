#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "byte.h"

#ifdef LINUX
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif  // LINUX

extern int main(int argc, char *argv[]);
extern void arg(int argc, char *argv);

extern void lexer(char *p, char *pe);
