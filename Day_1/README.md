**PART A**

Solution: 1466

Notes:

+ I've got 1465 as a wrong answer several times do to comparing strings instead of integers. (998 > 1006)
+ I've temporally forgot that the second paramether of the method "range" is not included

**PART B**

Solution: 1491

Notes:

+ When rebuilding the program to reuse code from the first part I learned something about the "passed by assignment"
arguments of the Python mrthods. I was passing the List "data" to a method and then reassigning its value inside the method,
hoping it would keep this new value after exiting the method. It didn't work as expected. However, updating the variable instead
of reassigning it did the trick:
	data = [...] _Vs_ data += [...]
+ I've submited the correct answer with the first attempt YAY!
+ The implementation of the B part is generalized, so it can also solve part A by chaging the "windws_size" parameter.
