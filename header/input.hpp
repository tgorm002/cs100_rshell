#ifndef __INPUT__HPP__
#define __INPUT__HPP__

#include "base.hpp"
#include "connector.hpp"

using namespace std;

class Base;

class Input : public Connector {
 public:
  Input() {}
  Input(Base *left, Base *right) : Connector(left, right) {}

  bool execute();
};

#endif