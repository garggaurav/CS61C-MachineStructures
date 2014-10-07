CS61C Fall 2014 Homework 3 Part 1
=================================

**Lead TA: Rohan Chitnis**

**Due Wednesday, September 17th, 2014 @ 11:59pm**

Goals
-----

This assignment will cover MIPS. Part 2 will be released later, and will
cover caches and floating point.

Obtaining the Assignment
------------------------

Copy the framework files (`mode.c, mode.s`) into your working directory:

``` {.input}
$ cp -R ~cs61c/hw/03-1 hw3-1
```

Exercises
---------

### Problem 1: C to MIPS

Translate the given C code into MIPS. Put your answer in `mode.s`. Some
code is provided for testing your solution, as well as starter code that
initializes variables. When you run `mode.s`, it will inform you what
you got, and what was expected. Make sure they match!

To write and run MIPS, you can (and definitely should!) download MARS
[here](http://courses.missouristate.edu/kenvollmar/mars/).

    /*
         IMPORTANT: Assume an "int" equates to 1 word (4 bytes) in MIPS, the array is 
         sorted, and len is the length of the array.
    */
    int mode(int* arr, int len) {
      int currNum = arr[0];
      int count = 1;
      int mode = currNum;
      int modeCount = 0;
      int i;
      for (i = 1; i < len; i++) {
        if (arr[i] == currNum) {
          count++;
        }
        if (i == len - 1 || arr[i] != currNum) {
          if (count > modeCount) {
            modeCount = count;
            mode = currNum;
          }
          currNum = arr[i];
          count = 1;
        }
      }
      return mode;
    }

Submission Guidelines
---------------------

Please enter your solution in `mode.s`. Once you have finished your
assignment, go to the directory containing this file and type:

``` {.output}
$ submit hw3-1
```
