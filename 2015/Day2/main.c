#include <stdio.h>
#include <string.h>

#include <time.h>

#define NUM_PRESENTS 1000
#define MAX_CHARS_PRESENT 12
#define MAGNITUDE_SEPARATOR 'x'
#define INPUT_DATA_FILENAME "./data.txt"

#define ASCII_TO_UNIT(X) ((int)X - (int)'0')

// Units are feet
typedef struct {
	unsigned int l, w, h;
} Present;

void presentToString(Present *p, char* str) {
	sprintf(str, "%d%c%d%c%d", p->l, MAGNITUDE_SEPARATOR, p->w, MAGNITUDE_SEPARATOR, p->h);
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
	while (*pStr != '\0' && *pStr != '\n')
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

// PART1; The formula is: 2*l*w + 2*w*h + 2*h*l + min(l*w,w*h,h*l)
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


// PART2; The formula is: min(2*(l+w),2*(w+h),2*(h+l)) + l*w*h
static inline unsigned int computeRequieredRibbon(Present *p) {
	unsigned int lwSidePerimeter = 2 * (p->l + p-> w);
	unsigned int whSidePerimeter = 2 * (p->w + p->h);
	unsigned int hlSidePerimeter = 2 * (p->h + p->l);
	unsigned int minPerimeter = lwSidePerimeter;
	if (whSidePerimeter < minPerimeter)
		minPerimeter = whSidePerimeter;
	if (hlSidePerimeter < minPerimeter)
		minPerimeter = hlSidePerimeter;
	return minPerimeter + p->w * p->h * p->l;
}

int main()
{
	clock_t startTimeParsing, endTimeParsing,
	        startTimePart1, endTimePart1,
            startTimePart2, endTimePart2;
    double elapsedTimeParsing, elapsedTimePart1, elapsedTimePart2;

	unsigned int totalPaperArea = 0;
	unsigned int totalRibbonLength = 0;

	int numPresents = NUM_PRESENTS;
	Present presents[numPresents];

    startTimeParsing = clock();
	FILE* fp = fopen(INPUT_DATA_FILENAME, "r");
    if (!fp) {
        perror("File opening failed");
        return -1;
    }
    for (int i = 0; i < NUM_PRESENTS; i++) {
    	char buffer[MAX_CHARS_PRESENT];
    	if (!fgets(buffer, MAX_CHARS_PRESENT, fp)) {
        	perror("File reading failed");
   			fclose(fp);
        	return -2;
    	}
    	presents[i] = parsePresent(buffer);
    }
    fclose(fp);
    endTimeParsing = clock();

    startTimePart1 = clock();
	for (int i = 0; i < numPresents; i++) {
		Present *present = &presents[i];
		unsigned int presentAreaRequired = computeRquieredPaper(present);
		totalPaperArea += presentAreaRequired;
	}
	endTimePart1 = clock();

	startTimePart2 = clock();
	for (int i = 0; i < numPresents; i++) {
		Present *present = &presents[i];
		unsigned int presentRibbonRequired = computeRequieredRibbon(present);
		totalRibbonLength += presentRibbonRequired;
	}
	endTimePart2 = clock();

	printf("The elves should order %d square feet of wrapping paper\n", totalPaperArea);
	printf("The elves should order %d feet of ribbon\n", totalRibbonLength);

	printf("================================================================================\n");
    
    elapsedTimeParsing = (double)(endTimeParsing - startTimeParsing) / CLOCKS_PER_SEC;
    elapsedTimePart1 = (double)(endTimePart1 - startTimePart1) / CLOCKS_PER_SEC;
    elapsedTimePart2 = (double)(endTimePart2 - startTimePart2) / CLOCKS_PER_SEC;
    printf("Time spent parsing is: %f\n", elapsedTimeParsing);
    printf("Time spent solving part1 individually is: %f\n", elapsedTimePart1);
    printf("Time spent solving part2 individually is: %f\n", elapsedTimePart2);

	return 0;
}
