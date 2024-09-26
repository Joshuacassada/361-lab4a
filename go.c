#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int req_pipe[2], reply_pipe[2];

    if (pipe(req_pipe) == -1 || pipe(reply_pipe) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    printf("\nGo started and created these pipes\n");
    printf("\t\tUser-to-Calculator Request pipe: read=%d write=%d\n", req_pipe[0], req_pipe[1]);
    printf("\t\tCalculator-to-User Reply pipe: read=%d write=%d\n", reply_pipe[0], reply_pipe[1]);

    pid_t user_pid = fork();
    if (user_pid == 0) {
        close(req_pipe[0]);
        close(reply_pipe[1]);
        char write_fd[10], read_fd[10];
        snprintf(write_fd, sizeof(write_fd), "%d", req_pipe[1]);
        snprintf(read_fd, sizeof(read_fd), "%d", reply_pipe[0]);
        execl("./user", "user", write_fd, read_fd, NULL);
        perror("User exec failed");
        exit(1);
    }

    pid_t calc_pid = fork();
    if (calc_pid == 0) {
        close(req_pipe[1]);
        close(reply_pipe[0]);
        char read_fd[10], write_fd[10];
        snprintf(read_fd, sizeof(read_fd), "%d", req_pipe[0]);
        snprintf(write_fd, sizeof(write_fd), "%d", reply_pipe[1]);
        execl("./calc", "calculator", read_fd, write_fd, NULL);
        perror("Calculator exec failed");
        exit(1);
    }

    close(req_pipe[0]);
    close(req_pipe[1]);
    close(reply_pipe[0]);
    close(reply_pipe[1]);

    printf("\nGo is now waiting for User to terminate\n");
    waitpid(user_pid, NULL, 0);
    printf("\nGo is now waiting for Calculator to terminate\n");
    waitpid(calc_pid, NULL, 0);
    printf("The Go process has terminated\n");

    return 0;
}