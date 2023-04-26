#include <stdio.h>
#include <cmath>
#include <stdlib.h> // included for rand() function
#include <time.h> //for time based rand()
#include <iostream> //for cin and printf
#include <cctype> // for toupper() function

using namespace std;

void printBiome(bool biome[10][10], bool chosenXY[10][10]);
void printCoordinates(bool biome[10][10], bool chosenXY[10][10]);
void beginSim(int camiPop, int pollPop, double camiPopMultiply, int numGenerations, bool printArray, bool printLocations);

int main()
{
    int camiPop = -1;
    int pollPop = -1;
    double camiPopMultiply = -1;
    int numGenerations = -1;
    bool printArray, printLocations = false;
    while((camiPop < 1) || (camiPop > 100))
    {
        printf("Enter starting Caminacule population (1-100): ");
        cin >> camiPop;
    }
    
    while((pollPop < 1) || (pollPop > 75))
    {
        printf("\nEnter starting Pollard population (1-75): ");
        cin >> pollPop;
    }
    
    while(camiPopMultiply < 0)
    {
        printf("\nEnter Caminacule Reproduction rate (1-10): ");
        cin >> camiPopMultiply;
    }
    
    while(numGenerations < 1)
    {
        printf("\nEnter the number of generations to simulate (1-100): ");
        cin >> numGenerations;
    }
    
    char userInput = 't';
    while(1)
    {
        printf("\nWould you like to display a population array after each generation (Y/N): ");
        cin >> userInput;
        userInput = toupper(userInput);
        if(userInput == 'Y')
        {
            printArray = true;
            break;
        }
        else if(userInput == 'N') break;
    }
    
        while(1)
    {
        printf("\nWould you like to display the coordinates for the Caminacules and Pollards each generation (Y/N): ");
        cin >> userInput;
        userInput = toupper(userInput);
        if(userInput == 'Y')
        {
            printLocations = true;
            break;
        }
        else if(userInput == 'N') break;
    }

    srand(time(NULL)); //Randomness based on system time
    beginSim(camiPop, pollPop, camiPopMultiply, numGenerations, printArray, printLocations);
    
    return 0;
}

void printBiome(bool biome[10][10], bool chosenXY[10][10]) {
    printf("Printing location array of Caminacule locations, 1 = occupied, 0 = unoccupied, X = found\n");
    printf("   A B C D E F G H I J\n");
    for (int i = 0; i < 10; i++) {
        if(i != 9) printf(" %d ", i+1);
        else printf("%d ", i+1);
        for (int j = 0; j < 10; j++) {
            if (biome[i][j] && !chosenXY[i][j]) {
                printf("1 ");
            } 
            else if(biome[i][j] && chosenXY[i][j])
            {
                printf("X ");
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}


void printCoordinates(bool biome[10][10], bool chosenXY[10][10]) {
    printf("Printing location coordinates of Caminacule locations(x,y)\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (biome[i][j]) {
                if(i != 9 && j != 9) printf("(%c,%d)",(i+65),j);
                else  printf("(%c,%d)",(i+65),j);
            } 
        }
    }
    
    printf("\nPrinting location coordinates of Pollard locations(x,y)\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (chosenXY[i][j]) {
                if(i != 9 && j != 9) printf("(%c,%d)",(i+65),j);
                else  printf("(%c,%d)",(i+65),j);
            } 
        }
    }
    printf("\n");
}

void beginSim(int camiPop, int pollPop, double camiPopMultiply, int numGenerations, bool printArray, bool printLocations)
{
    printf("Gen: 0 Starting Caminacule Pop: %d Starting Pollard Pop: %d\n", camiPop, pollPop);
    //For each generation 1-numGenerations
    for (int index = 0; index < numGenerations; index++)
    {
        int found = 0;
        bool biome[10][10] = {false}; // Initialize biome array to all false values

        //For each camincacule choose location
        for (int cami = 0; cami < camiPop; cami++)
        {
            int x = rand() % 10; // generate random index from 0 to 9
            int y = rand() % 10;

            //If the spot is not occupied
            if (!biome[x][y])
            {
                //Set it to occupied
                biome[x][y] = true;
            }
            //else the spot was occupied, find a different spot
            else
            {
                // Find a new location if the initial one is already occupied
                while (biome[x][y])
                {
                    x = rand() % 10;
                    y = rand() % 10;
                }
                biome[x][y] = true;
            }
        }

        bool chosenXY[10][10] = {false};
        //For each pollard choose location
        for (int polly = 0; polly < pollPop; polly++)
        {
            int x = rand() % 10;
            int y = rand() % 10;
            //If Camincacule is there and it hasnt been found before
            while(chosenXY[x][y])
            {
                x = rand() % 10;
                y = rand() % 10;
            }
            if (biome[x][y] && !chosenXY[x][y])
            {
                //Found cami
                camiPop = camiPop-1;
                found++;
                chosenXY[x][y] = true;
            }
            else
            {
                chosenXY[x][y] = true;
            }
        }
        
        //Need to update populations
        camiPop = camiPop * camiPopMultiply;
        if (camiPop < 1)
            camiPop = 1;
        if (camiPop > 100)
            camiPop = 100;
            
        double lostPop = floor(pollPop / 3);
        pollPop -= lostPop;
        pollPop += found+1;
        
        if (pollPop > 75)
            pollPop = 75;
        if (pollPop < 1)
            pollPop = 1;
        
        printf("Gen: %d Ending Caminacule Pop: %d Ending Pollard Pop: %d || found: %d\n", index+1, camiPop, pollPop, found);
        if(printArray) printBiome(biome, chosenXY);
        if(printLocations) printCoordinates(biome, chosenXY);
    }  
}
