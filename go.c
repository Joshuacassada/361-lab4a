#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int reqPipe[2], rplyPipe[2];

    if (pipe(reqPipe) == -1 || pipe(rplyPipe) == -1){
        perror("error");
        exit(1);
    }

    pid_t left_kid = fork();
    if (left_kid < 0){
        perror("Fork Failed");
        exit(-1);
    }

    if (left_kid == 0){
        close(reqPipe[0]);
        close(rplyPipe[1]);

        

    }

}