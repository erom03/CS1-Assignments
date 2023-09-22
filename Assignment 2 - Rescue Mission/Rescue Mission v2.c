// This is my second attempt at the problem
// Rather than calculating the middle of
// Speed rows and starting columns that contain a 1
// I count all "ones", split them in half, then find
// the "one" that is that half and evaluate from there

#include <stdio.h>
#include <string.h>

#define MAX_LEN 7
#define MAX_LOOP 24

int main() {
    // keeps track of current values im checking
    // or that im printing
    int currStart, currSpeed, currPrint;

    // used to handle user input
    int maxSpeed, maxStart;

    // used when couting how many valid
    // ships there are by counting how many
    // 1's are in the array
    int onesCenter, onesCount, centerCount;
    int leave;

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

    // Get intial middle values
    currSpeed = maxSpeed / 2;
    currStart = maxStart / 2;

    // set first scan location to location
    // of the boat in the middle
    currPrint = currStart + currSpeed;

    // Request first scan and 
    // start by checking the middle
    printf("? %d\n", currPrint);
    fflush(stdout);

    // loop through the rest of the 23 possible hours to check
    // starts at 2 as we already scanned day 1
    for(int k = 2; k <= MAX_LOOP; k++) {
        char response[MAX_LEN + 2];
        fgets(response, MAX_LEN + 2, stdin);

        // If ship has passed
        // Eliminate all combinations that would
        // yield same results
        if(strcmp(response, "Wake\n") == 0) {
            // Makes all values equal or below
            // the scan 0
            for(int i = 0; i <= maxSpeed; i++) {
                for(int j = 0; j <= maxStart; j++) {
                    if(j + (i * (k - 1)) <= currPrint) {
                        positions[i][j] = 0;
                    }
                }
            }
        }

        // If ship has NOT passed
        // Eliminate all combinations that would
        // yield same results
        if(strcmp(response, "No Wake\n") == 0) {
            // Makes all values equal or above
            // the scan 0
            for(int i = 0; i <= maxSpeed; i++) {
                for(int j = 0; j <= maxStart; j++) {
                    if(j + (i * (k - 1)) >= currPrint) {
                        positions[i][j] = 0;
                    }
                }
            }
        }

        // If Boat is spotted
        // Eliminate all combinations that would
        // NOT yield same results
        if(strcmp(response, "Boat!\n") == 0) {
            for(int i = 0; i <= maxSpeed; i++) {
                for(int j = 0; j <= maxStart; j++) {
                    if(j + (i * (k - 1)) != currPrint) {
                        positions[i][j] = 0;
                    }
                }
            }
        }
        
        onesCount = 0;
        centerCount = 0;
        leave = 0;

        // count how many boats are still 
        // in possible locations
        for(int i = 0; i <= maxSpeed; i++) {
            for(int j = 0; j <= maxStart; j++) {
                if(positions[i][j] == 1)
                    ++onesCount;
            }
        }

        // Gets the median from onesCount
        // this makes sure that there is no 0 count 
        // as 1 / 2 would return 0 otherwise
        if(onesCount % 2 == 1)
            onesCenter = (onesCount / 2) + 1;
        else
            onesCenter = onesCount / 2;

        // counts through the ones until the median is reached
        for(int i = 0; i <= maxSpeed; i++) {
            for(int j = 0; j <= maxStart; j++) {
                if(positions[i][j] == 1) {
                    ++centerCount;

                    // Once median is reached,
                    // save index and exit loop
                    if(centerCount == onesCenter) {
                        currSpeed = i;
                        currStart = j;
                        leave = 1;
                        break;
                    }
                }
            }

            // checks if loop should be exited
            if(leave == 1)
                break;
        }

        // calculate current location of ship were printing
        currPrint = currStart + (currSpeed * k);

        // if only one ship was detected, print answer
        if(onesCount == 1) {
            printf("! %d\n", currPrint);
            fflush(stdout);

            // Leave the loop to exit the program
            break;
        } else {
            // if more than one ship was detected,
            // ask to scan current ship
            printf("? %d\n", currPrint);
            fflush(stdout);
        }
    }

    return 0;
}