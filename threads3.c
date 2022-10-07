#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MAX 512


long long *factorial(int* n)
{
    long long result;
    result = 1;
    if(n < 0)
    {
        fprintf(stderr, "factorial of negative number is incalculable\n");
        result = -1ll;
        return result;
    }
    else if(n == 0)
    {
        result = 1ll;
        return result;
    }
    else{
        for(int i = 2; i <= *n; i++)
        {
            result *= i;
        }
        return result;
    }
}

long long *fibonacci(int* n)
{
    long long f0;
    long long f1;

    f0 = 0;
    f1 = 1;

    if(*n < 0)
    {
        f1 = -1;
        return f1;
    }
    else if(*n == 0)
    {
        f1 = 0;
        return f1;
    }
    else{
        for(int i = 2; i <= *n; i++)
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
    if(argc < 3){
        printf("To few parameters\n");
        exit(2);
    }
    void *fib_val;
    void *fact_val;
    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);
    pthread_t threadFact;
    pthread_create(&threadFact, NULL, (void * (*) (void(*)))factorial, &n1);
    pthread_t threadFib;
    pthread_create(&threadFib, NULL, (void * (*) (void(*)))fibonacci, &n2);
    pthread_join(threadFact, &fact_val);
    pthread_join(threadFib, &fib_val);
    long long val1 = (long long *) fib_val;
    long long val2 = (long long *) fact_val;
    printf("fib: %lld\n", val1);
    printf("fact: %lld\n", val2);
    long long res = val1 + val2;
    printf("res = %lld\n\n\n", res);
}
