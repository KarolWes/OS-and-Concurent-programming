#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int fin1 = open("num-2.dat", O_RDONLY);
    int fin2 = open("num-1.dat", O_RDONLY);
    int fout = open("num.dat", O_WRONLY);

    char a;
    char b;
    char dot = ',';
    while(read(fin1, &a, 1)){
        read(fin2, &b, 1);
        if(a >= '0' && a <= '9'){
            if(a <= b){
                write(fout, &a, 1);
                write(fout, &dot, 1);
                write(fout, &b, 1);
                write(fout, &dot, 1);
            }
            else{
                write(fout, &b, 1);
                write(fout, &dot, 1);
                write(fout, &a, 1);
                write(fout, &dot, 1);
            }
        }


    }
    close(fin1);
    close(fin2);
    close(fout);
}
