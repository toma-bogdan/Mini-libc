#include <fcntl.h>
#include <internal/syscall.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int puts(const char * str)
{
    size_t len = strlen(str);
    int res = write(1,str,len);

    if (res < 0) {
        errno = res;
        return -1;
    }

    return res + write(1, "\n", 1);
}