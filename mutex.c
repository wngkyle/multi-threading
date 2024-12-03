#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

char* helloMessage;
pthread_mutex_t helloMessageLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t messageCreatedCondition = PTHREAD_COND_INITIALIZER;
int messageInitialized = 0;

/*
    Using mutex to protect the messageInitialized variable
*/

void* workerThreadFunction(void* tid) {
    helloMessage = "Hello World!";
    pthread_mutex_lock(&helloMessageLock);
    messageInitialized = 1;
    pthread_cond_signal(&messageCreatedCondition); // Signal the condition to wake up workerThreadFunction2 that is put into sleep
    pthread_mutex_unlock(&helloMessageLock);
    return NULL;
}

void* workerThreadFunction2(void* tid) {
    pthread_mutex_lock(&helloMessageLock);
    while (messageInitialized == 0) {
        pthread_cond_wait(&messageCreatedCondition, &helloMessageLock); // Waiting to be signal by workerThreadFunction
    }
    pthread_mutex_unlock(&helloMessageLock);
    for (int i = 0; i < 13; i++) {
        printf("%c", helloMessage[i]);
    }
    printf("\n");
    return NULL;
}

int main() {
    pthread_t tid0;
    pthread_t tid1;

    pthread_create(&tid0, NULL, workerThreadFunction, (void*) &tid0);
    pthread_create(&tid1, NULL, workerThreadFunction2, (void*) &tid1);

    pthread_exit(NULL);
}
