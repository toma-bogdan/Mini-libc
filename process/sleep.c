#include <time.h>
#include <unistd.h>
#include <errno.h>

unsigned int sleep(unsigned int seconds)
{
	struct timespec req, rem;
    int res;
    req.tv_sec = seconds;
    req.tv_nsec = 0;

    while (1) {
        res = nanosleep(&req, &rem);
        if (res > 0 && errno != EINTR){
            return 0;
        }
        req = rem;
    }

	return -1;
}