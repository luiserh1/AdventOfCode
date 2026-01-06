#include <stdio.h>
#include <string.h>

#define ASCII_TO_UNIT(X) ((int)X - (int)'0')

const char MAGNITUDE_SEPARATOR = 'x';

const char* PART1_TEST_DATA1 = "2x3x4";    // Expected area of 58
const char* PART1_TEST_DATA2 = "1x1x10";   // Expected area of 43

// Units are feet
typedef struct
{
	unsigned int l, w, h;
} Present;

void printPresent(Present *p) {
	printf("%d%c%d%c%d\n", p->l, MAGNITUDE_SEPARATOR, p->w, MAGNITUDE_SEPARATOR, p->h);
}

/* Expected string format
 * "lxwxh" where:
 * 'x' is a separator
 * 'l' is a natural number representing length
 * 'w' is a natural number representing width
 * 'h' is a natural number representing height
*/
Present parsePresent(const char* presentStr) {
	Present parsedPresent = { .l = 0, .w = 0, .h = 0 };
	char const* pStr = presentStr;
	while (*pStr != '\0')
		pStr++;
	pStr--;

	// Parsing height
	int digitMult = 1;
	while (*pStr != MAGNITUDE_SEPARATOR) {
		parsedPresent.h += ASCII_TO_UNIT(*pStr) * digitMult;
		digitMult *= 10;
		pStr--;
	}
	// Parsing width
	digitMult = 1;
	pStr--;
	while (*pStr != MAGNITUDE_SEPARATOR) {
		parsedPresent.w += ASCII_TO_UNIT(*pStr) * digitMult;
		digitMult *= 10;
		pStr--;
	}
	// Parsing length
	digitMult = 1;
	while (1) {
		pStr--;
		parsedPresent.l += ASCII_TO_UNIT(*pStr) * digitMult;
		digitMult *= 10;
		if (pStr == presentStr)
			break;
	}

	return parsedPresent;
}

// The formula is: 2*l*w + 2*w*h + 2*h*l + min(l*w,w*h,h*l)
static inline unsigned int computeRquieredPaper(Present *p) {
	unsigned int lwSideArea = p->l * p-> w;
	unsigned int whSideArea = p->w * p->h;
	unsigned int hlSideArea = p->h * p->l;
	unsigned int minArea = lwSideArea;
	if (whSideArea < minArea)
		minArea = whSideArea;
	if (hlSideArea < minArea)
		minArea = hlSideArea;
	return 2 * lwSideArea + 
		   2 * whSideArea +
		   2 * hlSideArea +
		   minArea;
}

int main()
{
	unsigned int paperArea = 0;

	Present testPresent = parsePresent(PART1_TEST_DATA2);
	printPresent(&testPresent);
	paperArea = computeRquieredPaper(&testPresent);

	printf("The elves should order %d square feet of wrapping paper\n", paperArea);
	return 0;
}
