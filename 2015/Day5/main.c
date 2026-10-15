#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define VOWEL_TARGET 3

#define INPUT_DATA_FILENAME "./data.txt"
#define MAX_CHARS_STRING 16
#define NUM_STRINGS 1000

typedef struct {
	char str[MAX_CHARS_STRING + 1];
} String;

int is_vowel(char c) {
	return c == 'a' || c =='e' || c == 'i' || c == 'o' || c == 'u';
}

#define NUM_BANNED_SUBSTRINGS 4

static const char banned_substrings[NUM_BANNED_SUBSTRINGS][2] = {
	{'a', 'b'},
	{'c', 'd'},
	{'p', 'q'},
	{'x', 'y'}
};

static inline int is_banned(char prevC, char c) {
	for (size_t i = 0; i < NUM_BANNED_SUBSTRINGS; i++) {
		if (prevC == banned_substrings[i][0] &&
			c     == banned_substrings[i][1]) {
			return 1;
		}
	}
	return 0;
}

int is_nice_string(const char* str) {
	assert(str);

	int vowelCond = (size_t)VOWEL_TARGET < 1;
	int twiceInARowCond = 0;
	int bannedSubstrCond = 1;

	size_t vowelCount = 0;
	char prevC = '\0';
	size_t i = 0;
	char c = str[0];
	while (c != '\0') {
		if (!vowelCond) {
			if (is_vowel(c)) {
				vowelCount++;
				if (vowelCount == VOWEL_TARGET) {
					vowelCond = 1;
					//printf("%s meets the vowel count condition\n", str);
				}
			}
		}

		if (!twiceInARowCond) {
			if (c == prevC) {
				twiceInARowCond = 1;
				//printf("%s meets the twice in a row char condition\n", str);
			}
		}

		if (is_banned(prevC, c)) {
			bannedSubstrCond = 0;
			//printf("%s contains a banned substring\n", str);
			break;
		}

		prevC = c;
		c = str[++i];
	}

	int isNice = vowelCond && twiceInARowCond && bannedSubstrCond;
	return isNice;
}

// This program gets the data from the standard input
int main(void) {
	// is_nice_string("ugknbfddgicrmopn");
	// is_nice_string("aaa");
	// is_nice_string("jchzalrnumimnmhp");
	// is_nice_string("haegwjzuvuyypxyu");
	// is_nice_string("dvszwmarrgswjxmb");

	String strings[NUM_STRINGS];
	char buffer[MAX_CHARS_STRING + 1];
	int c;
	size_t buffer_i = 0, strings_i = 0;
	while ((c = fgetc(stdin)) != EOF) {
		if (c == '\n') {
			buffer[buffer_i] = '\0';
			//printf("%s\n", buffer);
			memcpy(strings[strings_i].str, buffer, MAX_CHARS_STRING + 1);
			// When all the strings have the same length this is not necessary
			// I am leaving it anyway
			memset(buffer, '\0', MAX_CHARS_STRING + 1);
			buffer_i = 0;
			strings_i++;
		}
		else {
			buffer[buffer_i] = c;
			buffer_i++;
		}
	}
	if (buffer_i > 0) {
		buffer[buffer_i] = '\0';
		//printf("%s\n", buffer);
		memcpy(strings[strings_i].str, buffer, MAX_CHARS_STRING + 1);
	}

    size_t nice_count = 0;
    for (size_t i = 0; i < NUM_STRINGS; i++) {
    	if (is_nice_string(strings[i].str))
    		nice_count++;
    }

	printf("Solution: [%zu] nice strings.\n", nice_count);
}
