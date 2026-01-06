#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <time.h>

/*
* NOTE: The algorithm for the part 2 works under the assumption that the basement is eventually reached
*/
#define INPUT_DATA_CHARACTERS_NUM 7000
#define INPUT_DATA_FILENAME "./data.txt"

const char MOVING_UP_CHAR   = '(';
const char MOVING_DOWN_CHAR = ')';

const int INIT_FLOOR = 0;
const int BASEMENT   = -1;

static inline int moveFloor(int currentFloor, char moveCode) {
    if (moveCode == MOVING_UP_CHAR)
        return currentFloor + 1;
    else // if (moveCode == MOVING_DOWN_CHAR)
        return currentFloor - 1;
}

int solvePart1(const char *moves, int numMoves) {
    int current = INIT_FLOOR;
    for (int i = 0; i < numMoves; i++)
       current = moveFloor(current, moves[i]);
    return current;
}

int solvePart2(const char *moves, int numMoves) {
    int current = INIT_FLOOR;
    int movesTaken = 1;
    for (int i = 0; i < numMoves; i++, movesTaken++) {
        current = moveFloor(current, moves[i]);
        if (current == BASEMENT)
            break;
    }

    return movesTaken;
}

void solveBothParts(const char *moves, int numMoves, int *finalFloor, int *movesToReachBasement) {
    int current = INIT_FLOOR;
    int movesTaken = 0;
    int i = 0;
    for (; i < numMoves; i++) {
        movesTaken++;
        current = moveFloor(current, moves[i]);
        if (current == BASEMENT)
            break;
    }
    *movesToReachBasement = movesTaken;
    i++;
    for (; i < numMoves; i++)
        current = moveFloor(current, moves[i]);
    *finalFloor = current;
}

int main()
{
    clock_t startTimePart1, endTimePart1,
            startTimePart2, endTimePart2,
            startTimeBothParts, endTimeBothParts;
    double elapsedTimePart1, elapsedTimePart2, elapsedTimeBothParts;
    
    char inputData[INPUT_DATA_CHARACTERS_NUM+1];

    FILE* fp = fopen(INPUT_DATA_FILENAME, "r");
    if (!fp) {
        perror("File opening failed");
        return -1;
    }
    if (!fgets(inputData, INPUT_DATA_CHARACTERS_NUM+1, fp)) {
        perror("File reading failed");
        fclose(fp);
        return -2;
    }
    fclose(fp);

    int numMoves = strlen(inputData);
    int finalFloor1, movesToReachBasement1;
    int finalFloor2, movesToReachBasement2;


    startTimePart1 = clock();
    finalFloor1 = solvePart1(inputData, numMoves);
    endTimePart1 = clock();

    startTimePart2 = clock();
    movesToReachBasement1 = solvePart2(inputData, numMoves);
    endTimePart2 = clock();

    startTimeBothParts = clock();
    solveBothParts(inputData, numMoves, &finalFloor2, &movesToReachBasement2);
    endTimeBothParts = clock();
    assert(finalFloor1 == finalFloor2);
    assert(movesToReachBasement1 == movesToReachBasement2);

    printf("After %d moves the floor Santa Claus arrives to is: %d\n", 
        numMoves, finalFloor1);
    printf("The position of the character that causes Santa to first enter the basement is: %d\n",
        movesToReachBasement1);

    printf("================================================================================\n");
    
    elapsedTimePart1 = (double)(endTimePart1 - startTimePart1) / CLOCKS_PER_SEC;
    elapsedTimePart2 = (double)(endTimePart2 - startTimePart2) / CLOCKS_PER_SEC;
    elapsedTimeBothParts = (double)(endTimeBothParts - startTimeBothParts) / CLOCKS_PER_SEC;
    printf("Time spent solving part1 individually is: %f\n", elapsedTimePart1);
    printf("Time spent solving part2 individually is: %f\n", elapsedTimePart2);
    printf("Time spent solving both parts separately is: %f\n", elapsedTimePart1 + elapsedTimePart2);
    printf("Time spent solving both parts simultaniously is: %f\n", elapsedTimeBothParts);

    return 0;
}
    