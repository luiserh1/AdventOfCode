#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define MAX_CHARS_LINE 64

#define TURN_ON_TEXT "turn on"
#define TURN_OFF_TEXT "turn off"
#define TOGGLE_TEXT "toggle"
#define COORD_SEPARATOR ','
#define TOKEN_SEPARATOR ' '
#define POINT_SEPARATOR " through "

typedef enum {
	TURN_OFF = 0,
	TURN_ON = 1,
	TOGGLE = 2
} ACTIONS;

typedef struct {
	uint32_t minX, minY, maxX, maxY;
} Range;

typedef struct {
	ACTIONS act;
	Range range;
} Instruction;

typedef uint8_t LightsGrid[125000]; // Storing the state of the lights in one bit

// static inline bool toggle_lights(LightsGrid* lights, const Range* range) {
// 	return false;
// }

// static inline bool set_lights(LightsGrid* lights, const Range* range, bool on) {
// 	return false;
// }

// bool modify_grid(LightsGrid* lights, const Instruction* inst) {
// 	return false;
// }

/*
*	The expected format for each line is:
*	[TURN_ON_TEXT/TURN_OFF_TEXT/TOGGLE_TEXT] + TOKEN_SEPARATOR + x_min +
*	COORD_SEPARATOR + y_min + POINT_SEPARATOR + x_max + COORD_SEPARATOR + y_max
*/
bool parse_input_file(FILE* fp) {
	static const size_t turnoffTokenLen = strlen(TURN_OFF_TEXT);
	static const size_t toggleTokenLen = strlen(TOGGLE_TEXT);
	static const size_t turnonTokenLen = strlen(TURN_ON_TEXT);
	static const size_t pointSepTokenLen = strlen(POINT_SEPARATOR);

	char buffer[MAX_CHARS_LINE];
	while (fgets(buffer, MAX_CHARS_PRESENT, fp)) {
		
	}
}

bool parse_input_from_filepath(const char* filepath) {
	FILE* fp = fopen(filepath, "r");
    if (!fp) {
        perror("File opening failed");
        return false;
    }

    bool success = parse_input_file(fp);
    fclose(fp);
    return success;
}

int main(int argc, char* argv[]) {
	// Supporting different kinds of input
	if (argc > 1) {
		if (!parse_input_from_filepath(argv[1]))
			return 2;
	}
	else if ((fseek(stdin, 0, SEEK_END), ftell(stdin)) > 0){
	  rewind(stdin);
	  if (!parse_input_file(stdin))
	  	return 2;
	}
	else {
		printf("Provide input with a filepath or via the standard input\n");
		return 1;
	}

	return 0;
}