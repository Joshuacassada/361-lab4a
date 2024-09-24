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
        char req_fd[10], rply_fd[10];
        snprintf(req_fd, sizeof(req_fd), "%c", reqPipe[1]);
        snprintf(rply_fd, sizeof(rply_fd), "%c", rplyPipe[0]);

        execlp("./user", "Jim", req_fd, rply_fd, NULL);
        perror('Failed');
        exit(1);
    }

    pid_t right_kid = fork();
    if (right_kid < 0){
        perror("Fork Failed");
        exit(-1);
    }

    if (right_kid == 0){
        close(reqPipe[1]);
        close(rplyPipe[0]);
        char req_fd[10], rply_fd[10];
        snprintf(req_fd, sizeof(req_fd), "%d", reqPipe[0]);
        snprintf(rply_fd, sizeof(rply_fd), "%d", rplyPipe[1]);

        execlp("./calculator", "Jim", req_fd, rply_fd, NULL);
        perror('Failed');
        exit(1);
    }


    close(reqPipe[0]);
    close(reqPipe[1]);
    close(rplyPipe[0]);
    close(rplyPipe[1]);


}