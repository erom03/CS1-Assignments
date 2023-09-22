#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 20

typedef struct Boat {
    long long int dotProduct;   // Dot product of boat and main vector
    long long int distSquared;  // Distance to broken ship squared

    char name[NAME_SIZE + 1];

    int valid;  // Whether or not boat will help
} Boat;

void mergeSort(Boat * boats, int numBoats);
Boat * merge(Boat * first, int firstSize, Boat * second, int secondSize);
void printInfo(Boat * boats, int numBoats);
void compare(Boat * boats, int numBoats);

int main() {
    // keeps track of ships position
    long long int shipX;
    long long int shipY;

    // keeps track of harbors position
    long long int harborX;
    long long int harborY;

    // scan in values
    scanf("%lld %lld %lld %lld", &shipX, &shipY, &harborX, &harborY);

    // Normalize harbor location according to ship location and set to main vector
    long long int mainVecX;
    long long int mainVecY;
    mainVecX = harborX - shipX;
    mainVecY = harborY - shipY;

    // Create a dot product using main vector
    // Tells us the max dot product before a
    // ship is no longer useful to us
    long long int mainDotProduct;
    mainDotProduct = mainVecX * mainVecX + mainVecY * mainVecY;

    // Get the number of boats
    int numBoats;
    scanf("%d", &numBoats);

    // Create an array of Boats
    Boat * boats = (Boat *)malloc(numBoats * sizeof(Boat));

    // Get information for each boat
    for(int i = 0; i < numBoats; i++) {
        // Track boat position
        long long int boatX;
        long long int boatY;

        // Read in boats position
        scanf("%lld %lld %s", &boatX, &boatY, boats[i].name);

        // Find boats vector
        long long int boatVecX;
        long long int boatVecY;
        boatVecX = boatX - shipX;
        boatVecY = boatY - shipY;
        
        // Get boats dot product
        boats[i].dotProduct = mainVecX * boatVecX + mainVecY * boatVecY;

        // Get boats distance to ship squared
        boats[i].distSquared = boatVecX * boatVecX + boatVecY * boatVecY;

        // Check if boat dot product is still valid
        if(boats[i].dotProduct > 0 && boats[i].dotProduct <= mainDotProduct)
            boats[i].valid = 1;
        else
            boats[i].valid = 0;
    }

    // Sort the boats by dot product
    mergeSort(boats, numBoats);

    // Compare the boats
    compare(boats, numBoats);

    // Print neccessary info
    printInfo(boats, numBoats);

    // Free our dynamic array
    free(boats);
    
    return 0;
}

void mergeSort(Boat * boats, int numBoats) {
    if (numBoats <= 1) return;
    // Getting the sizes of the two halves
    int sizeLeft = numBoats / 2;
    int sizeRight = numBoats - sizeLeft;
    // Get the pointers into the two halves
    Boat * leftArr = boats;
    Boat * rightArr = &boats[sizeLeft];
    // Sort the left side
    mergeSort(leftArr, sizeLeft);
    // Sort the right side
    mergeSort(rightArr, sizeRight);
    Boat * result = merge(leftArr, sizeLeft, 
                         rightArr, sizeRight);
    // Copy result into arr
    for (int i = 0; i < numBoats; i++)
        boats[i] = result[i];
    
    // Clean up the memory from result
    free(result);
}

Boat * merge(Boat * first, int firstSize, Boat * second, int secondSize) {
    int total = firstSize + secondSize;
    Boat * result = (Boat *) calloc(total, sizeof(Boat));
    
    int firstPtr = 0;
    int secondPtr = 0;
    for (int i = 0; i < total; i++) {
        if (firstPtr == firstSize) {
            // Empty first array
            result[i] = second[secondPtr];
            secondPtr++;
        } else if (secondPtr == secondSize) {
            // Empty second array
            result[i] = first[firstPtr];
            firstPtr++;
        } else if (first[firstPtr].dotProduct < second[secondPtr].dotProduct) {
            // First is smaller
            result[i] = first[firstPtr];
            firstPtr++;
        } else {
            // Second was equal or smaller
            result[i] = second[secondPtr];
            secondPtr++;
        }
    }   
    
    return result;
}

void compare(Boat * boats, int numBoats) {
    // Compare the boats to evaluate
    // which boat should be used if
    // two have the same dot product
    for(int i = 0; i < numBoats - 1; i++) {       
        // Check following ships
        for(int j = i + 1; j < numBoats; j++) {
            // Check if current boat is valid
            if(boats[i].valid == 0)
                break;   // Don't bother checking if it isnt

            // Check if following ship is valid
            if(boats[j].valid == 0)
                continue;   // Don't bother checking if it isnt

            // Check if dot products are not the same
            if(boats[i].dotProduct != boats[j].dotProduct)
                break;  // If they arent equal, because list is sorted, we can skip the current boat
            
            // By here we know both boats are valid
            // and that they have the same dot product
            // so we can go ahead and
            // Compare distances
            if(boats[i].distSquared < boats[j].distSquared) // Current boat is closer than following boat
                boats[j].valid = 0;
            else if(boats[i].distSquared > boats[j].distSquared) // Current boat is further than following boat
                boats[i].valid = 0;
            else {  // Boats have same distance squared, so compare names
                if(strcmp(boats[i].name, boats[j].name) < 0)    // Current boat comes first lexigraphically
                    boats[j].valid = 0;
                else    // Subsequent boat comes first lexigraphically
                    boats[i].valid = 0;
            }
        }
    }
}

// Because list should be sorted by the time it reaches here
// No need to check if boats are being printed in the correct order
void printInfo(Boat * boats, int numBoats) {
    // Keeps track of number of valid boats
    int validBoats = 0;
    
    // Count how many boats are valid
    for(int i = 0; i < numBoats; i++) {
        if(boats[i].valid == 1)
            validBoats++;
    }

    // Print how many boats are valid
    printf("%d\n", validBoats);

    // Print out boats that are valid
    for(int i = 0; i < numBoats; i++) {
        if(boats[i].valid == 1)
            printf("%s\n", boats[i].name);
    }
}