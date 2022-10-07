#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int char_to_int(char *c)
{
    int c_size = sizeof(c)/sizeof(char);
    printf("char_to_int: %d\n", c_size);
    int res=0;
    for(int i = 0; i < c_size; i+=1)
    {
        res*=10;
        res+=(c[i]-'0');
    }
    return res;
}

int main(int argc, char* argv[])
{
    if(argc < 4)
    {
        fprintf(stderr, "To few parameters\n");
        exit(1);
    }
    else{
        int file_in = open(argv[1], O_RDONLY);
        int id = atoi(argv[2]);
        fprintf(stderr, "%d\n", id);
        int file_out = open(argv[3], O_WRONLY);

        if(file_in == -1||file_out==-1)
        {
            fprintf(stderr, "cannot open file\n");
            exit(2);
        }
        long file_size = lseek(file_in, 0, SEEK_END);
        lseek(file_in, 0, SEEK_SET);
        if(id > file_size)
        {
            fprintf(stderr, "Cannot delete nonexistent char\n");
            exit(3);
        }
        for(int i = 0; i < file_size; i+=1)
        {
            char c;
            read(file_in, &c, 1);
            if(i != id)
            {
                write(file_out, &c, 1);
            }
        }
        close(file_in);
        close(file_out);

    }

    exit(0);
}

