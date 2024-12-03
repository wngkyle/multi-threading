/* 
    Terminal Run Command: 
        $ gcc thread.c -o thread_c
        $ ./thread_c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* workerThreadFunction(void* tid) {
    long* myID = (long*) tid;
    printf("Hello World! This is thread %ld\n", *myID);
    return NULL; // Returning a valid void value
}

int main() {
    pthread_t tid0; // Data type of pthread_t (a large integer)
    pthread_t tid1;
    pthread_t tid2;
    pthread_t* pthreads[3] = { &tid0, &tid1, &tid2 };
    for (int i = 0; i < 3; i++) {
        // pthread_create returns 0 if the call completes successfully
        int rc = pthread_create(pthreads[i], NULL, workerThreadFunction, (void *)&pthreads[i]); // Create a new ID and assign that ID to tid
        if (rc) {
            printf("Error creating thread %ld\n", (long) pthreads[i]);
            exit(-1);
        }
    }

    pthread_exit(NULL); // Forces the main thread to wait until the pthreads are done executing
    return 0;
}
