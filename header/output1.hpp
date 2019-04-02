#ifndef __OUTPUT1__HPP__
#define __OUTPUT1__HPP__

#include "base.hpp"
#include "connector.hpp"

using namespace std;

class Base;

class Output1 : public Connector {
 public:
  Output1() {}
  Output1(Base *left, Base *right) : Connector(left, right) {}

  bool execute();
};

#endif