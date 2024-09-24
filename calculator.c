#include <stdio.h>

int main() {
    int num1, num2, result;
    char op;

    // Read the operation from the request pipe (stdin)
    scanf("%d %c %d", &num1, &op, &num2);

    // Perform the calculation
    switch (op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': result = num1 / num2; break;
        default:
            fprintf(stderr, "Invalid operator\n");
            return 1;
    }

    // Send the result back via the reply pipe (stdout)
    printf("%d\n", result);
    fflush(stdout);

    return 0;
}
