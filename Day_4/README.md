## Problem

https://adventofcode.com/2021/day/4

## Input

TXT file containing a first line with a sequence of numbers separeted by commas and many blocks of five lines with five numbers each.
The blocks are separated from each other by a blank line. These blocks represent bingo boards and the sequence of
numbers represents the order in which the numbers are pulled out.

## **PART A**

### Goal
+ Get the **score** of the **winning board**

### Details
+ The winning board is the one that **first** completes a **row** or a **column**
+ To complete any of them **all** the numbers of it have to be **pulled out**
+ The numbers are pulled out one by one and sequentialy
+ As previously described, each board has 5 columns and 5 rows, making a **5-sizez regular matrix**
+ The score of a winning board is calculated by **multiplying** the **last** pulled out *number by the result of
the **sum** of all the numbers in the board that **haven't been pulled out**

### My solutions:
**2745**

### Notes
+ Surprisingly, the most troublesome part has been dealing with the input
+ Using indices has felt like a really appropiate idea
+ First try! Yahoooooooo!
+ From now on it's quite possible that I implement all the tests
+ It has taken me 2 hours aprox. Maybe is too much, but nothnig compared to the previous one

## **PART B**

### Goal
+ Get the score of the las winning board

### Details
+ Same rules to declare a winner

### My solutions:
24480

### Notes
+ The "reverse()" function of a list reverses the list, but returns "None"
+ The algotythm passed the test, but gave the wrong answer. Yikes
+ I made a mistake where I was calculating the score after the loser was decided,
when I must have waited for it to end
+ I leave it on standby, I can't figure out why isn't working. I've checked that
the loser is correct and that when it ends, the correct numbers are used on the calculation.
I'll come back when I got a gasp of what's happening