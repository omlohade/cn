#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// #define TIMEOUT 3

void sender(int frame);
void receiver(int expectedFrame);

int main() {
    int framesToSend = 5;

    printf("Stop-and-Wait Protocol Simulation\n");

    for (int i = 0; i < framesToSend; i++) {
        sender(i);
        receiver(i);
        // sleep(TIMEOUT); // Simulate the time taken for frame transmission
    }

    return 0;
}

void sender(int frame) {
    printf("Sender: Sending Frame %d\n", frame);
}

void receiver(int expectedFrame) {
    int receivedFrame;
    printf("Receiver: Waiting for Frame %d\n", expectedFrame);

    // Simulate receiving a frame
    // For simplicity, assume that frames are not lost or corrupted
    scanf("%d", &receivedFrame);

    if (receivedFrame == expectedFrame) {
        printf("Receiver: Received Frame %d successfully\n", receivedFrame);
        printf("Receiver: Acknowledging Frame %d\n", receivedFrame);
    } else {
        printf("Receiver: Received incorrect frame. Discarding.\n");
    }
}
