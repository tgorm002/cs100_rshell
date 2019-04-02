#ifndef __OUTPUT2__HPP__
#define __OUTPUT2__HPP__

#include "base.hpp"
#include "connector.hpp"

using namespace std;

class Base;

class Output2 : public Connector {
 public:
  Output2() {}
  Output2(Base *left, Base *right) : Connector(left, right) {}

  bool execute();
};

#endif