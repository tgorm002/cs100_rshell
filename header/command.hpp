#ifndef __COMMAND__HPP__
#define __COMMAND__HPP__

#include <string>
#include "base.hpp"

using namespace std;

class Base;

class Command : public Base {
 protected:
  // exec performs on char *
  string command;

 public:
  Command(){};
  Command(string &command) : command(command) {}
  virtual bool execute();
  string get_command() { return command; }
};

class TestCommand : public Command {
 public:
  TestCommand() {}
  TestCommand(string &command) : Command(command) {}

  bool execute();
};

#endif
