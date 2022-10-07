#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX 512

int main(int argc, char* argv[])
{
    mkfifo("/tmp/fifo1", 0600);
    if(fork() == 0)
    {
        mkfifo("/tmp/fifo2", 0600);
        if(fork() == 0)
        {
            close(1);
            open("/tmp/fifo2", O_WRONLY);
            execlp("ps", "ps", "-ef", (char * ) NULL);
            perror("ps");
            exit(1);
        }
        else{
            close(1);
            close(0);
            open("/tmp/fifo2", O_RDONLY);
            open("/tmp/fifo1", O_WRONLY);
            execlp("tr", "tr", "-s", " ", (char * ) NULL);
            perror("tr");
            exit(1);
        }
    }
    else{
        close(0);
        open("/tmp/fifo1", O_RDONLY);
        execlp("cut", "cut","-f2", "-d", " ", (char * ) NULL);
        perror("cut");
        exit(1);
    }
    exit(0);
}
