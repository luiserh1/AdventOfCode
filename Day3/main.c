#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NORTH_CHARACTER '^'
#define SOUTH_CHARACTER 'v'
#define WEST_CHARACTER '<'
#define EAST_CHARACTER '>'

#define INPUT_DATA_CHARACTERS_NUM 8193
#define INPUT_DATA_FILENAME "./data.txt"

typedef struct {
	int x, y; 
} Cords;

typedef struct {
	Cords pos;
	Cords *path;

	// Computable stats
	Cords mostDelivered;
	uint32_t mostDeliveries;
	uint32_t numDeliveredHouses;
} SantaClaus;

// Assuming minCoords and maxCoords are initiallized to { .x=0, .y=0 }
void fillPath(SantaClaus *santa, const char *pathStr, Cords *minCoords, Cords *maxCoords) {
	int i = 0;
	while (pathStr[i] != '\0') {
		switch (pathStr[i]) {
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

// Part1. Returns the amount of times the most delivered house is reached
void computeSantaStats(SantaClaus *santa, int numMoves, Cords minCoords,	Cords maxCoords) {
	int neightbourhoodWidth = maxCoords.x - minCoords.x + 1;
	int neightbourhoodHeight = maxCoords.y - minCoords.y + 1;

	int xOffset = -minCoords.x;
	int yOffset = -minCoords.y;

	// Row major
	uint32_t *neightbourhoodGrid = calloc(neightbourhoodWidth * neightbourhoodHeight, sizeof(uint32_t));

	// Initial house has the delivery count set to 1
	neightbourhoodGrid[xOffset * neightbourhoodWidth + yOffset] += 1;
	for (int i = 0; i < numMoves; i++) {
		int x = santa->path[i].x + xOffset;
		int y = santa->path[i].y + yOffset;
		neightbourhoodGrid[x * neightbourhoodWidth + y]++;
	}

	santa->mostDeliveries = 0;
	santa->numDeliveredHouses = 0;
	for (int i = 0; i < neightbourhoodWidth; i++) {
		for (int j = 0; j < neightbourhoodHeight; j++) {
			uint32_t presentsDelivered = neightbourhoodGrid[i * neightbourhoodWidth + j];
			if (!presentsDelivered)
				continue;

			santa->numDeliveredHouses++;
			if (presentsDelivered > santa->mostDeliveries) {
				santa->mostDeliveries = presentsDelivered;
				santa->mostDelivered.x = i;
				santa->mostDelivered.y = j;
			}
		}
	}

	// Debug printing the matrix
	//for (int i = 0; i < neightbourhoodWidth; i++) {
	//	for (int j = 0; j < neightbourhoodHeight; j++) {
	//		printf(" %d", neightbourhoodGrid[i * neightbourhoodWidth + j]);
	//	}
	//	printf("\n");
	//}

	free(neightbourhoodGrid);
}

int main()
{
	int numMoves = INPUT_DATA_CHARACTERS_NUM;
	//int numMoves = 4;
	//const char *pathStr = "^>v<";
	SantaClaus santa = { .pos = { .x = 0, .y = 0 }, .mostDeliveries = 0,
		                 .mostDelivered = { .x = 0, .y = 0 }, .numDeliveredHouses = 0 };
	santa.path = calloc(INPUT_DATA_CHARACTERS_NUM, sizeof(Cords));

	FILE* fp = fopen(INPUT_DATA_FILENAME, "r");
    if (!fp) {
        perror("File opening failed");
        free(santa.path);
        return -1;
    }
	char pathStr[INPUT_DATA_CHARACTERS_NUM + 1];
    if (!fgets(pathStr, INPUT_DATA_CHARACTERS_NUM+1, fp)) {
        perror("File reading failed");
        free(santa.path);
        fclose(fp);
        return -2;
    }
    fclose(fp);

	Cords minCoords = { .x = 0, .y = 0 };
	Cords maxCoords = { .x = 0, .y = 0 };
	fillPath(&santa, pathStr, &minCoords, &maxCoords);
	computeSantaStats(&santa, numMoves, minCoords, maxCoords);
	printf("After %d moves presents have been delivered to %d houses and the house with the most"
		   " deliveries is at [%d, %d] with %d deliveries\n",
		   numMoves, santa.numDeliveredHouses, santa.mostDelivered.x, santa.mostDelivered.y, santa.mostDeliveries);
    
    free(santa.path);
	return 0;
}
