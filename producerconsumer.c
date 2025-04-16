#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mutex = 1;
int full = 0;
int empty = 1;
int x = 0;

int wait(int s) {
    return (--s);
}

int signal(int s) {
    return (++s);
}

void producer() {
    mutex = wait(mutex);
    if (empty != 0) {
        full = signal(full);
        empty = wait(empty);
        x = rand() % 50 + 1; // Random number between 1 and 50
        printf("Producer 1 produced %d\n", x);
    } else {
        printf("Buffer is full, producer is waiting\n");
    }
    mutex = signal(mutex);
}

void consumer() {
    mutex = wait(mutex);
    if (full != 0) {
        full = wait(full);
        empty = signal(empty);
        printf("Consumer 2 consumed %d\n", x);
        x = 0; // After consumption, buffer is empty
    } else {
        printf("Buffer is empty, consumer is waiting\n");
    }
    mutex = signal(mutex);
}

int main() {
    int n, i;

    printf("Enter the number of Producers: 1\n");
    printf("Enter the number of Consumers: 1\n");
    printf("Enter buffer capacity: 1\n");

    printf("Successfully created producer 1\n");
    printf("Successfully created consumer 1\n");

    srand(time(NULL));  // Seed for random number generation

    for (i = 0; i < 10; i++) {
        producer();
        printf("Buffer: %d\n", x);
        consumer();
        printf("Current buffer len: %d\n", x);
    }

    return 0;
}
