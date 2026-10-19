I started reviewing the previous days code before I worked on this one. I tried to apply what I learnt then to improve the implementation this time. I still made several mistakes and took different approaches, some of which are kept in earlier commits. Another bad practice of mine was jumping too soon into implementation without drafting the algorithm first and reading the specification twice. Doing that would have saved me one or two headaches. I reduced the consultations with the AI (Claude Opus 5.5) this time, but I still needed some help with some logic and compile errors.

The part with the most relevant challenges was part two (or B, as I like to call it). One of my first approaches was using qsort and ordered insertions, aiming to keep an array of pairs of consecutive letters sorted all the time. This approach had several flaws, it was excessively complicated, slow and not the right tool for the case. Across both parts, these are the points where I asked the AI for hints:
- I used the wrong syntax to declare a constant 2D array
- I tried to use nested functions, which are not part of the C standard
- While comparing the speed of two commits, the AI found that my reading loop dropped the last line when the file did not end with a newline (EOF)
- I was using a correct approach but the code had two bugs that prevented it from getting the right answer:
	- I was not comparing all the relevant instances of equal pairs of chars in the same string
	- The validation loop was one iteration short

---

## Review notes (written by Claude Opus 5.5)

> This section was written by Claude Opus 5.5, an AI assistant, in October 2026. It is not the author's text; the paragraphs above are the author's own words.
> Unlike Days 1 to 4, which were reviewed together after all four were solved, this review was done right after Day 5 was finished. Nothing listed here had been applied when it was written. Findings marked as run were checked on a copy of the program; the rest follow from reading the code.

The final version of Part B agrees, line by line, with a deliberately naive checker on the whole input, passes the puzzle's examples, and runs without errors under AddressSanitizer. It also compiles cleanly with `-Wall -Wextra -pedantic -Werror`, both with and without `-DMOCK_RUN`.

### Main findings

1. **The reading loop writes without bounds checks** (run). Neither the character index nor the line index is compared with the size of its array. A line longer than 16 characters writes past the end of the line buffer, and more than 1000 lines write past the end of the array of strings; AddressSanitizer reports a `stack-buffer-overflow` in both cases. With fewer than 1000 lines, the final loop checks entries that were never written.
2. **Allocation failures are not handled.** If `malloc` fails, the error is printed and the list is used anyway with a `NULL` pointer. The result of `realloc` overwrites the only pointer to the old block, so a failure loses it and the next write goes through `NULL`.
3. **The pair list does not need the heap.** A 16-character string has at most 15 pairs, so a fixed array would replace the five allocator calls made for every string.
4. **The pair condition has simpler solutions than sorting** (run). Searching for each pair two or more positions later, and a 26 × 26 table of the first position of each pair, both give the same result as the author's version on every line of the input.
5. **The two parts are separate programs with the same `main`.** Every fix to the reading loop has to be made in both files.

### Smaller points

- The examples run under `-DMOCK_RUN` are checked by eye; a table of inputs with expected results, including `aaaa` and `zzazz` from the two bugs, would check them automatically.
- A two-character string makes the final comparison read a list entry that was never written. The result is unaffected, because such a string cannot meet the other condition.
- One compound literal mixes designated and positional initializers, and another depends on the order of the struct's members.
- `int` is used where `bool` would say "true or false".
- `perror` is used for the program's own messages, as in Day 3.
