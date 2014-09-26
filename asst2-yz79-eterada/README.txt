README for Assignment 2
P536

Sept 25, 2014

Peter Zhang (yz79)
Eriya Terada (eterada)


Answers to Questions:
1. Without threads, we would basically have a main while loop that
loops through various functions that handle the tasks of matrix calculation,
monitoring user input, and monitoring 'sharedfile.txt'.
  This means that the program will certainly be less responsive than the
version that incorporates multiple threads, since one process needs to
repeatedly do some calculation for a fraction of a time, wait for file I/O
for another, then finally spend some time waiting for user input.
  We would also like to mention that file I/O takes a VERY long time (compared
to the other tasks that take place), and that when the process is waiting for
user input, no calculation will be happening in the background, making this
implementation not only less responsive, but less efficient compared to the
multi-threaded version.

2. Since in Linux systems, there is a one-to-one mapping between user and
kernel threads, there should not be any noticeable differences in the behavior
between the two modes of operation. If we were to test this hypothesis, we
can use kthread_create() (included in the kernel) to use kernel threads in
our program, instead of using pthread_create().


APPENDIX
- A struct storing flags necessary for matrix multiplication is shared between threads.

- Your computer should have a compiler that supports OpenMP, for the parallel generation
of random matrices.

- Your computer should be running a *NIX environment and have some kind of
curses library installed for our program to run correctly.

- We use the inotify API to monitor the commands from 'sharedfile.txt'.
- As a reference for using inotify, we have consulted the code that appears in
  http://www.ibm.com/developerworks/linux/library/l-ubuntu-inotify/index.html

-- delete later --
- If you have a sequence of commands stored in 'sharedfile.txt', all of them
will be executed sequentially from the beginning, over and over again unless
you change the contents of the file.
------------------

- You are free to change the size of the matrices by modifying the DIM macro
in 'matmult.h'.

