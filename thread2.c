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
void *Pong(pthread_mutex_t *m){
    while(1){
        pthread_mutex_trylock(m);
        printf("Pong\n");
        pthread_mutex_unlock(m);
    }
    return;
}



int main(int argc, char* argv[])
{
    int err;
    pthread_mutex_t m1;
    err = pthread_mutex_init(&m1, NULL);
    pthread_mutex_t m2;
    err = pthread_mutex_init(&m2, NULL);
    pthread_t threadPing;
    pthread_t threadPong;
    pthread_mutex_lock(&m1);
    pthread_mutex_lock(&m2);
    err = pthread_create(&threadPing, NULL, (void * (*) (void( *)))Ping, &m1);
    err = pthread_create(&threadPong, NULL, (void * (*) (void( *)))Pong, &m2);
    while(1){
        pthread_mutex_unlock(&m1);
        sleep(2);
        pthread_mutex_trylock(&m1);
        pthread_mutex_unlock(&m2);
        sleep(2);
        pthread_mutex_trylock(&m2);
    }


    exit(0);
}

