// This was my original attempt at the problem
// I realized it was only effective at finding
// values at the corners since it simply checked diagonals
// v2 contains my second attempt

#include <stdio.h>
#include <string.h>

#define MAX_LEN 7
#define MAX_LOOP 24

int GetMid(int low, int high);

int main() {
    // keeps track of low, high, and current values
    int lowSpeed, highSpeed, currSpeed;
    int lowStart, highStart, currStart;
    int maxSpeed, maxStart, currPrint;

    // Get max speed and starting point from user
    scanf("%d %d", &maxSpeed, &maxStart);
    getchar();  // Removes problematic newline character

    // Create array of possible locations, mark each as currently possible
    int positions[maxSpeed + 1][maxStart + 1];
    for(int i = 0; i <= maxSpeed; i++) {
        for(int j = 0; j <= maxStart; j++) {
            positions[i][j] = 1;
        }
    }

    // get value of high and low
    highSpeed = maxSpeed;
    lowSpeed = 0;

    highStart = maxStart;
    lowStart = 0;

    // Get intial values
    currSpeed = GetMid(lowSpeed, highSpeed);
    currStart = GetMid(lowStart, highStart);
    currPrint = currStart + currSpeed;

    // Request first scan and 
    // start by checking the middle
    printf("? %d\n", currPrint);
    fflush(stdout);

    for(int k = 2; k <= MAX_LOOP; k++) {
        char response[MAX_LEN + 2];
        fgets(response, MAX_LEN + 2, stdin);
        printf("%s", response);
        fflush(stdout);

        // If ship has passed
        if(strcmp(response, "Wake\n") == 0) {
            // Eliminate all combinations that would
            // yield same results
            for(int i = 0; i <= maxSpeed; i++) {
                for(int j = 0; j <= maxStart; j++) {
                    if(i + j <= currSpeed + currStart) {
                        positions[i][j] = 0;
                    }
                }
            }

            // Find the current lowest values
            int leave = 0;  // Marks whether or not to leave loop

            // Gets initial low values
            for(int i = 0; i <= maxSpeed; i++) {
                for(int j = 0; j <= maxStart; j++) {
                    if(positions[i][j] == 1) {
                        lowSpeed = i;
                        lowStart = j;
                        leave = 1;  // Tell loop to fully exit
                        break;
                    }
                }
                
                if(leave == 1)
                    break;
            }

            // Find the current highest values
            for(int i = maxSpeed; i >=0; i--) {
                for(int j = maxStart; j >= 0; j--) {
                    if(positions[i][j] == 1 && j > highStart) {
                        highStart = j;
                    }

                    if(positions[i][j] == 1 && i > highSpeed) {
                        highSpeed = i;
                    }
                }
            }

            // Get current mid points were checking
            currSpeed = GetMid(lowSpeed, highSpeed);
            currStart = GetMid(lowStart, highStart);

            currPrint = currStart + (currSpeed * k);

            for(int i = 0; i <= maxSpeed; i++) {
                for(int j = 0; j <= maxStart; j++) {
                    printf("%d ", positions[i][j]);
                    fflush(stdout);
                }
                printf("\n");
                fflush(stdout);
            }
            printf("currSpeed: %d\ncurrStart: %d\n", currSpeed, currStart);
            fflush(stdout);

            // Prints answer
            printf("? %d\n", currPrint);
            fflush(stdout);
        }

        // If ship has NOT passed
        if(strcmp(response, "No Wake\n") == 0) {
            fflush(stdout);
            for(int i = 0; i <= maxSpeed; i++) {
                for(int j = 0; j <= maxStart; j++) {
                    if(i + j >= currSpeed + currStart) {
                        positions[i][j] = 0;
                    }
                }
            }

            // Find the current lowest values
            int leave = 0;  // Marks whether or not to leave loop

            for(int i = 0; i <= maxSpeed; i++) {
                for(int j = 0; j <= maxStart; j++) {
                    if(positions[i][j] == 1) {
                        lowSpeed = i;
                        lowStart = j;
                        leave = 1;  // Tell loop to fully exit
                        break;
                    }
                }
                
                if(leave == 1)
                    break;
            }

            // Find the current highest values
            for(int i = maxSpeed; i >=0; i--) {
                for(int j = maxStart; j >= 0; j--) {
                    if(positions[i][j] == 1 && j > highStart) {
                        highStart = j;
                    }

                    if(positions[i][j] == 1 && i > highSpeed) {
                        highSpeed = i;
                    }
                }
            }

            // Get current mid points were checking
            currSpeed = GetMid(lowSpeed, highSpeed);
            currStart = GetMid(lowStart, highStart);

            currPrint = currStart + (currSpeed * k);

            for(int i = 0; i <= maxSpeed; i++) {
                for(int j = 0; j <= maxStart; j++) {
                    printf("%d ", positions[i][j]);
                    fflush(stdout);
                }
                printf("\n");
                fflush(stdout);
            }
            printf("currSpeed: %d\ncurrStart: %d\n", currSpeed, currStart);
            fflush(stdout);

            printf("? %d\n", currPrint);
            fflush(stdout);
        }

        // If Boat is spotted
        if(strcmp(response, "Boat!\n") == 0) {
            currPrint = currStart + (currSpeed * k);

            printf("! %d\n", currPrint);
            fflush(stdout);

            break;
        }
    }

    return 0;
}

int GetMid(int low, int high) {
    int mid;
    mid = (low + high) / 2;

    return mid;
}