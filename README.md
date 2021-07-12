# Operating System Concepts
Just an attempt to understand core OS concepts.
## Table of contents
* [IO with system calls](#io-with-system-calls)
* [Pthread and mutex](#pthread-and-mutex)
* [Synchronisation: Condition Variables](#synchronisation-condition-variables)
* [Compile](#compile)

## IO with system calls
Write a program using only system calls that does the following:
* When run initially, creates a file with fixed sized records of contacts
* Each record will be fixed size of 40 characters
* Character 0-19 will hold the name of the person
* Characters 20-39 will hold the phone number
* In the initial run, create 10 random entries with name (alphabetical) and number (digits 0-9)
* Run the program second time and only read names and list them, one on a line
* Run the program third time and only read numbers and list them, one on a line
* Run the program fourth time and list every name and number (on a line each)
* Run the program fifth time with a command line argument of name 3 "Blue Sky" "5551212"
* This should replace the 3rd entry with the name and number from command line
* You cannot read anything in this operation
* You are allowed to only write 40 characters (no more)
* Run the program fourth time and list every name and number (on a line each) and verify that previous update worked
* You will need to learn about lseek(2) system call.

## Pthread and mutex
Write a program to create 5 (child) threads and make the parent wait until they exit.
* In each thread, write a message to screen with thread ID, then pthread_yield(), then write another message, then sleep for a few random seconds (1 to 20), then write a third message and exit.
* What can you tell about the effects of pthread_yield() vs sleep()?
* Run the program a few times to see if the output varies.

## Synchronisation: Condition Variables
### General instructions
Write the code using the Pthreds library. 
* Each producer and consumer should using condition variable(s). 
* Each should acquire the lock at the start and release it at the end. 
* Use wait(), signal() and broadcast() as appropriate.

#### Exercise A
Write a program with 20 threads,
*10 of which are producers and 10 are consumers. 
*Declare a shared variable count = 0 and 
* in the producer thread, increment it by one and 
* in the consumer thread decrement by 1. 
* thread_id is an integer that is 1 to 10 for producers and 11 to 20 for consumers.
* Synchronize this code so that the count goes from 1 to 10 and then goes from 10 to 1.

The code for each thread is given below.

```
producer() {
count++; print thread_id, count;
}

consumer () {
print thread_id, count; count--;
}
```

#### Exercise B
Modify the above code (version A) such that 
*the count goes from 1 to 5. After that the consumers can start consuming it. 
* Every time count goes below 5, producers can add to it. 
* But if count is at 5, producer should not add to it.

## Compile:

```
$ gcc -o file-io-syscall  file-io-syscall.c
$ g++ -o pthread-example pthread-example.c -lpthread
```
