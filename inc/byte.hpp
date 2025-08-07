#pragma once

/// @defgroup libc libc
/// @{
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef LINUX
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif  // LINUX
        /// @}

/// @defgroup main main
/// @{
extern int main(int argc, char *argv[]);  ///< POSIX entry point
extern void arg(int argc, char *argv);    ///< print command line argument

/// @}

/// @defgroup parser parser
/// @{
extern void lexer(char *p, char *pe);  ///< lexer /ragel/
extern char *yyfile;                   ///< current file name
extern size_t yyline;                  ///< current line number
extern int dec(char *ts, char *te);    ///< sublexer for decimal integers
#include "byte.lemon.hpp"
/// @}
