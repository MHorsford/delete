#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock1, lock2;

void* processA(void* arg) {
    pthread_mutex_lock(&lock1);
    printf("Process A acquired lock 1\n");
    sleep(1); // Simula algum processamento
    pthread_mutex_lock(&lock2);
    printf("Process A acquired lock 2\n");

    // Release locks
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
}

void* processB(void* arg) {
    pthread_mutex_lock(&lock2);
    printf("Process B acquired lock 2\n");
    sleep(1); // Simula algum processamento
    pthread_mutex_lock(&lock1);
    printf("Process B acquired lock 1\n");

    // Release locks
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock1, NULL);
    pthread_mutex_init(&lock2, NULL);

    pthread_create(&t1, NULL, processA, NULL);
    pthread_create(&t2, NULL, processB, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    return 0;
}
