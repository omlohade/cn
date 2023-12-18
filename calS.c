#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8000

int performCalculation(int operand1, int operand2, char operator) {
    switch (operator) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 != 0) {
                return operand1 / operand2;
            } else {
                printf("Error: Division by zero\n");
                return 0;  // Handle division by zero
            }
        default:
            printf("Error: Invalid operator\n");
            return 0;  // Handle invalid operator
    }
}

int main() {
    int serversocket, clientsocket;
    struct sockaddr_in serveraddress, clientaddress;

    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serversocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serversocket, (struct sockaddr *)&serveraddress, sizeof(serveraddress)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    listen(serversocket, 5);

    printf("Server waiting for client...\n");

    socklen_t clientaddress_len = sizeof(clientaddress);
    clientsocket = accept(serversocket,NULL,NULL);

    if (clientsocket < 0) {
        perror("Acceptance failed");
        exit(EXIT_FAILURE);
    }

    printf("Connection accepted\n");

    char operator;
    int operand1, operand2, result;

    // Receive client requests and perform calculations
    while (1) {
        recv(clientsocket, &operand1, sizeof(operand1), 0);
        recv(clientsocket, &operator, sizeof(operator), 0);
        recv(clientsocket, &operand2, sizeof(operand2), 0);

        if (operator == 'q') {
            printf("Server shutting down\n");
            break;
        }

        result = performCalculation(operand1, operand2, operator);
        send(clientsocket, &result, sizeof(result), 0);

        printf("Calculation result: %d %c %d = %d\n", operand1, operator, operand2, result);
    }

    close(serversocket);
    close(clientsocket);

    return 0;
}

