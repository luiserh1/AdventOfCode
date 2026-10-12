#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define M5D_LENGTH 16
#define M5D_HEX_LENGTH 32

uint32_t rotate_left(uint32_t value, uint32_t shift) {
	return (value << shift) | (value >> (sizeof(uint32_t) * 8 - shift));
}

// Based on the pseudocode from: https://en.wikipedia.org/wiki/MD5
void m5d(const char* srcMsg, char output[16]) {
	// per-round shift amounts
	static uint32_t s[64] = {
		7, 12, 17, 22, 
		7, 12, 17, 22, 
		7, 12, 17, 22, 
		7, 12, 17, 22,
		5,  9, 14, 20,
		5,  9, 14, 20,
		5,  9, 14, 20,
		5,  9, 14, 20,
		4, 11, 16, 23,
		4, 11, 16, 23,
		4, 11, 16, 23,
		4, 11, 16, 23,
		6, 10, 15, 21,
		6, 10, 15, 21,
		6, 10, 15, 21,
		6, 10, 15, 21
	};

	// Precomputed table of the integer part of the sines of integers (Radians) as constants
	static uint32_t K[64] = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
	};

    // Stracting relevant info from the source
    const size_t msgBaseLength = strlen(srcMsg);
    const size_t msgBaseSize = msgBaseLength * sizeof(char);
    const size_t msgBaseSizeInBits = msgBaseSize * 8;
    // [ leftover message bytes ][ 0x80 ][ zeros... ][ 8 length bytes ]
    //     r bytes                1 byte   whatever     always last 8
    //                                     is left
    const size_t mandatoryBytesAppended = 9;
    size_t msgSizeAfterPadding0s;
    size_t msgSizeMod64 = msgBaseSize % 64;
    if (msgSizeMod64 + mandatoryBytesAppended < 65)
		msgSizeAfterPadding0s = msgBaseSize + (56 - msgSizeMod64);
	else
		msgSizeAfterPadding0s = msgBaseSize + (64 - msgSizeMod64) + 56;
    const size_t msgFinalSize = msgSizeAfterPadding0s + 8;

    uint8_t* msg = calloc(msgFinalSize, sizeof(uint8_t));
    memcpy(msg, srcMsg, msgBaseSize);

    // Initialize variables
    uint32_t a0 = 0x67452301;
    uint32_t b0 = 0xefcdab89;
    uint32_t c0 = 0x98badcfe;
    uint32_t d0 = 0x10325476;

    // Preprocessing: adding 1
    msg[msgBaseSize] = 0x80;
    // Preprocessing: padding with 0s
    for (int i = msgBaseSize + 1; i < msgSizeAfterPadding0s; i++)
    	msg[i] = 0x00;
    // Preprocessing: addiing original size
    memcpy(msg + msgSizeAfterPadding0s, &msgBaseSizeInBits, sizeof(size_t));

    // Process the message in successive 512-bit (64-byte) chunks:
    for (int chunkI = 0; chunkI < msgFinalSize; chunkI += 64) {
    	// Break chunk into sixteen 32-bit words
    	uint32_t M[16];
    	memcpy(M, &msg[chunkI], sizeof(M));
    	// Initialize hash value for this chunk
    	uint32_t A = a0;
    	uint32_t B = b0;
    	uint32_t C = c0;
    	uint32_t D = d0;

    	// Main loop:
    	for (int i = 0; i < 64; i++) {
    		uint32_t F, g;
    		if (i < 16) {
    			F = (B & C) | (~B & D);
    			g = i;
    		}
    		else if (i < 32) {
    			F = (D & B) | (~D & C);
    			g = (5 * i + 1) % 16;
    		}
    		else if (i < 48) {
    			F = B ^ C ^ D;
    			g = (3 * i + 5) % 16;
    		}
    		else {
    			F = C ^ (B | ~D);
    			g = (7 * i) % 16;
    		}

    		F = F + A + K[i] + M[g];
    		A = D;
    		D = C;
    		C = B;
    		B = B + rotate_left(F, s[i]);
    	}
    	a0 += A;
    	b0 += B;
    	c0 += C;
    	d0 += D;
    }

    // Build output
    memset(output, 0x00, sizeof(char) * 16);
    memcpy(output,      &a0, sizeof(uint32_t));
    memcpy(output + 4,  &b0, sizeof(uint32_t));
    memcpy(output + 8,  &c0, sizeof(uint32_t));
    memcpy(output + 12, &d0, sizeof(uint32_t));

    // Clean up
	free(msg);
}

// assuming char hex[M5D_HEX_LENGTH + 1]
void m5d_hex(const char* m5d, char* hex) {
	for (size_t i = 0; i < M5D_LENGTH; i++) {
		char buffer[3];
		sprintf(buffer, "%02hhx", m5d[i]);
		memcpy(hex + i*2, buffer, sizeof(char)*2);
	}
	hex[M5D_HEX_LENGTH] = '\0';
}

void solve(const char* key, size_t targetLeadingZeros) {
	assert(targetLeadingZeros < M5D_HEX_LENGTH);
	for (size_t counter = 1; counter < SIZE_MAX; counter++) {
		size_t base10Digits = 1;
		for (size_t remainingDigits = counter; remainingDigits / 10 > 0; remainingDigits /= 10)
			base10Digits++;

		const size_t conunterChars = base10Digits + 1;
		const size_t keyLength = strlen(key);
		const size_t requiredChars = keyLength + conunterChars;
		char counterString[conunterChars + 1];
		sprintf(counterString, "%zu", counter);


		char* keyAndCounter = calloc(requiredChars, sizeof(char));
		memcpy(keyAndCounter, key, sizeof(char) * keyLength);
		memcpy(keyAndCounter + keyLength, counterString, sizeof(char) * conunterChars);
		
		char m5dStr[M5D_LENGTH];
		m5d(keyAndCounter, m5dStr);

		free(keyAndCounter);

		char hex[M5D_HEX_LENGTH + 1];
	 	m5d_hex(m5dStr, hex);

		static size_t maxLeadingZeros = 0;
		size_t leadingZerosCount = 0;
		for (; leadingZerosCount < targetLeadingZeros; leadingZerosCount++) {
			char c = hex[leadingZerosCount];
			if (c != '0')
				break;
		}
		if (leadingZerosCount > maxLeadingZeros) {
			maxLeadingZeros = leadingZerosCount;
			printf("New maximum of leading 0s found: %zu. The hash is: %s\n",
				maxLeadingZeros, hex);
		}
		if (leadingZerosCount < targetLeadingZeros)
			continue;

		printf("Solution found, the target has for key [%s] is: %s\n", key, hex);
		printf(". The number we are looking for is, then: %zu\n", counter);
		break;
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("This program takes 2 mandatory arguments: the key"
			" and the amount of leading zeroes target.\n");
		return 1;
	}
	size_t targetLeadingZeros;
	if (sscanf (argv[2], "%zu", &targetLeadingZeros) != 1) {
		printf("The second argument has to be a number.\n");
    	return 2;
	}

	solve(argv[1], targetLeadingZeros);

	return 0;
}