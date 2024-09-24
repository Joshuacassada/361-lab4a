#include <stdio.h>
#include <unistd.h>

int main() {
    int num1, num2;
    char op;

    printf("Enter operation (e.g., 5 + 2): ");
    scanf("%d %c %d", &num1, &op, &num2);

    printf("%d %c %d\n", num1, op, num2);
    fflush(stdout);

    int result;
    scanf("%d", &result);

    printf("Result: %d\n", result);

    return 0;
}
