#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include<time.h>


#define TIMEOUT 3
#define MAX_FRAMES 10

// Function to simulate random acknowledgment loss
bool shouldLoseAcknowledgment() {
    return rand() % 2 == 0;
}

// Function to simulate message transmission
void sendMessage(int message) {
    printf("Sending Message: %d\n", message);
}

// Function to simulate receiving acknowledgment
bool receiveAcknowledgment() {
    // Simulate acknowledgment loss
    if (shouldLoseAcknowledgment()) {
        printf("Acknowledgment Lost! Resending Message...\n");
        return false;
    } else {
        printf("Acknowledgment Received!\n");
        return true;
    }
}

int main() {
    srand((unsigned int)time(NULL));

    int message = 0;
    int expectedAck = 0;
    int framesSent = 0;

    while (framesSent < MAX_FRAMES) {
        // Send message
        sendMessage(message);

        // Wait for acknowledgment with timeout
        int timeout = 0;
        while (!receiveAcknowledgment()) {
            sleep(1);
            timeout++;
            if (timeout == TIMEOUT) {
                printf("Timeout! Resending Message: %d\n", message);
                continue;
            }
        }

        // Move to the next message
        message++;
        expectedAck++;
        framesSent++;
    }

    return 0;
}