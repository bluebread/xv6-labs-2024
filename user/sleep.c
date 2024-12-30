#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc >= 2) {
        int t = atoi(argv[1]);
        sleep(t);
    } 
    else {
        char msg[] = "Error: Missing 1 required argument.\n";
        write(1, msg, sizeof(msg));
    }

    exit(0);
}
