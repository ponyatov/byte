#include "byte.hpp"

int main(int argc, char *argv[]) {
    arg(0, argv[0]);
    for (int i = 1; i < argc; i++) {  //
        arg(i, argv[i]);
    }
}

//     void* pParser = ParseAlloc(malloc);
    
//     Parse(pParser, NUMBER, "42", 0);
//     Parse(pParser, PLUS, 0, 0);
//     Parse(pParser, NUMBER, "10", 0);
//     Parse(pParser, 0, 0, 0);
    
//     ParseFree(pParser, free);


void arg(int argc, char *argv) { //
    fprintf(stderr,"arg[%i] = <%s>\n",argc,argv);
}
