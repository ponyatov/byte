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
extern size_t yyline;                  ///< current line
extern size_t yycol;                   ///< current column
extern int dec(char *ts, char *te);    ///< sublexer for decimal integers
#include "byte.lemon.hpp"

#define parserTOKENTYPE int
#define parserARG_PDECL
#define parserCTX_PDECL

extern void parser(void *yyp,              /* The parser */
                   int yymajor,            /* The major token code number */
                   parserTOKENTYPE yyminor /* The value for the token */
                       parserARG_PDECL /* Optional %extra_argument parameter */
);

#ifndef YYMALLOCARGTYPE
#define YYMALLOCARGTYPE size_t
#endif

extern void *parserAlloc(void *(*mallocProc)(YYMALLOCARGTYPE)parserCTX_PDECL);

extern void parserFree(void *p,                 /* The parser to be
                                                                    deleted */
                       void (*freeProc)(void *) /* Function used to
                                                   reclaim memory */
);

/// @}
