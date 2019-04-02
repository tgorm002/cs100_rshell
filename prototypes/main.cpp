#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
  // execvp - provide array of pointers to null-term strings that rep argument list for new program
  // MUST terminate by NULL

  char *arg[5];
  string ls = "ls";
  string dash_l = "-l";
  string echo = "echo";
  string mkdir = "mkdir";

  arg[0] = (char *)ls.c_str();
  arg[1] = (char *)dash_l.c_str();
  arg[2] = (char *)echo.c_str();
  arg[3] = (char *)mkdir.c_str();
  arg[4] = NULL;

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