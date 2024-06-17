# ATM management system program

A terminal application that simulates what a customer would do at an ATM

## Dependencies
* gcc compiler / clang compiler on linux
* Mingw or a similar compiler on Windows (Haven't tried, might fail!).

## Compiling

Project was compiled using gcc. use the following commands to run.

    gcc ./atm.c -o atm -lm
    ./atm

Using clang compiler.

    clang ./atm.c -o atm -lm
    ./atm

## Running the executable
If you would like to just run the executable provided

    clone the repository
    cd ~/your_folder
    ./atm

## TODOS

* Implement some sort of caching
* Write user data to a file, start programs by checking that a user ID is in the file instead of beginning a new session every time.