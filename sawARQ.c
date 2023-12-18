#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TIMEOUT 5

bool isAckLost() {
    return rand() % 100 < 20;
}

bool receiveAck() {
    if (isAckLost()) {
        printf("Acknowledgment Lost\n");
        return false;
    } else {
        printf("Acknowledgment Received\n");
        return true;
    }
}

void sendData(int frame) {
    printf("Sending Frame %d\n", frame);
}


void stopAndWait(int numFrames) {
    for (int frame = 0; frame < numFrames; ) {
        sendData(frame);

       
        if (receiveAck()) {
            frame++;
        }
        else{
            printf("TIMEOUTRESEND FRAME\n");
        }
       
    }
}

int main() {
    srand(42);

    int numFrames;
    printf("Enter the number of frames to be transmitted: ");
    scanf("%d", &numFrames);

    stopAndWait(numFrames);
    return 0;
}