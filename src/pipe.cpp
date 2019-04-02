#include "../header/pipe.hpp"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include "../header/base.hpp"
#include "../header/command.hpp"
#include "../header/connector.hpp"

using namespace std;

bool Pipe::execute() {
  // https://www.geeksforgeeks.org/piping-in-unix-or-linux/
  // https://www.guru99.com/linux-pipe-grep.html

  // https://stackoverflow.com/questions/976015/why-do-i-need-to-close-fds-when-reading-and-writing-to-the-pipe
  // fds 0 -- stdin
  // fds 1 -- stdout
  // fds 2 -- stderr

  //   int fd[2];
  //   if (pipe(fd) == -1) {
  //     perror("pipe");
  //     return false;
  //   }
  //   // pipe goes from left to right -- close after pass
  //   if (!left->execute()) {
  //     exit(1);
  //     return false;
  //   }
  //   cout << "in the pipe area" << endl;
  //   if (close(fd[1]) == -1) {
  //     perror("errno");
  //     exit(1);
  //     return false;
  //   } else if (close(fd[1]) == 0) {
  //     close(fd[1]);
  //     return true;
  //   }

  //   if (!right->execute()) {
  //     exit(1);
  //     return false;
  //   }
  //   if (close(fd[0]) == -1) {
  //     perror("errno");
  //     exit(1);
  //     return false;
  //   } else if (close(fd[0]) == 0) {
  //     close(fd[0]);
  //     return true;
  //   }
  //   cout << "ITSA ME MARIO" << endl;
  //   return true;
  // }

  int fds[2];
  int status;
  pid_t pid, pid2;

  int ret = pipe(fds);
  if (ret < 0) {  //error
    perror("pipe");
    exit(1);
    return false;
  }
  pid = fork();
  if (pid < 0) {
    perror("fork");
    exit(1);
    return false;
  }
  //https://stackoverflow.com/questions/37895274/c-in-unix-fork-waitpid-and-pipes
  //using pipe is only visible to the concerned processes, tried inherited pipe
  //tried using one fork already, it did not fully run gtests, so we had to fork twice

  if (pid == 0) {  //returns 0 which means success
    pid2 = fork();

    if (pid2 < 0) {
      perror("fork");
      exit(1);
      return false;
    } else if (pid2 == 0) {
      if (dup2(fds[1], 1) < 0) {
        perror("dup2");
        exit(1);
        return false;
      }
      if (close(fds[0]) < 0) {  //we close the read side
        perror("errno");
        exit(1);
        return false;
      }
      if (!left->execute()) {
        exit(1);
        return false;
      }
      exit(0);
    } else {
      if (dup2(fds[0], 0) < 0) {
        perror("dup2");
        exit(1);
        return false;
      }
      if (close(fds[1]) < 0) {  //closing the output side
        perror("errno");
        exit(1);
        return false;
      }
      if (!right->execute()) {
        exit(1);
        return false;
      }
      exit(0);
    }
  }
  //close pipe at the end
  if (close(fds[0]) < 0) {
    perror("errno");
    exit(1);
    return false;
  }
  if (close(fds[1]) < 0) {
    perror("errno");
    exit(1);
    return false;
  }

  // do {
  //   waitpid(pid, &status, 0);
  // } while (!WIFEXITED(status));

  // return !WEXITSTATUS(status);

  waitpid(pid, &status, 0);

  while (!WIFEXITED(status)) {
  }
  waitpid(pid, &status, 0);
  if (status > 0) {
    //this is bad !
    // exit(1);
    return false;
  } else if (WEXITSTATUS(status) == 0) {
    // exit(0);
    return true;
  } else if (WEXITSTATUS(status) == 1) {
    // exit(0);
    return false;
  }
}
