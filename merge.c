#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    if(argc < 4)
    {
        fprintf(stderr, "To few parameters\n");
        exit(1);
    }
    else{
        int file_a = open(argv[1], O_RDONLY);
        int file_b = open(argv[2], O_RDONLY);
        int file_ab = open(argv[3], O_WRONLY);
        if(file_a == -1 || file_b == -1 || file_ab == -1)
        {
            fprintf(stderr, "Cannot open a file\n");
            exit(10);
        }
        long a_size = lseek(file_a, 0, SEEK_END);
        lseek(file_a,0,SEEK_SET);
        lseek(file_b,0,SEEK_SET);
        int saved = 0;
        for(int i = 0; i < a_size; i+=1)
        {
            char a[2];
            read(file_a, a, 1);
            read(file_b, &a[1], 1);
            write(file_ab, a, 2);
            saved +=2;
        }
        fprintf(stderr, "Saved %d chars\n", saved);
        close(file_a);
        close(file_b);
        close(file_ab);

    }
    exit(0);
}
