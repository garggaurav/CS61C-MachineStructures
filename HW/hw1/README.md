CS61C Fall 2014 Homework 1
==========================

TA: Riyaz Faizullabhoy

Due Sunday, September 7, 2014 @ 11:59pm

Goals
-----

This assignment covers a range of topics related to number
representation. It is also intended to get you familiar with basic C
bitwise operators.

Submission
----------

Submit your solution by creating a directory named `hw1` that contains a
file named [`hw1.txt`](hw1.txt). **Please use the provided format in
`hw1.txt`.** File names are case-sensitive and the submission program
will not accept your submission if your file names differ at all from
those specified. From within that directory, type `submit hw1`. Partners
are not allowed on this assignment.

Exercises
---------

### Problem 1: Number representation - 5pts

Put your answers to the following questions in `hw1.txt`

Assume we are dealing with 8 bit numbers for this problem. Fill in the
following table according to the representation given by the column
header. If you are given binary or hexadecimal, give the decimal value
interpreted under the given representation. If you are given a decimal
value, convert it to binary under the given representation and write
your answer in hexadecimal. Put "n/a" if the value cannot be converted.

  ---------------- -------------- ---------------------- ---------------------- ----------------------
                   **unsigned**   **sign & magnitude**   **one's complement**   **two's complement**

  `0b11110000`                                                                   

  `0b00001111` \                                                                 
                                                                                

  `0x0F`                                                                         

  `0xA1`                                                                         

  `0xFF`                                                                         

  `0xBE`                                                                         

  `64`                                                                           

  `-35`                                                                          

  `128`                                                                          

  `-128`                                                                         
  ---------------- -------------- ---------------------- ---------------------- ----------------------

\

### Problem 2: C bitwise operators - 5pts

Put your answers to the following questions in `hw1.txt`

Note: If you are unfamiliar with or need to review the truth tables for
the standard 2-input logic gates, just Google or Wikipedia 'logic
gates.' Same goes for 'bit-shifting.'

C provides bitwise commands for `AND(&), OR(|), XOR(^),` and `NOT(~)`.

1.  Let `x` be a single-bit input. Fill in the following blanks with
    either `0, 1, x,` or `x̅` (`NOT x`):
     
     
    `x & 0 = ___ `
     
    `x | 0 = ___ `
     
    `x ^ 0 = ___ `
     
    `x & 1 = ___ `
     
    `x | 1 = ___ `
     
    `x ^ 1 = ___ `
     
2.  Based on your responses, look at the columns (grouped by operation)
    above. Which operation would be useful for:
    1.  turning bits OFF?
    2.  turning bits ON?
    3.  flipping bits?

3.  Now let's also consider logical bit-shifting operators for
    `LEFT SHIFTING(<<)` and `RIGHT SHIFTING(>>)` which are also provided
    in C (you may have seen them in 61B in Java as well). Note that
    logical left shifting works on both unsigned and signed types,
    whereas logical right shifting only makes sense for unsigned types.
    1.  Fill in the blank with the result in terms of an 8-bit binary
        number: \
        \
           `  ((0b01010101 << 3) & 0xAE) | 2 = ___`
    2.  Fill in the blank with the simplest numerical expression in
        terms of `x`, simple arithmetic operators (`+, -, *, /`, and
        `%`), and numerical constants : \
        \
           `  x << 4 = ___`
    3.  Fill in the blank with the simplest numerical expression in
        terms of `x`, simple arithmetic operators (`+, -, *, /`, and
        `%`), and numerical constants : \
        \
           `  x >> 1  = ___`
    4.  Write a simple expression for turning the `n`-th bit ON for a
        number `x`, in terms of `n, x,` bits, and bit-wise operators.
        You may assume `x` has at least `n+1` bits, and that the bits
        are indexed from zero.

\

### Problem 3: Picking representations - 6pts

Put your answers to the following questions in `hw1.txt`

Assume we are working with 8-bit numbers for the entirety of this
question.

1.  For each part below, you will be given a choice of two number
    representations to choose between. It's your job to pick the better
    number representation for the given criteria, or denote that both
    representations are equally good. Explain your answer in one
    sentence or less.:
    1.  You would like multiple ways to represent 0: \
        \
           `ONE'S COMPLEMENT`   or   `TWO'S COMPLEMENT`   or `BOTH`
    2.  You would like to maximize the range (distance between most
        negative represented number, and most positive represented
        number): \
        \
           `UNSIGNED`   or   `SIGN AND MAGNITUDE`   or `BOTH`
    3.  You would like to represent an equal number of positive and
        negative numbers: \
        \
           `SIGN AND MAGNITUDE`   or   `TWO'S COMPLEMENT`   or `BOTH`
    4.  You would like to maximize the range (distance between most
        negative represented number, and most positive represented
        number): \
        \
           `UNSIGNED`   or   `TWO'S COMPLEMENT`   or `BOTH`

2.  Describe how you could compare numbers represented in two's
    complement, in at most 3 simple steps, if you only have unsigned
    comparators (\<,≤,≥,\>,=,≠) and basic logic (if, and, or, else). You
    can use as many of these components as you need. Please keep each
    step to two sentences maximum, but be sure to describe each step in
    enough detail.

\

### Problem 4: Ternary - 4pts

Put your answers to the following questions in `hw1.txt`

Consider the ternary system: base 3. We will denote this system with the
subscript 3, here is an example for representing the number 4 in
ternary, using only two trits: `113`

Similar to the binary system, the ternary system has Three's Complement
for representng negative numbers: to negate a three's complement number,
the process is exactly the same as in two's complement because we invert
the number and add one. However, tritwise inversion is slightly
different: for each trit (that's what we call digits in ternary), its
inverse can be found by subtracting it from 2.

For example, we represent -4 as `123` in ternary three's complement.

For a system of `n`-digit unsigned ternary numbers, how many numbers can
be represented?

\
\

For an `n`-digit signed three's complement ternary number (n \> 1), what
is the number of negative integers?

\
\

For an `n`-digit signed three's complement ternary number (n \> 1), how
many zeros are there?

\
\

For a 4-digit signed three's complement ternary number, what is the
representation of -5?

\
\

