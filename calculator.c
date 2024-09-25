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

    int value1, value2, result;
    char operation;
    char buffer[100];
    read(read_fd, buffer, sizeof(buffer));
    sscanf(buffer, "%d %c %d", &value1, &operation, &value2);

    printf("Calculator received the following: %d %c %d from FD %d\n", value1, operation, value2, read_fd);

    switch (operation) {
        case '+': result = value1 + value2; break;
        case '-': result = value1 - value2; break;
        case '*': result = value1 * value2; break;
        case '/': result = value1 / value2; break;
        default:
            fprintf(stderr, "Invalid operation\n");
            exit(1);
    }

    write(write_fd, &result, sizeof(int));
    printf("Calculator sent the following to the User: %d on FD %d\n", result, write_fd);

    return 0;
}