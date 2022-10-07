#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *Ping(pthread_mutex_t *m)
{
    while(1){
        pthread_mutex_trylock(m);
        printf("Ping\n");
        pthread_mutex_unlock(m);
    }
}


int main(int argc, char* argv[]){

    pthread_mutex_t m;
    pthread_mutex_init(&m, NULL);
    pthread_t thr;
    pthread_create(&thr, NULL, (void * (*)(void *))Ping, &m);

    while(1){
        pthread_mutex_trylock(&m);
        printf("Pong\n");
        pthread_mutex_unlock(&m);
    }
    exit(0);
}
