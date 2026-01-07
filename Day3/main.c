#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NORTH_CHARACTER '^'
#define SOUTH_CHARACTER 'v'
#define WEST_CHARACTER '<'
#define EAST_CHARACTER '>'

#define INPUT_DATA_CHARACTERS_NUM 8193
#define NUM_SANTAS 2
#define INPUT_DATA_FILENAME "./data.txt"

typedef struct {
	int x, y; 
} Cords;

typedef struct {
	Cords pos;
	char  *pathStr;
	Cords *path;
} SantaClaus;

typedef struct {
	// To be filled from SantasClaus path
	uint32_t *deliveriesGrid;

	// To be computed from deliveriesGrid
	int width, height;
	int xOffset, yOffset;
	Cords mostDelivered;
	uint32_t mostDeliveries;
	uint32_t numDeliveredHouses;
} Neightbourhood;

void parsePath(SantaClaus *santa, Cords *minCoords, Cords *maxCoords) {
	int i = 0;
	while (santa->pathStr[i] != '\0') {
		switch (santa->pathStr[i]) {
		case NORTH_CHARACTER:
			santa->pos.y++;
			if (santa->pos.y > maxCoords->y)
				maxCoords->y = santa->pos.y;
			break;
		case SOUTH_CHARACTER:
			santa->pos.y--;
			if (santa->pos.y < minCoords->y)
				minCoords->y = santa->pos.y;
			break;
		case EAST_CHARACTER:
			santa->pos.x--;
			if (santa->pos.x < minCoords->x)
				minCoords->x = santa->pos.x;
			break;
		case WEST_CHARACTER:
			santa->pos.x++;
			if (santa->pos.x > maxCoords->x)
				maxCoords->x = santa->pos.x;
			break;
		default:
			perror("Unexpected character!\n");
			break;
		}
		santa->path[i] = santa->pos;
		i++;
	}
}

void delimitNeightbourhoodArea(Neightbourhood *hood, Cords minCoords, Cords maxCoords) {
	hood->width = maxCoords.x - minCoords.x + 1;
	hood->height = maxCoords.y - minCoords.y + 1;

	hood->xOffset = -minCoords.x;
	hood->yOffset = -minCoords.y;

	hood->deliveriesGrid = calloc(hood->width * hood->height, sizeof(uint32_t));
}

void traverseNeightbourhood(Neightbourhood *hood, Cords *path, int numMoves) {
	// Starting house has the delivery count increased by 1
	hood->deliveriesGrid[hood->xOffset * hood->width + hood->yOffset] += 1;
	for (int i = 0; i < numMoves; i++) {
		int x = path[i].x + hood->xOffset;
		int y = path[i].y + hood->yOffset;
		hood->deliveriesGrid[x * hood->width + y]++;
	}
}

void computeNeightbourhoodStats(Neightbourhood *hood) {
	hood->mostDeliveries = 0;
	hood->numDeliveredHouses = 0;

	for (int i = 0; i < hood->width; i++) {
		for (int j = 0; j < hood->height; j++) {
			uint32_t presentsDelivered = hood->deliveriesGrid[i * hood->width + j];
			if (!presentsDelivered)
				continue;

			hood->numDeliveredHouses++;
			if (presentsDelivered > hood->mostDeliveries) {
				hood->mostDeliveries = presentsDelivered;
				hood->mostDelivered.x = i;
				hood->mostDelivered.y = j;
			}
		}
	}
}

int main()
{
	// Init
	SantaClaus santaArmy[NUM_SANTAS];
	int movesPerSanta = INPUT_DATA_CHARACTERS_NUM / NUM_SANTAS;
	for (int i = 0; i < NUM_SANTAS; i++) {
		santaArmy[i].pos = (Cords){ .x=0, .y=0 };
		santaArmy[i].path = calloc(movesPerSanta, sizeof(Cords));
		santaArmy[i].pathStr = calloc(movesPerSanta, sizeof(char));
	}
	Neightbourhood hood = { .width=0, .height=0, .xOffset=0, .yOffset=0,
		.mostDelivered={ .x=0, .y=0 }, .mostDeliveries=0, .numDeliveredHouses=0 };

	// Data file loading
	FILE* fp = fopen(INPUT_DATA_FILENAME, "r");
    if (!fp) {
        perror("File opening failed");
        return -1;
    }
    int santaIndex = 0;
    int pathIndex = 0;
    for (int i = 0; i < INPUT_DATA_CHARACTERS_NUM; i++) {
    	char pathChar = fgetc(fp);
    	if (pathChar == EOF) {
       		break;
    	}
    	santaArmy[santaIndex].pathStr[pathIndex] = pathChar;

    	santaIndex++;
    	if(santaIndex == NUM_SANTAS) {
    		santaIndex = 0;
    		pathIndex++;
    	}
    }
    fclose(fp);

    // Data parsing
	Cords minCoords = { .x = 0, .y = 0 };
	Cords maxCoords = { .x = 0, .y = 0 };
	for (int i = 0; i < NUM_SANTAS; i++) {
		parsePath(&santaArmy[i], &minCoords, &maxCoords);
	}

	// Traversing
	delimitNeightbourhoodArea(&hood, minCoords, maxCoords);
	for (int i = 0; i < NUM_SANTAS; i++) {
		traverseNeightbourhood(&hood, santaArmy[i].path, movesPerSanta);
	}

	// Computing result
	computeNeightbourhoodStats(&hood);

	// Pint result
	printf("After %d moves by %d Santas presents have been delivered to %d houses and the house with the most"
		   " deliveries is at [%d, %d] with %d deliveries\n",
		   movesPerSanta, NUM_SANTAS, hood.numDeliveredHouses, hood.mostDelivered.x,
		   hood.mostDelivered.y, hood.mostDeliveries);
    
    // Clean up
	for (int i = 0; i < NUM_SANTAS; i++) {
    	free(santaArmy[i].path);
    	free(santaArmy[i].pathStr);
	}
	free(hood.deliveriesGrid);
	return 0;
}
