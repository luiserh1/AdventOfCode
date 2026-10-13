# 2015, Day 2

## Review notes (written by Claude Opus 5.5)

> This section was written by Claude Opus 5.5, an AI assistant, in October 2026. It is not the author's text.
> I reviewed the finished solution together with the author. The code was left as it was: nothing described here has been applied. Each finding was checked by running a copy of the program.
> The reviews of Days 1 to 4 were all done at the same time, after the author had solved those four days. That is why some of the same mistakes appear in more than one day: none of this feedback existed when the later days were written.

The program gives the right answers for the author's input, and compiles without warnings under `-Wall -Wextra`. The findings are about what happens with any other input.

### Main findings

1. **The hand-written parser trusts every line.** It reads each line backwards until it finds a separator, without checking where the line starts. A line with a missing separator, or an empty line, makes it read before the beginning of the buffer: the normal build crashes with a segmentation fault, and AddressSanitizer reports a `stack-buffer-underflow` in `parsePresent`.
2. **Non-digit characters are converted as if they were digits.** With Windows line endings the program runs to the end, exits with status 0 and prints different totals, without any message.
3. **The number of lines is hard-coded to 1000.** With 999 lines the program stops with `File reading failed: Undefined error: 0`, although nothing failed. A 1001st line is ignored silently.
4. **The line buffer has little margin.** A line of 11 characters or more is split by `fgets`, and the remainder is read as if it were the next present, which leads to the crash from the first point.
5. **`ASCII_TO_UNIT` does not parenthesize its argument.** `ASCII_TO_UNIT(flag ? a : b)` returns `a` unconverted when `flag` is true. The calls in this program are not affected.

### Smaller points

- The "minimum of three" logic is written twice. Storing the three dimensions in ascending order when parsing would remove it from both parts.
- `presentToString` is never called. The compiler does not report it because the function is not `static`.
- `unsigned int` values are printed with `%d`.
- The path, the exit codes and the timings have the same weaknesses described in the Day 1 notes.

A version that parses with `sscanf`, reads until the end of the file and sorts the dimensions gives the same totals for the original input, also gives them with Windows line endings, and rejects a malformed line with a message.
