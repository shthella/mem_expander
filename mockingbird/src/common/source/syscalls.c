// syscalls.c: Minimal syscalls for newlib on bare-metal

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int _read(int fd, char *ptr, int len) { return 0; }

int _close(int fd) { return -1; }
int _lseek(int fd, int ptr, int dir) { return 0; }
int _fstat(int fd, struct stat *st) { st->st_mode = S_IFCHR; return 0; }
int _isatty(int fd) { return 1; }
int _kill(int pid, int sig) { errno = EINVAL; return -1; }
int _getpid(void) { return 1; }

void *_sbrk(ptrdiff_t incr) {
    extern char __heap_start__;  // Defined in linker script
    static char *heap_end;
    char *prev_heap;

    if (heap_end == 0)
        heap_end = &__heap_start__;

    prev_heap = heap_end;
    heap_end += incr;

    return (void *)prev_heap;
}

void _exit(int status) { while (1); }

