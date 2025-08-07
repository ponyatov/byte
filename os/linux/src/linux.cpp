#include "linux.hpp"
#include "byte.hpp"

int main(int argc, char *argv[]) {
    arg(0, argv[0]);

    for (int i = 1; i < argc; i++) {
        arg(i, argv[i]);
        yyfile = argv[i];

        int fd = open(argv[i], O_RDONLY);
        assert(fd > 0);
        struct stat st;
        fstat(fd, &st);
        size_t size = st.st_size;
        char *src = (char *)mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);

        assert(size > 0);
        lexer(src, src + size);

        munmap(src, st.st_size);
        close(fd);
        yyfile = nullptr;
    }
    return 0;
}
