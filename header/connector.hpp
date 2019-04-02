#ifndef __CONNECTOR__HPP__
#define __CONNECTOR__HPP__

#include "base.hpp"
#include "command.hpp"

using namespace std;

class Base;

class Connector : public Base {
 protected:
  Base *left;
  Base *right;

 public:
  Connector(){};
  Connector(Base *left, Base *right) : left(left), right(right){};

  virtual bool execute() = 0;
  string get_command() { return ""; }
};

#endif