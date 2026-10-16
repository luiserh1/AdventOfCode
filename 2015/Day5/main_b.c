#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS_STRING 16
#define NUM_STRINGS 1000

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

#ifdef MOCK_RUN
void print_pair(const Pair* p) {
	printf("[(%c, %c) at %zu] ", p->c1, p->c2, p->index);
}

void print_pairs(const PairList* pairs) {
	for (size_t i = 0; i < pairs->length; i++)
		print_pair(&(pairs->list[i]));
	printf("\n");
}
#endif

int compare_pairs(const void *a, const void *b) {
	const Pair *p = a;
    const Pair *q = b;
    if (p->c1 != q->c1)
    	return (p->c1 > q->c1) - (p->c1 < q->c1);
    if (p->c2 != q->c2)
    	return (p->c2 > q->c2) - (p->c2 < q->c2);
    else
    	return (p->index > q->index) - (p->index < q->index);
}

int equal_pairs(const Pair* p1, const Pair* p2) {
	return p1->c1 == p2->c1 && p1->c2 == p2->c2;
}

int do_overlap(const Pair* p1, const Pair* p2) {
	if (p1->index > p2->index)
		return ((p1->index - p2->index) < 2);
	else
		return ((p2->index - p1->index) < 2);
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
	int pairCond = 0;
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

	qsort(pairs.list, pairs.length, sizeof(Pair), compare_pairs);
#ifdef MOCK_RUN
	printf("Pairs of %s:\n", str);
	print_pairs(&pairs);
#endif
	Pair* p1 = &(pairs.list[0]);
	Pair* p2 = &(pairs.list[1]);
	for (size_t i = 2; i < pairs.length; i++) {
		if (equal_pairs(p1, p2)) {
			if (!do_overlap(p1, p2)) {
				pairCond = 1;
				break;
			}
		} else {
			p1 = p2;
		}

		p2 = &(pairs.list[i]);
	}
	if (equal_pairs(p1, p2) && !do_overlap(p1, p2))
		pairCond = 1;

	free_pair_list(&pairs);

	int isNice = pairCond && sandwitchLetterCond;
#ifdef MOCK_RUN
	if (isNice)
		printf("%s is NICE\n", str);
	else
		printf("%s is NAUGHTY\n", str);
#endif
	return isNice;
}

// This program gets the data from the standard input
int main(void) {
#ifdef MOCK_RUN
	is_nice_string("qjhvhtzxzqqjkmpb");
	is_nice_string("xxyxx");
	is_nice_string("uurcxstgmygtbstg");
	is_nice_string("ieodomkazucvgmuy");
#endif 

#ifndef MOCK_RUN
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
#endif
}
