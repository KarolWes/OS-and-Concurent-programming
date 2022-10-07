#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MAX 512

void *Ping(pthread_mutex_t *m){
    while(1){
        pthread_mutex_trylock(m);
        printf("Ping\n");
        pthread_mutex_unlock(m);
    }
    return;
}

int main(int argc, char* argv[])
{
    int err;
    pthread_mutex_t m;
    err = pthread_mutex_init(&m, NULL);
    pthread_t thread;
    err = pthread_create(&thread, NULL, (void * (*) (void( *)))Ping, &m);
    while(1){
        pthread_mutex_trylock(&m);
        printf("Pong\n");
        pthread_mutex_unlock(&m);
    }


    exit(0);
}
