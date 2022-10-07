#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    close(0);
    int filein = open("dane.txt", O_RDONLY);
    close(1);
    int fileout = open("wynik.txt", O_WRONLY);
    if(filein == -1 || fileout == -1)
    {
        fprintf(stderr, "cannot open the file\n");
        exit(10);
    }

    int a;
    int b = -1;
    while(scanf("%d ", &a) != EOF)
    {
        fprintf(stderr, "%d\n", a);
        printf("%d^2=%d\n", a, a*a);
    }
    close(filein);

    exit(0);
}
