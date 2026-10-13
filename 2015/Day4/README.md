### Part A

The bold decision of trying to implement the MD5 algorithm from the pseudocode ended up frustrating me and making me drop the challenge for months. I am not particularly proud of it. I ended up relying on some help in other aspects too. To summarize, the points I struggled the most with were:

1. Validating the first MD5 implementation. I tried so many times to get the expected result for "The quick brown fox jumps over the lazy dog", listed on Wikipedia, to no avail. I ended up asking for some hints and it turned out I had made three mistakes:
   - the digest was printed as text with `%s` when it is 16 raw bytes
   - an operator precedence mistake in the rotate line
   - an off-by-one in the padding condition, for messages of exactly 55 bytes

2. Getting the right format for printing the hex took me far too long. After using `%c` I tried `%hhx`, but then the padding was also wrong. Third time's the charm, `%02hhx` was the answer.

3. I misread the pseudocode, which resulted in the off-by-one mentioned before. Here is where I needed the most help. It started with me not taking into account the last 8 bytes. From there, it was like falling into a pit of trying to figure out the logic, writing down the conditions and failing spectacularly.

4. I made a mistake when calculating the number of characters the counter would take when appended to the key. This mistake did not make the solution wrong, but it made each iteration slower than the previous one. It was a small mistake where I divided the counter by 10 once instead of counting how many times I had to divide it by 10 to get down to a single digit.

Overall, a hard experience with a satisfying end. At least I have learnt some things, I hope.

### Part B

After all the suffering in Part A, this one was almost trivial: the puzzle only asks for six leading zeroes instead of five. I turned the target into a second program argument and that was it.

Well, almost. While adapting the code I managed to delete the `free` for the string built on each iteration, so the program was quietly eating hundreds of megabytes. It still gave the right answer, which is exactly why I did not notice it myself.


---

### Review notes (written by Claude Opus 5.5)

> This section was written by Claude Opus 5.5, an AI assistant, in October 2026. The two sections above are the author's own words; this one is not.
> I helped during the work described above, mostly with hints at the author's request, and reviewed the finished solution afterwards. The code was left as it was after that review: nothing listed under "Still present" has been applied. The errors in the first list were seen while they happened. Those under "Still present" were checked by running a copy of the program, except the dependence on little-endian machines, which follows from reading the code.
> The reviews of Days 1 to 4 were all done at the same time, after the author had solved those four days. That is why some of the same mistakes appear in more than one day: none of this feedback existed when the later days were written.

The MD5 function matches the system `md5` for messages of 0, 1, 43, 54, 55, 56, 57, 63, 64, 65, 119, 120 and 200 bytes, and the program gives the expected numbers for both public examples of the puzzle.

#### Errors found while the solution was being written

The author's sections describe most of these. In order:

1. The 16-byte digest was printed as text with `%s`, then with `%c`, then with `%hhx` without zero padding.
2. A missing pair of parentheses in the rotate line: the addition was applied before the OR.
3. The padding condition sent messages of exactly 55 bytes to the wrong branch. A later rewrite of the padding gave a wrong size for every message and made the block loop read past the end of the buffer.
4. `itoa` did not compile, because it is not standard C.
5. The number of digits of the counter was computed as `counter / 10 + 1`, and that value was passed in both arguments of `calloc`, so each iteration was slower than the previous one.
6. In the hex conversion, a 2-byte buffer received two digits plus the terminator, and the output parameter was declared `const`.
7. The search compared the bytes of the digest with the character `'0'`.
8. In Part B, the `free` for the string built on each iteration was deleted. Memory for about a million iterations went from 1.7 MB to 236 MB.

#### Still present

- **The MD5 function only works on little-endian, 64-bit machines.** It copies bytes directly onto 32-bit words and writes the length from a `size_t`.
- **Two warnings remain under `-Wall -Wextra`:** `int` loop variables compared with `size_t` values.
- **The second argument is not fully validated.** `5abc` is accepted as 5. `-1` is converted to a huge number and stopped only by an `assert`.
- **Error messages are written to standard output**, not to standard error.
- **`maxLeadingZeros` is a `static` local**, so it would keep its value in a second call to `solve`.
- **The function is named `m5d`** where the algorithm is MD5.

#### Alternatives not applied

- Building the key and the counter with a single `snprintf` into a fixed buffer.
- Passing the data to hash as bytes with an explicit length, and returning the digest as `uint8_t`.
- Hashing without allocating memory, by padding only the last one or two blocks in a fixed buffer.
- Checking the leading zeroes on the raw bytes, and building the hex text only to print it.
