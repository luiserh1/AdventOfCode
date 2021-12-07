## Problem

https://adventofcode.com/2021/day/3

## Input

TXT file containing a binary number per line

## **PART A**

### Goal
+ Get the power **consumption** of the submarine

### Details
+ The compsuption value is the result of **multiplying** the **gamma** and **epsilon** rates
+ Both rates are binary numbers where
+ + in the **gamma** rate each bit has the value of the **most common** bit in the corresponding position
+ + in the **epsilom** rate each bit has the value of the **least common** bit in the corresponding position
+ The **solution** is a **decimal** number

### My solutions:

753279, **749376**

### Notes
+ I was getting the wrong binary to decimal trasnformation because "0^0 = 1" *facepalm*
+ Despite the fact that I got some wrong answers I didn't submit them... the over keeps getting!

## **PART B**

### Goal
+ Get the **life support rating**

### Details
+ The life support rating is obtained by **multiplying** the oxygen generator rating (**O2_rating**)
by the CO2 scrubber rating (**CO2_rating**)
+ For both ratings, every number in the input is a valid candidate
+ A loop of discards is applied until only **one number** remains
+ + Each **iteration** considers just **one bit** of the binary numbers, **starting** from the first bit (**left**)
+ + The discard criteria varies depending on the rating:
+ + + O2_rating: The numbers with the **most common** value in the current bit position are kept. In case of tie, keep the ones with "1" in that bit
+ + + CO2_rating: The numbers with the **least common** value in the current bit position are kept. In case of tie, keep the ones with "0" in that bit
+ + When an iteration ends the **next** considered bit is the one **to the right**

### My solutions:

757182, 3932936, 2368632, 2368632, 3925824, **2372923**

### Notes
+ Now there is no doubt, the streak is over :(
+ This's been the hardes so far
+ I made some mistakes and trying to fix them I made some more
+ Even the test has been implemented for this oen
+ Some of the mistakes:
+ + "/" returns a float, "//" returns an integer (newbie)
+ + if most_common_value > 1:
		o2_rating_candidates = [candidate for candidate in o2_rating_candidates if candidate[i] == 1]
	else:
		o2_rating_candidates = [candidate for candidate in o2_rating_candidates if candidate[i] == most_common_value]

and

o2_rating_candidates = [candidate for candidate in o2_rating_candidates if candidate[i] == most_common_value or

are not equivalent

+ Trying to generalize the code too much has turned against me

+ In addition to the logical errors, I misunderstood the discard criteria at first
               
