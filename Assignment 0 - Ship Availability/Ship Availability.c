#include <stdio.h>

#define MAX_LINE_NUMBER 100
#define MAX_SHIPS_PER_LINE 100
#define MAX_NAME_LENGTH 20

void GetShips(int lineNum, char names[MAX_LINE_NUMBER][MAX_SHIPS_PER_LINE][MAX_NAME_LENGTH + 2], int shipsInLines[MAX_LINE_NUMBER]);
void CalcResults(int lines, char names[MAX_LINE_NUMBER][MAX_SHIPS_PER_LINE][MAX_NAME_LENGTH + 2], int shipsInLines[MAX_LINE_NUMBER]);

int main() 
{
    // Used to store the fleet
    char names[MAX_LINE_NUMBER][MAX_SHIPS_PER_LINE][MAX_NAME_LENGTH + 2];
    // Used to track how many ships in each line
    int shipsInLine[MAX_LINE_NUMBER];

    int customers;
    int lines;

    // Prompt user for how many lines of ships will be created
    scanf("%d", &lines);

    // Disposes the new line character
    getchar();

    // Loops for as many lines as there are to get the ship for each line
    // In this loop, I represents which number line is being inputted
    for(int i = 0; i < lines; ++i)
        GetShips(i, names, shipsInLine);

    // Prompt user for number of customers
    scanf("%d", &customers);

    // Loops for as many customers as there are
    // and calculates results for each one
    for(int i = 0; i < customers; ++i)
        CalcResults(lines, names, shipsInLine);

    return 0;
}

// Function in charge of gathering each line of ships
void GetShips(int lineNum, char names[MAX_LINE_NUMBER][MAX_SHIPS_PER_LINE][MAX_NAME_LENGTH + 2], int shipsInLine[MAX_LINE_NUMBER])
{
    char currChar = ' ';

    // Keeps track of current ship and how many ships there are in each line
    int shipNum = -1;   // -1 so its set to 0 on first loop

    // Will keep looping until new line is reached
    while(currChar != '\n')
    {
        // Increment which ship were on
        ++shipNum;

        // Get ship name
        scanf("%s", names[lineNum][shipNum]);

        // Grab next character (should be either space or newline)
        currChar = getchar();
    }

    // keeps track of how many ships in each line
    shipsInLine[lineNum] = shipNum;
}

void CalcResults(int lines, char names[MAX_LINE_NUMBER][MAX_SHIPS_PER_LINE][MAX_NAME_LENGTH + 2], int shipsInLine[MAX_LINE_NUMBER])
{
    int week;
    int currShip;

    // prompts user for which week they'd like
    scanf("%d", &week);

    // Dispose the new line character
    getchar();

    // Zero index week
    week -= 1;

    // scrolls through each line of ship and prints the one for the week
    for(int i = 0; i < lines; ++i) {
        currShip = week;

        // This will assign currShip with the remainder of itself divided by how many ships are in that line
        currShip %= shipsInLine[i] + 1;
        
        printf("%s ", names[i][currShip]);
    }

    printf("\n");
}