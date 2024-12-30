#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int pipeline[2];

    pipe(pipeline);

    int ch_pid = fork();

    if (ch_pid == 0) {
        char ch;
        int my_pid = getpid();

        read(pipeline[0], &ch, 1);
        write(pipeline[1], &ch, 1);
        printf("%d: received ping\n", my_pid);
    }
    else {    
        char ch = 'Y';
        int my_pid = getpid();
        int status;

        write(pipeline[1], &ch, 1);
        wait(&status);
        read(pipeline[0], &ch, 1);
        printf("%d: received pong\n", my_pid);
    }

    exit(0);
}
