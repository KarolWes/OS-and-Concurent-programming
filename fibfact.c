#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


long long factorial(int n)
{
    long long result = 1;
    if(n < 0)
    {
        fprintf(stderr, "factorial of negative number is incalculable\n");
        return -1;
    }
    else if(n == 0)
    {
        return 1;
    }
    else{
        for(int i = 2; i <= n; i++)
        {
            result *= i;
        }
        return result;
    }
}

long long fibonacci(int n)
{
    long long f0 = 0;
    long long f1 = 1;

    if(n < 0)
    {
        return -1;
    }
    else if(n == 0)
    {
        return f0;
    }
    else{
        for(int i = 2; i < n; i++)
        {
            long long tmp = f1;
            f1 += f0;
            f0 = tmp;
        }
        return f1;
    }

}


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "To few parameters\n");
        exit(1);
    }
    int N = argv[1];
    int pid = fork();
    if(pid == 0)
    {
        fprintf(stdout, "%d: silnia(%d) = %ll", getpid(), N, factorial(N));
        exit(0);
    }
    else{
        pid = fork();
        if(pid == 0)
        {
            fprintf(stdout, "%d: silnia(%d) = %ll", getpid(), N, fibonacci(N));
            exit(0);
        }
    }
    fprintf(stdout, "%d: KONIEC", getpid());
    wait(NULL);
    exit(0);
}
