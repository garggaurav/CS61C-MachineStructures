CS61C Fall 2014 HW2: restricted grep (rgrep)
============================================

Lead TA: Rohan Chitnis (modified from hw by Paul Ruan, Eric Liang, and
originally by Conor Hughes)

**Due Sunday, September 14, 2014 at 23:59:59**

Goals
-----

The objective of this assignment is to get you familiar and comfortable
with string manipulation and algorithms in C. You'll also likely get
some good experience debugging C code.

Background
----------

`grep` is a UNIX utility that is used to search for patterns in text
files. It's a powerful and versatile tool, and in this assignment you
will implement a version that, while simplified, should still be useful.

Your assignment is to complete the implementation of `rgrep`, our
simplified, restricted grep. `rgrep` is "restricted" in the sense that
the patterns it matches only support a few regular operators (the easier
ones). The way `rgrep` is used is that a pattern is specified on the
command line. `rgrep` then reads lines from its standard input and
prints them out on its standard output if and only if the pattern
"matches" the line. For example, we can use `rgrep` to search for lines
that contain text file names that are at least 3 characters long (plus
the extension) in a file like the following:

``` {.output}

# so you can see what lines are in the file:
$ cat testin

1 fine.txt
2 reallylong.txt
3 abc.txt
4 s.txt
5 nope.pdf

# note that there is a space as the first character in the pattern:
$ ./rgrep ' ...+\.txt' < testin

1 fine.txt
2 reallylong.txt
3 abc.txt
    
```

What's going on here? `rgrep` was given the pattern "` ...+\.txt`"; it
printed only the lines from its standard input that matched this
pattern. How can you tell if a line matches the pattern? **A line
matches a pattern iff the pattern "appears" somewhere inside the line**.
In the absence of any special operators, seeing if a line matches a
pattern reduces to seeing if the pattern occurs as a substring anywhere
in the line. So for most characters, their meaning in a pattern is just
to match themselves in the target string. However, there are a few
special clauses you must implement:

. (period)

Matches any character (including newlines or spaces).

+ (plus sign)

The preceding character may appear 1 or more times (in other words, the
preceding character can be repeated several times in a row). Note that
this means the pattern ".+" can match any non-empty string.

? (question mark)

The preceding character may appear between 0 and 1 times (in other
words, the preceding character is optional).

\\ (backslash)

"Escapes" the following character, nullifying any special meaning it
has.

So, here are some examples of patterns and the kind of lines they match:

  ----------- ------------------------------------------------------------------------------------------------------------------------------------------------------------------
  (           An open parenthesis must appear somewhere in the line.
  hey+        Matches a line that contains the string "hey" followed by any number (0 or more) of y's.
  str?ing     Matches lines that contain the substrings "string" or "sting", since the "r" is optional.
  z.z\\.txt   Matches lines that contain the substring "zaz.txt", "zbz.txt", etc., where the character between the z's can be anything, including a period, newline, or space.
  ----------- ------------------------------------------------------------------------------------------------------------------------------------------------------------------

These are the only special characters you have to handle. With the
exception of the null char that terminates a string, you should not have
to handle any other character (like newlines and spaces) in any special
way. You may assume that your code will not be run against patterns that
don't make sense. You must follow the spec strictly - so \#including a
regular expression library will likely turn out badly for you.

Getting started
---------------

Copy the framework files (`Makefile, matcher.c, matcher.h, rgrep.c`)
into your working directory:

``` {.input}
$ cp -R ~cs61c/hw/02 hw2
```

To compile, type:

``` {.input}
$ make
```

To run against a particular pattern, use

``` {.input}
$ ./rgrep pattern
```

The skeleton code handles reading lines from standard input and printing
them out for you; you must implement the function
`int rgrep_matches(char *line, char *pattern)` in `matcher.c`, which
returns true if and only if the string contains the pattern. You may
also choose to implement `matches_leading`, which is also in
`matcher.c`, to guide your submission, though this is optional. You may
change matcher.c however you want, but **please do not modify any other
files**. The autograder will overwrite the other files in your
submission with reference versions, so you only need to submit
`matcher.c`.

Testing
-------

Be sure to test on a hive machine. For a quick sanity check to see if
your solution is on the right track, type:

``` {.input}
$ make check
```

Note that this doesn't mean your solution will receive full points,
since the autograder will be running a much larger suite of test cases
-- to be exact, the provided tests comprise less than half of our full
set. You should **test your code** to make sure that it properly matches
lines against patterns. One way to do this is to create a text file with
the lines you want to test against, say `test_input.txt` and then verify
that running `./rgrep pattern < test_input.txt` prints only the lines
that you think should match the pattern, and no others. You can also
just invoke `./rgrep pattern` and type lines, and verify that `rgrep`
repeats lines iff they match the pattern.

If you wish to replicate the sample tests from `make check`, run them
from the command line on a hive machine as follows:
`` test "`echo -ne "a\nb\nc" | ./rgrep 'a'`" = "a" `` (note the -ne
options to echo).

Note that your shell might interpret the backslash operator for you,
which is not what you want. For example, when you type at your shell

``` {.input}
$ ./rgrep \.hi < input.txt
```

your program might get the pattern ".hi" because the shell interpreted
the backslash before it got passed to your program. The solution is to
put the pattern in single quotes, so what you want to type is:

``` {.input}
$ ./rgrep '\.hi' < input.txt
```

This should ensure that your pattern operators aren't expanded or
consumed by the shell. You should also be aware that input lines may end
with a newline character, which the 'period' character will match.

Grading
-------

You will be autograded on a hive machine and your score will depend on
the tests your code passes. You won't get any points if your code
doesn't compile. Each feature will be worth the following:

Feature

Points

Patterns without special characters.

5

Patterns with periods.

5

Patterns with plus signs.

5

Patterns with question marks.

5

Patterns with periods, plus signs, question marks, and backslashes.

5

Submission
----------

When you are ready to submit, go into the directory that contains your
`matcher.c` file. You should only submit `matcher.c`. From within that
directory, run `submit hw2`. You can submit multiple times; we'll grade
the latest submission.

Suggestions
-----------

Many people have found this assignment really challenging in the past.
Here are some suggestions that may help you:

-   Start early.
-   Recursion can be your friend, based on your chosen implementation.
-   Write your own tests.

