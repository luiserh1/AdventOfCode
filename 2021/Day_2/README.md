## Problem

https://adventofcode.com/2021/day/2

## Input

TXT file containing a word and a number per line

## **PART A**

### Goal
+ Get the result of **multiplying** the final **horizontal position** by the final **depth**

### Details
+ Both of these values **start at 0**
+ There are three possible words in the input
+ Each word implies a change in one of the previous values. Be "word X" the format:
	+ "up": **decreases** the **depth** by X
	+ "down": **increases** the **depth** by X
	+ "forward" **increases** the **horizontal position** by X

### My solutions:

**1813801**

### Notes
+ Another one with just one try!
+ The "print" of the solution had the "h_desp" and switched

## **PART B**

### Goal
+ Same goal

### Details
+ The new variable "aim" is added and the words have different meanings:
	+ "up": **decreases** the **aim** by X
	+ "down": **increases** the **aim** by X
	+ "forward":
		+ **increases** your **horizontal position** by X
		+ **increases** your **depth** by the **aim multiplied by X**

### My solutions:

**1960569556**

### Notes
+ 3 in a row!
