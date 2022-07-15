#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 100

int main(int argc, char *argv[]) {
    int filedes[2]; // (read, write)
    int status;
    char buff[BUFSIZE];

    status = pipe(filedes);
    if (status == -1) {
        printf("pipe failed\n");
        exit(1);
    }

    int rc_1 = fork();
    if (rc_1 == -1) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc_1 == 0) {
        close(filedes[0]);
        dup2(filedes[1], STDOUT_FILENO); // stdout -> pipe write
        printf("test\n") ;
        close(filedes[1]);
    } else {
        int rc_2 = fork();
        if (rc_2 == -1) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc_2 == 0) {
            close(filedes[1]);
            dup2(filedes[0], STDIN_FILENO); // stdin -> pipe read
            read(STDIN_FILENO, buff, BUFSIZE);
            printf("%s", buff);
        }
    }
    return 0;
}
