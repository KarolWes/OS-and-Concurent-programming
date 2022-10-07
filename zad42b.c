#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{


    if(mkfifo("fifo", 0600) == -1){
        exit(10);
    }

    if(fork() == 0)
    {
        close(1);
        open("fifo", O_WRONLY);
        execlp("ps", "ps", "-ef", (char *)NULL);
        perror("ps");
        exit(1);
    }
    else{
        close(0);
        open("fifo", O_RDONLY);
        execlp("grep", "grep", "^root", (char * ) NULL);
        perror("grep");
        exit(1);
    }
    exit(0);
}
