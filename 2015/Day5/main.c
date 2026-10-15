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

void clean_input(char *buffer) {
    buffer[strcspn(buffer, "\n")] = '\0';
}

int is_vowel(char c) {
	return c == 'a' || c =='e' || c == 'i' || c == 'o' || c == 'u';
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

		if (prevC == 'a') {
			if (c == 'b') {
				bannedSubstrCond = 0;
				//printf("%s contains a banned substring (ab)\n", str);
				break;
			}
		}
		else if (prevC == 'c') {
			if (c == 'd') {
				bannedSubstrCond = 0;
				//printf("%s contains a banned substring (cd)\n", str);
				break;
			}
		}
		else if (prevC == 'p') {
			if (c == 'q') {
				bannedSubstrCond = 0;
				//printf("%s contains a banned substring (pq)\n", str);
				break;
			}
		}
		else if (prevC == 'x') {
			if (c == 'y') {
				bannedSubstrCond = 0;
				//printf("%s contains a banned substring (xy)\n", str);
				break;
			}
		}


		prevC = c;
		c = str[++i];
	}

	int isNice = vowelCond && twiceInARowCond && bannedSubstrCond;
	// if (isNice)
	// 	printf("%s is NICE\n", str);
	// else
	// 	printf("%s is NAUGHTY\n", str);
	return isNice;
}

int main(void) {
	// is_nice_string("ugknbfddgicrmopn");
	// is_nice_string("aaa");
	// is_nice_string("jchzalrnumimnmhp");
	// is_nice_string("haegwjzuvuyypxyu");
	// is_nice_string("dvszwmarrgswjxmb");

	String strings[NUM_STRINGS];
	FILE* fp = fopen(INPUT_DATA_FILENAME, "r");
    if (!fp) {
        perror("File opening failed");
        return -1;
    }
    for (int i = 0; i < NUM_STRINGS; i++) {
    	char buffer[MAX_CHARS_STRING + 1];
    	if (!fgets(buffer, MAX_CHARS_STRING + 2, fp)) {
        	perror("File reading failed");
   			fclose(fp);
        	return -2;
    	}
    	clean_input(buffer);
    	memcpy(strings[i].str, buffer, MAX_CHARS_STRING + 1);
    }
    fclose(fp);

    size_t nice_count = 0;
    for (size_t i = 0; i < NUM_STRINGS; i++) {
    	if (is_nice_string(strings[i].str))
    		nice_count++;
    }

	printf("Solution: [%zu] nice strings.\n", nice_count);
}
