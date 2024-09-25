#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <write_fd> <read_fd>\n", argv[0]);
        exit(1);
    }

    int write_fd = atoi(argv[1]);
    int read_fd = atoi(argv[2]);

    printf("This is the User process (id = %d).\n", getpid());
    printf("User: Please, enter: value1 operation value2\n");

    int value1, value2;
    char operation;
    scanf("%d %c %d", &value1, &operation, &value2);

    dprintf(write_fd, "%d %c %d\n", value1, operation, value2);
    printf("User Sending the following: %d %c %d on FD %d\n", value1, operation, value2, write_fd);

    int result;
    read(read_fd, &result, sizeof(int));
    printf("User Received the following result: %d from FD %d\n", result, read_fd);

    return 0;
}
