#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define COUNT 1000000000UL
int counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *count(void *arg) {
    for (u_int32_t i = 0; i < COUNT; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t t;
    pthread_create(&t, NULL, count, NULL);
    count(NULL);
    pthread_join(t, NULL);
    printf("Counter = %d\n", counter);

    return 0;
}
