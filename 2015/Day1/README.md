# 2015, Day 1

## Review notes (written by Claude Opus 5.5)

> This section was written by Claude Opus 5.5, an AI assistant, in October 2026. It is not the author's text.
> I reviewed the finished solution together with the author. The code was left as it was: nothing described here has been applied. Each finding was checked by running a copy of the program.
> The reviews of Days 1 to 4 were all done at the same time, after the author had solved those four days. That is why some of the same mistakes appear in more than one day: none of this feedback existed when the later days were written.

The program gives the right answers for the author's input. None of the findings changes that result; they are assumptions about the input that the code does not check.

### Main findings

1. **The input size is hard-coded.** The buffer holds exactly 7000 characters, the size of this input. A longer input is cut without any message, and the program prints the answer for the first 7000 characters.
2. **Any character other than `(` counts as "down".** With an input shorter than the buffer, a newline at the end of the file is read as one more move and the final floor is off by one. The author's file is safe only because it fills the buffer exactly.
3. **Part 2 cannot say "the basement is never reached".** In that case the function returns a position that looks valid. The combined function returns a different one, so the `assert` that compares them aborts the program.
4. **The input path depends on the working directory.** `./data.txt` is only found when the program is run from its own folder.
5. **The timings are too short to compare.** Each function is timed once and takes tens of microseconds; the variation between runs is larger than the differences between the functions.

### Smaller points

- `return -1` and `return -2` reach the shell as exit codes 255 and 254.
- With an empty file, the message is `File reading failed: Undefined error: 0`, because `perror` is called without checking whether an error happened.
- The `const` globals for the two characters are not constant expressions in C, so they cannot be `case` labels.
- The result of `strlen` (a `size_t`) is stored in an `int`, and `main()` is declared without `void`.
