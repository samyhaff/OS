#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hellow world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failded\n");
        exit(1);
    } else if (rc == 0) {
        printf("hello, I am child (pid:%d)\n", (int) getpid());
    } else {
        int rc_wait = wait(NULL);
        printf("hello, I am parent of %d (pid:%d) (rc_wait:%d)\n",
               rc, (int) getpid(), rc_wait);
    }
    return 0;
}
