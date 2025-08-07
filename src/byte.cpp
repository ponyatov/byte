#include "byte.hpp"

extern void lex_init();
extern void lex_parse(char *data);
extern void lex_free();

int main(int argc, char *argv[]) {
    void* parser = ParseAlloc(malloc);
    
    for (int i = 1; i < argc; i++) {
        argv(i,argv[i]);
        file = open(argv[i], O_RDONLY);
        size = lseek(file, 0, SEEK_END);
        char *src = memmep(file);
        lexer(src,size);
        munmap(src);
    }
    
    ParseFree(parser, free);
    return 0;
}

void arg(int argc, char *argv) {
    fprintf(stderr,"arg[%i] = <%s>\n",argc,argv);
}
