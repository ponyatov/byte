#include "byte.hpp"

int main(int argc, char *argv[]) {
    arg(0, argv[0]);
    void *parser = ParseAlloc(malloc);

    for (int i = 1; i < argc; i++) {
        arg(i, argv[i]);

        int fd = open(argv[i], O_RDONLY);
        struct stat st;
        size_t size = st.st_size;
        fstat(fd, &st);
        char *src = (char *)mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);

        lexer(src, src + size);

        munmap(src, st.st_size);
        close(fd);
    }
    ParseFree(parser, free);
    return 0;
}

void arg(int argc, char *argv) {
    fprintf(stderr, "arg[%i] = <%s>\n", argc, argv);
}
