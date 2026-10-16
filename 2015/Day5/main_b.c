#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS_STRING 16
#define NUM_STRINGS 1000

static inline uint8_t letter_to_index(char c) {
	assert(c > '`' && c < '{');
	return (uint8_t)'{' - (uint8_t)c;
}

typedef struct {
	char str[MAX_CHARS_STRING + 1];
} String;

typedef struct {
	char c1, c2;
	size_t index;
} Pair;

typedef struct {
	Pair* list;
	size_t length;
	size_t capacity;
} PairList;

void print_pairs(const PairList* piezas) {
	for (size_t i = 0; i < piezas->length; i++) {
		printf("[%c, %c] ", piezas->list[i].c1, piezas->list[i].c2);
	}
	printf("\n");
}

int compare_pairs(const void *a, const void *b) {
	const Pair *p = a;
    const Pair *q = b;
    if (p->c1 != q->c1)
    	return (p->c1 > q->c1) - (p->c1 < q->c1);
    return (p->c2 > q->c2) - (p->c2 < q->c2);
}

#define INITIAL_LIST_CAPACITY 3

void init_pair_list(PairList* pairs) {
	Pair* list = malloc(INITIAL_LIST_CAPACITY * sizeof(Pair));
	if (!list)
		perror("ERROR: malloc failed\n");
	*pairs = (PairList){ list, 0, INITIAL_LIST_CAPACITY };
}

void append_pair(char c1, char c2, PairList* pairs) {
	if (pairs->length == pairs->capacity) {
		size_t newCapacity = pairs->capacity * 2;
		pairs->list = realloc(pairs->list, sizeof(Pair) * newCapacity);
		pairs->capacity = newCapacity;
	}

	pairs->list[pairs->length] = (Pair){ .c1 = c1, .c2 = c2, pairs->length };
	pairs->length++;
}

void free_pair_list(PairList* pairs) {
	free(pairs->list);
}

int is_nice_string(const char* str) {
	assert(str);

	char c1, c2, c3;
	if (str[0] == '\0')
		return 0;
	c1 = str[0];
	if (str[1] == '\0')
		return 0;
	c2 = str[1];
	c3 = str[2];

	// It contains a pair of any two letters that appears at least twice in
	// the string without overlapping, like xyxy (xy) or aabcdefgaa (aa),
	// but not like aaa (aa, but it overlaps).
	int pairCond = 1;
	// It contains at least one letter which repeats with exactly one
	// letter between them, like xyx, abcdefeghi (efe), or even aaa.
	int sandwitchLetterCond = 0;

	PairList pairs;
	init_pair_list(&pairs);

	size_t i = 2;
	while (c3 != '\0') {
		if (!sandwitchLetterCond) {
			if (c1 == c3) {
				sandwitchLetterCond = 1;
			}
		}

		append_pair(c1, c2, &pairs);

		c1 = c2;
		c2 = c3;
		c3 = str[++i];
	}
	append_pair(c1, c2, &pairs);

	size_t strLength = (i + 1);
	char* sortedStr = malloc(sizeof(char) * strLength);
	strcpy(sortedStr, str);
	qsort(sortedStr, strLength - 1, sizeof(char), (int (*)(const void*, const void *))strcmp);
	c1 = sortedStr[0];
	c2 = sortedStr[1];
	char dupChar = '\0';
	uint8_t* charAppearances = calloc('z' - 'a', sizeof(uint8_t));
	for (i = 0; i < strLength - 1; i++) {
		//charAppearances[letter_to_index(sorted)]
	}
	// printf("Pairs of %s:\n", str);
	// print_pairs(&pairs);
	// printf("Sorted str: %s\n", sortedStr);
	free(areDupped);
	free(sortedStr);
	free_pair_list(&pairs);

	int isNice = pairCond && sandwitchLetterCond;
	return isNice;
}

// This program gets the data from the standard input
int main(void) {
	is_nice_string("qjhvhtzxzqqjkmpb");
	is_nice_string("xxyxx");
	is_nice_string("uurcxstgmygtbstg");
	is_nice_string("ieodomkazucvgmuy");

	// String strings[NUM_STRINGS];
	// char buffer[MAX_CHARS_STRING + 1];
	// int c;
	// size_t buffer_i = 0, strings_i = 0;
	// while ((c = fgetc(stdin)) != EOF) {
	// 	if (c == '\n') {
	// 		buffer[buffer_i] = '\0';
	// 		//printf("%s\n", buffer);
	// 		memcpy(strings[strings_i].str, buffer, MAX_CHARS_STRING + 1);
	// 		// When all the strings have the same length this is not necessary
	// 		// I am leaving it anyway
	// 		memset(buffer, '\0', MAX_CHARS_STRING + 1);
	// 		buffer_i = 0;
	// 		strings_i++;
	// 	}
	// 	else {
	// 		buffer[buffer_i] = c;
	// 		buffer_i++;
	// 	}
	// }
	// if (buffer_i > 0) {
	// 	buffer[buffer_i] = '\0';
	// 	//printf("%s\n", buffer);
	// 	memcpy(strings[strings_i].str, buffer, MAX_CHARS_STRING + 1);
	// }

    // size_t nice_count = 0;
    // for (size_t i = 0; i < NUM_STRINGS; i++) {
    // 	if (is_nice_string(strings[i].str))
    // 		nice_count++;
    // }

	// printf("Solution: [%zu] nice strings.\n", nice_count);
}
