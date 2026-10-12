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
