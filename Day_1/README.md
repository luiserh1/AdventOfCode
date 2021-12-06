## Problem

https://adventofcode.com/2021/day/1

## Input

TXT file containing a number per line

## **PART A**

### Goal
+ Get the **amount** of times where there is an **increase** in the number compared to the previous line

### Details
+ First number is not increased (no previous measurement)

### My solutions: 1465, **1466**

### Notes

+ I've got 1465 as a wrong answer several times do to comparing strings instead of integers. (998 > 1006)
+ I've temporally forgot that the second paramether of the method "range" is not included

## **PART B**

### Goal
+ Same goal, but the values to compare are now windowed

### Details
+ To do the comparisson both windows have to get its members summed
+ A **window** contains **three** consecutive numbers
+ Thi offset when changing to the next window is 1 number

### My solution: **1491**

### Notes

+ When rebuilding the program to reuse code from the first part I learned something about the "passed by assignment"
arguments of the Python mrthods. I was passing the List "data" to a method and then reassigning its value inside the method,
hoping it would keep this new value after exiting the method. It didn't work as expected. However, updating the variable instead
of reassigning it did the trick:
	data = [...] _Vs_ data += [...]
+ I've submited the correct answer with the first attempt YAY!
+ The implementation of the B part is generalized, so it can also solve part A by chaging the "windws_size" parameter.
