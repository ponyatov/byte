#pragma once

/// @defgroup libc libc
/// @{
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef LINUX
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif  // LINUX

#include <map>
#include <string>

/// @}

/// @defgroup main main
/// @{
extern int main(int argc, char *argv[]);  ///< POSIX entry point
extern void arg(int argc, char *argv);    ///< print command line argument

/// @}

/// @defgroup parser parser
/// @ingroup compiler
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

/// @defgroup vm vm

/// @defgroup config config
/// @ingroup vm
/// @{
/// @ref M size, @ref byte s
#define Msz 0x10000
/// @ref R size, @ref call s
#define Rsz 0x100
#define Dsz 0x10
/// @}

/// @defgroup types types
/// @ingroup vm
/// @{
typedef uint8_t byte;   ///< single byte
typedef uint16_t addr;  ///< @ref M address (limited for MCUs & enumlation)
typedef int32_t cell;   ///< signed integer
/// @}

/// @defgroup memory memory
/// @ingroup vm
/// @{
extern byte M[Msz];  ///< bytecode/data memory
extern addr Cp;      ///< compiler pointer
extern addr Ip;      ///< instruction pointer
extern addr R[Rsz];  ///< return stack
extern uint8_t Rp;   ///< @ref R pointer
extern addr D[Dsz];  ///< data stack
extern uint8_t Dp;   ///< @ref D pointer
/// @}

/// @defgroup command command
/// @ingroup vm
/// @{

/// opcode
enum class Op : byte {
    nop = 0x00,   ///< `00` `( -- )` do nothing
    halt = 0xFF,  ///< `FF` `( -- )` stop system
    jmp = 0x01,   ///< `01` `( -- )` unconditional jump
    jz = 0x02,    ///< `02` `( flag -- )` jump if false
    call = 0x03,  ///< `03` `(R: -- addr )` nested call
    ret = 0x04,   ///< `04` `(R: addr -- )` return from @ref call
    lit = 0x05,   ///< `05` `( -- n )` push constant
};

extern void nop();   ///< `( -- )` do nothing
extern void halt();  ///< `( -- )` stop system
extern void jmp();   ///< `( -- )` unconditional jump
extern void jz();    ///< `( flag -- )` jump if false
extern void call();  ///< `(R: -- addr)` nested call
extern void ret();   ///< `(R: addr --)` return from @ref call
extern void lit();   ///< `( -- n )` push constant
/// @}

/// @defgroup compiler compiler
/// @ingroup vm
/// @{
std::map<std::string, addr> label;  ///< known labels
/// @}

/// @defgroup debug debug
/// @ingroup vm
/// @{
extern bool trace;  ///< trace flag

/// @}
