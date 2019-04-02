#include "../header/input.hpp"
#include "../header/base.hpp"
#include "../header/connector.hpp"

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

using namespace std;

bool Input::execute() {
  // https://www.tutorialspoint.com/unix/unix-io-redirections.htm
  // https://www.guru99.com/linux-redirection.html#2

  int fd;
  int ret;
  int saved_stdin;

  string file = right->get_command();

  fd = open(file.c_str(), O_RDONLY);

  if (fd < 0) {
    perror("open");
    exit(1);
    return false;
  }

  saved_stdin = dup(0);
  ret = dup2(fd, 0);

  if (ret < 0) {
    perror("dup2");
    exit(1);
    return false;
  }

  left->execute();
  //close(fd);
  dup2(saved_stdin, 0);
  //cout << "nicole" << endl;
  if (close(saved_stdin) == -1) {
    perror("errno");
    exit(1);
    return false;
  } else if (close(saved_stdin) == 0) {
    close(saved_stdin);
    return true;
  }
  // exit(0);
  // //cout << "Trevpr" << endl;
  return true;

  // left->execute();
  // //close(fd);
  // dup2(saved_stdin, 0);
  // //cout << "nicole" << endl;
  // if (close(saved_stdin) == -1) {
  //   perror("errno");
  //   exit(1);
  //   return false;
  // } else if (close(saved_stdin) == 0) {
  //   close(saved_stdin);
  //   return true;
  // }
  // exit(0);
  // //cout << "Trevpr" << endl;
  // return true;
}