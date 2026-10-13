# 2015, Day 3

## Review notes (written by Claude Opus 5.5)

> This section was written by Claude Opus 5.5, an AI assistant, in October 2026. It is not the author's text.
> I reviewed the finished solution together with the author. The code was left as it was: nothing described here has been applied. Each finding was checked by running a copy of the program.
> The reviews of Days 1 to 4 were all done at the same time, after the author had solved those four days. That is why some of the same mistakes appear in more than one day: none of this feedback existed when the later days were written.

The program gives the right answers for the author's input, and compiles without warnings under `-Wall -Wextra`. Unlike Days 1 and 2, the review found two memory errors that are present with the real input. The program survives them by luck.

### Memory errors

1. **With two Santas, the path strings have no null terminator.** The buffer size is 8193 (the 8192 moves plus one) divided by the number of Santas. For two, integer division gives 4096, and each Santa receives exactly 4096 characters, so there is no byte left for the terminator. `parsePath` then reads past the end of the buffer looking for it. AddressSanitizer reports a `heap-buffer-overflow` at that loop. In the normal build the effect varies between runs: in one run out of three, the loop read 8 extra bytes, printed "Unexpected character!" eight times and wrote eight entries past the end of the coordinate array.
2. **The grid index uses the wrong dimension.** The grid has `width * height` cells and is indexed as `x * width + y`, which is only correct for a square grid. For this input the grid is wider than tall, so the highest indexes fall beyond the allocation (AddressSanitizer: `heap-buffer-overflow` in `traverseNeightbourhood`). The count is still right because every function uses the same formula. With a grid taller than wide the count is wrong: `^^^^^>` reports 10 houses where there are 7.

### Other findings

3. **East and west are swapped.** `>` decreases `x` and `<` increases it, so the route is a mirror image. The number of houses is unaffected; the coordinates printed for the most visited house are mirrored.
4. **The replay uses the buffer size, not the number of moves read.** Unused entries count as visits to the starting house, which inflates its number of deliveries.
5. **The result of `fgetc` is stored in a `char`.** A byte 0xFF in the input is taken for the end of the file and the reading stops there.
6. **`perror` is used for the program's own error.** For an unexpected character it prints the message followed by `: Undefined error: 0`.
7. **Clock ticks are printed as "ms".** On macOS a tick is a microsecond.

### Smaller points

- The `#ifndef` around `NUM_SANTAS` is commented out, so choosing the part means editing the file. With it enabled, `-DNUM_SANTAS=1` selects Part 1.
- The route is stored three times (text, coordinates, grid). Sorting the visited positions and counting the changes would answer the same question without the grid, the bounding box or the index formula. I did not run that alternative on the real input.
- None of the `calloc` calls is checked.
- The path and the exit codes have the same weaknesses described in the Day 1 notes.
