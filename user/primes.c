#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define MAXN 280

__attribute__((noreturn))
void seize_prime(int ppl[2]) {
    int prime, n;
    int cpl[2];
    bool fork_child = false;

    close(ppl[1]);
    dup(ppl[0]);

    if (read(ppl[0], &prime, sizeof(int)) == 0) {
        exit(0);
    }
    
    printf("prime %d\n", prime);

    while (read(ppl[0], &n, sizeof(int)) != 0) {
        if (prime * prime >= n) {
            printf("prime %d\n", n);
        }
        else if (n % prime != 0) {
            if (! fork_child) {
                pipe(cpl);

                if (fork() == 0) {
                    seize_prime(cpl);
                }

                close(cpl[0]);
                fork_child = true;
            }

            write(cpl[1], &n, sizeof(int));
        }
    }

    if (fork_child)
        close(cpl[1]);

    close(ppl[0]);
    wait(NULL);
    exit(0);
}


int main (int argc, char * argv[]) {
    int pl[2];
    int cpid;

    pipe(pl);

    if ((cpid = fork()) == 0) {
        seize_prime(pl);
    }
    else {
        close(pl[0]);

        for (int n = 2; n <= MAXN; n++) {
            write(pl[1], &n, sizeof(int));
        }

        close(pl[1]);
        wait(NULL);
    }

    exit(0);
}
