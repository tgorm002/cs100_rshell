#ifndef __PIPE__HPP__
#define __PIPE__HPP__

#include "base.hpp"
#include "command.hpp"
#include "connector.hpp"

using namespace std;

class Base;
class Connector;

class Pipe : public Connector {
 public:
  Pipe() {}
  Pipe(Base *left, Base *right) : Connector(left, right) {}

  bool execute();
};

#endif