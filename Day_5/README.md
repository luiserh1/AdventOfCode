## Problem

https://adventofcode.com/2021/day/5

## Input

TXT file containing pairs of numbers separated by a " -> ".
The numbers in the pairs are also separated by commas from each other
The pairs are 2D coordinates; the left one represents the begining
of a line segment and the second one the end

## **PART A**

### Goal
+ Get at how many points do at least two lines overlap

### Details
+ We work in a 2D grid
+ All units are natural numbers (and 0). This way we can see the grid as a bunch of points
+ This time only vertical and horizontal segments will be used
+ All the points between the begining and the end (both inclusive) are considered overlaped
by the segment they describe


### My solutions:
**6397**

### Notes
+ I' ve had the classic index out of bounds a couple of times. It's not hard to fix,
but I keep making the mistake over and ove again
+ First try! We are back

## **PART B**

### Goal
+ Same goal, but now the diagonals also count

### Details
+ Only diagonals forming 45ª with the axis
	+ Ej.: An entry like 1,1 -> 3,3 covers points 1,1, 2,2, and 3,3

### My solutions:
10312, **22335**

### Notes
+ Trying to generalize this code has been troublesome
+ I made a mistake where assuming I had to change a number of
points equivalent to the length of the segment. But the distance might be
negative. I fixed it with the "abs" function
+ TODO: Figure out why I had to manually increment the size of the grid in the
X axis to avoid ONE segment of exceding it
+ Submitted right with the first try, btw