#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{

    mkfifo("fifo1", 0600);
    mkfifo("fifo2", 0600);
    mkfifo("fifo3", 0600);
    int pid = fork();
    if(pid == 0)
    {

        pid = fork();
        if(pid == 0){

            pid = fork();
            if(pid == 0)
            {
                close(1);
                open("fifo3", O_WRONLY);
                execlp("who", "who",(char *)NULL);
                perror("who");
                exit(1);
            }
            else{
                close(1);
                open("fifo2", O_WRONLY);
                close(0);
                open("fifo3", O_RDONLY);
                execlp("cut", "cut", "-f1", "-d", " ", (char *)NULL);
                perror("cut");
                exit(1);
            }

        }
        else{
            close(1);
            open("fifo1", O_WRONLY);
            close(0);
            open("fifo2", O_RDONLY);
            execlp("sort", "sort", (char *)NULL);
            perror("sort");
            exit(1);
        }

    }
    else{
        close(0);
        open("fifo1", O_RDONLY);
        execlp("uniq", "uniq", "-c", (char *)NULL);
        perror("uniq");
        exit(1);
    }
    exit(0);
}

