#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8000

int main() {
    int clientsocket;
    struct sockaddr_in serveraddress;

    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientsocket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_addr.s_addr = INADDR_ANY;

    if (connect(clientsocket, (struct sockaddr *)&serveraddress, sizeof(serveraddress)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    char operator;
    int operand1, operand2, result;

    while (1) {
        printf("Enter operator (+, -, *, /) or 'q' to quit: ");
        scanf(" %c", &operator);

        if (operator == 'q') {
            send(clientsocket, &operand1, sizeof(operand1), 0);
            send(clientsocket, &operator, sizeof(operator), 0);
            send(clientsocket, &operand2, sizeof(operand2), 0);
            printf("Client shutting down\n");
            break;
        }

        printf("Enter operands: ");
        scanf("%d %d", &operand1, &operand2);

        send(clientsocket, &operand1, sizeof(operand1), 0);
        send(clientsocket, &operator, sizeof(operator), 0);
        send(clientsocket, &operand2, sizeof(operand2), 0);

        recv(clientsocket, &result, sizeof(result), 0);

        printf("Result: %d %c %d = %d\n", operand1, operator, operand2, result);
    }

    close(clientsocket);

    return 0;
}

