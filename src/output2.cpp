#include "../header/output2.hpp"
#include "../header/base.hpp"
#include "../header/connector.hpp"

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

bool Output2::execute() {
  // https://serverfault.com/questions/196734/bash-difference-between-and-operator
  // http://www.tldp.org/LDP/abs/html/io-redirection.html

  int fd;
  int ret;
  int saved_stdout;

  string file = right->get_command();

  fd = open(file.c_str(), O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);

  if (fd < 0) {
    perror("open");
    exit(1);
    return false;
  }

  saved_stdout = dup(1);
  ret = dup2(fd, 1);

  if (ret < 0) {
    perror("dup2");
    exit(1);
    return false;
  }

  left->execute();

  dup2(saved_stdout, 1);
  // close(saved_stdout);
  //close(fd);

  if (close(saved_stdout) == -1) {
    perror("errno");
    exit(1);
    return true;
  } else if (close(saved_stdout) == 0) {
    close(saved_stdout);
    return true;
  }

  return true;
}