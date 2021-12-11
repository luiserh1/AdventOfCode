## Problem

https://adventofcode.com/2021/day/7

## Input

TXT file containing a sequence of numbers representing the
horizontal position of the crabs

## **PART A**

### Goal
+ Optimization problem. Find the minimun displacement (use of fuel)
required to allign all the crabs

### Details
+ At the end, all the crabs must share the same position
+ The fuel used by a crab is equivalent to the distance it needs
to move in order to reach the final position
+ The final result is the sum of the fuel used by every crab

### My solutions:
**364898**

### Notes
+ Short data, so the greedy implementation has been worthy
+ FIRST...TRY!

## **PART B**

### Goal
+ Same goal

### Details
+ The "evaluation function" has changed:
	+ Fuel(X) = X + Fuel(X-1)
	+ Fuel(0) = 0
	

### My solutions:
104149091

### Notes
+ Aaaaaannnd another first try!
+ When I first read the problem I thought it required the application
of some algorithm or methodology of complex optimization problems. In the end,
it wa easier than that and the greedy implementation is enough (although I made
some precalculations hehe)
+ This problem has been the easiest so far. I am happy to have solve at least one
so fast :D
