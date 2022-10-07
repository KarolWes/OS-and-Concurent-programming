#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    unsigned long s = 0;
    if(argc < 2)
    {
        printf("wrong 1\n");
        fprintf(stderr, "something wrong");
        exit(1);
    }
    else{

        int fd = open(argv[1], O_RDONLY);
        if(fd == -1)
        {
            printf("wrong 2\n");
            fprintf(stderr, "cannot open a file\n");
            exit(1);
        }
        long buff_size = lseek(fd, 0, SEEK_END);
        lseek(fd, 0, SEEK_SET);
        for(int i = 0; i < buff_size; i++)
        {
            char ch;
            fprintf(stderr, ":%ld", read(fd, &ch, 1));
            s+=ch;
        }
        fprintf(stdout, "\n%lu\n", s);
        close(fd);
    }


    exit(0);
}
