#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX 512

int main(int argc, char* argv[])
{
    int pdesc[2];

    pipe(pdesc);
    if(fork() == 0)
    {
        dup2(pdesc[1],1);
        execvp("finger", argv);
        exit(1);
    }
    else{
        close(pdesc[1]);
        dup2(pdesc[0], 0);
        execlp("cut", "cut", "-d", " ", "-f1", 0);
        exit(1);
    }
    exit(0);
}
