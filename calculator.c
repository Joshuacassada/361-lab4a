#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <read_fd> <write_fd>\n", argv[0]);
        exit(1);
    }

    int read_fd = atoi(argv[1]);
    int write_fd = atoi(argv[2]);

    printf("This is the Calculator process (id = %d).\n", getpid());
    printf("Calculator Waiting to receive from FD %d\n", read_fd);

    int num1, num2, result;
    char op;
    char buffer[100];
    read(read_fd, buffer, sizeof(buffer));
    sscanf(buffer, "%d %c %d", &num1, &op, &num2);

    printf("Calculator received the following: %d %c %d from FD %d\n", num1, op, num2, read_fd);

    switch (op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': result = num1 / num2; break;
        default:
            fprintf(stderr, "Invalid operation\n");
            exit(1);
    }

    write(write_fd, &result, sizeof(int));
    printf("Calculator sent the following to the User: %d on FD %d\n", result, write_fd);

    return 0;
}