#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_TICKETS 100

typedef struct process {
    char name;
    int tickets;
    struct process *next;
} process;

process *get_winner(process *head) {
    int counter = 0;
    int winner = rand() % (TOTAL_TICKETS + 1);

    process *current = head;
    while (1) {
        counter += current->tickets;
        if (counter > winner) return current;
        current = current->next;
    }
}

int main(int argc, char *argv[]) {
    process c = { .name = 'C', .tickets = 20, .next = NULL };
    process b = { .name = 'B', .tickets = 30, .next = &c };
    process a = { .name = 'A', .tickets = 50, .next = &b };

    srand(time(NULL));
    process *winner = get_winner(&a);
    printf("Winner: process %c\n", winner->name);

    return 0;
}
