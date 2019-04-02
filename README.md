# CS 100 Programming Project

> Winter 2019 // Trevor Gorman 862012653, Nicole Nguyen 862034393

## Introduction
This project will be a C++ language-based program called RShell. This will be designed as a bash terminal to print a command prompt, take in, and execute commands. It will read in commands and the connector from the user's input and utilize syscalls(execvp, fork, waitpid). It will be created with the Composite pattern as there is specific functionality for certain subclasses.The design would take the commands as operators and operands, executing them as they are evaluated. In addition, they will be executed with a left and right, with every character included.

## UML Diagram
![uml diagram](https://github.com/cs100/assignment-cs100_trevor_nicole/blob/master/images/umldiagram.png?raw=true)

## Classes
`User` 
* This class will be the client, aka the one that deals with commands. We will start off with an opening() function to instruct the user on what to do (if needed) and to start entering a command. This will take place in main so it will continue to take in input. As the user types in their commands, the command will be held in a string, in which it will be passed into a function that will parse and extract that command. This will return a base pointer. Lastly, there is a vector of Base pointers which will hold the commands after they have been parsed which will then go through to the Base class, where executable functions will take place. 

### Class Group

`Component Class`
* **Base:** This will act as the interface or default behavior of the composite pattern. As so, it will inherit from the User and take in its commands. This will hold a pure virtual function that its subclasses can override called execute, which will let us know whether the command has executed or not, using booleans. In addition to this, Base will hold the children which add functionality to the commands to be executed.

`Leaf`
* **Command:** Acting as the leaf, this will hold the command taken from Base from User as a string. Inheriting from base, this will also hold an execute function. The composite class will be built on this. To implement this, we will need to use system calls such as execvp, waitpid, and fork.

    * TestConnector: Created for the case where the user inputs a test command such as: test -e src/main.cpp or [-e src/main.cpp]. Returns true or false depending on if the user inputs a valid command or not. This function has flags -e, -f, and -d for checking if the file/directory exists, if the file/directory exists and is a regular file, and if the file/directory exists and is a directory, respectively. Cannot use execvp() call and must be compatible with regular connectors.


`Composite Classes`
* **Connector:** Similar to an expression tree, this class will have two Base pointers, left and right, which will use commands and other subclasses. These include AND(&&), OR(||), and Semicolon(;). Its execute function is also virtual.

    * AndConnector: Functioning as a logic expression, this will call the execute functions, overall evalutating the truth value of the children. Calling the left first, if it is false, it will return false and break out. If not, it will call execute on the right; this can only return true if the right child returns true.

    * OrConnector: Like its logic operator, this will function like 'AND' except returns true right away if the left child is true. If not, it will carry on to the right child, in which the function may return true only if the right child returns true.

    * SemiConnector: Though the semicolon class has the execute function, unlike AND and OR, this class calls the function on the left and the right and has no condition for whether the children return true or false.

    * Ouput1: The single output connector is used to overwrtite the file if it has already been created, and to create it if it has not been created yet 

    * Ouput2: The double output connector is used to append the text to the file if it has already been created, and to create the file if it has not been created yet

    * Input: The input connector used so that a program can read input from the keyboard and can also read input from a text file

    * Pipe: The pipe connector is used o send the output of one command/program/process to another command/program/process for further processing

## Prototypes/Research
Code Prototype: syscalls -- includes waitpid(), execvp(), fork()

```C++
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>

using namespace std;

int main() {

    // execvp - provide array of pointers to null-term strings that rep argument list for new program
    // MUST terminate by NULL

    char * arg[5];
    string ls = "ls";
    string dash_l = "-l";
    string echo = "echo";
    string mkdir = "mkdir";

    arg[0] = (char *)ls.c_str();
    arg[1] = (char *)dash_l.c_str();
    arg[2] = (char *)echo.c_str();
    arg[3] = (char *)mkdir.c_str();
    arg [4] = NULL;

    // fork - create a child process (2 duplicate)
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork");
    } 
    // child process
    else if (pid == 0) {
        cout << "Child: " << pid << endl;

        if (execvp(arg[0], arg) == -1) {
            perror("exec");
        }
    } 
    //parent process
    else {
        if (waitpid(pid, NULL, WNOHANG) == -1) {
            if (wait(0) == -1) {
                perror("wait");
            }
        }

        cout << "Parent: " << pid << endl;
    }
    
    return 0;
}
```

Research / Notes: 
* Program seems to compile fine 
* Output received when run:
    - Parent: 16297
    - Child: 0
    - ls: echo: No such file or directory
    - ls: mkdir: No such file or directory
* Shows parent outputted before child
* More to learn about these syscalls and perror

## Development and Testing Roadmap

Development Tasks
* Create branches to work on specific parts of the program
    - [Link to issue](https://github.com/cs100/assignment-cs100_trevor_nicole/issues/1)
* Get the program to read in the line of commands with the format of argument list, connector, and command
    * Get program to output command prompt: $ (Nicole)
    * Find a way to parse through and extract the command (Nicole)
    - [Linked](https://github.com/cs100/assignment-cs100_trevor_nicole/issues/2)
* Execute using syscalls execvp, fork, and waitpid (Nicole and Trevor)
    * Research and read up on it 
    - [Linked](https://github.com/cs100/assignment-cs100_trevor_nicole/issues/3)
* Put in unit tests to get functions to work like they should (Nicole and Trevor)
    - [Linked](https://github.com/cs100/assignment-cs100_trevor_nicole/issues/4)
* Depending on how we go about it, we may make use of Decorator as we learn from mistakes and see how we can continue building our commands so we can extend the functionality of the command tree (Trevor)
    - [Linked](https://github.com/cs100/assignment-cs100_trevor_nicole/issues/5)
* Get parser to deal with taking in parentheses (Nicole)
    - [Linked](https://github.com/cs100/assignment-cs100_trevor_nicole/issues/6)
* Deal with test functions and hard-coding (Trevor)
    - [Linked](https://github.com/cs100/assignment-cs100_trevor_nicole/issues/7)

