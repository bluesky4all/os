# Exercise 1:  I/O with system calls.
## Write a program using only system calls that does the following:
### When run initially, creates a file with fixed sized records of contacts
* Each record will be fixed size of 40 characters
* Character 0-19 will hold the name of the person
* Characters 20-39 will hold the phone number
### In the initial run, create 10 random entries with name (alphabetical) and number (digits 0-9)
* Run the program second time and only read names and list them, one on a line
* Run the program third time and only read numbers and list them, one on a line
* Run the program fourth time and list every name and number (on a line each)
* Run the program fifth time with a command line argument of name 3 "Blue Sky" "5551212"
* This should replace the 3rd entry with the name and number from command line
* You cannot read anything in this operation
* You are allowed to only write 40 characters (no more)
* Run the program fourth time and list every name and number (on a line each) and verify that previous update worked
* You will need to learn about lseek(2) system call.
