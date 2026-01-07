#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NORTH_CHARACTER '^'
#define SOUTH_CHARACTER 'v'
#define WEST_CHARACTER '<'
#define EAST_CHARACTER '>'

#define NUM_MOVES 8193

typedef struct {
	int x, y; 
} Cords;

typedef struct {
	Cords pos;
	Cords path[NUM_MOVES];
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

// Part1. Returns the amount of times the most visited house is reached
uint32_t getMostVisitedHouse(Cords *path, int numMoves, Cords minCoords,
	Cords maxCoords, Cords *mostVisited)
{
	int neightbourhoodWidth = maxCoords.x - minCoords.x + 1;
	int neightbourhoodHeight = maxCoords.y - minCoords.y + 1;

	int xOffset = -minCoords.x;
	int yOffset = -minCoords.y;

	// Row major
	uint32_t *neightbourhoodGrid = calloc(neightbourhoodWidth * neightbourhoodHeight, sizeof(uint32_t));

	// Initial house has the visits count set to 1
	neightbourhoodGrid[xOffset * neightbourhoodWidth + yOffset] += 1;
	for (int i = 0; i < numMoves; i++) {
		int x = path[i].x + xOffset;
		int y = path[i].y + yOffset;
		neightbourhoodGrid[x * neightbourhoodWidth + y] += 1;
	}

	uint32_t mostVisits = 0;
	for (int i = 0; i < neightbourhoodWidth; i++) {
		for (int j = 0; j < neightbourhoodWidth; j++) {
			if (neightbourhoodGrid[i * neightbourhoodWidth + j] > mostVisits) {
				mostVisits = neightbourhoodGrid[i * neightbourhoodWidth + j];
				mostVisited->x = i;
				mostVisited->y = j;
			}
		}
	}

	// Debug printing the matrix
	for (int i = 0; i < neightbourhoodWidth; i++) {
		for (int j = 0; j < neightbourhoodWidth; j++) {
			printf(" %d", neightbourhoodGrid[i * neightbourhoodWidth + j]);
		}
		printf("\n");
	}


	free(neightbourhoodGrid);
	return mostVisits;
}

int main()
{
	SantaClaus santa = { .pos = { .x = 0, .y = 0 } };
	Cords minCoords = { .x = 0, .y = 0 };
	Cords maxCoords = { .x = 0, .y = 0 };
	const char *pathStr = "^>v<";
	fillPath(&santa, pathStr, &minCoords, &maxCoords);
	Cords mostVisited;
	uint32_t mostVisites = getMostVisitedHouse(&santa.path, 4, minCoords, maxCoords, &mostVisited);
	printf("Most visited house at [%d, %d] with %d visites\n", mostVisited.x, mostVisited.y, mostVisites);
	return 0;
}
