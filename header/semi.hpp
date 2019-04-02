#ifndef __SEMI__HPP__
#define __SEMI__HPP__

#include "base.hpp"
#include "connector.hpp"

using namespace std;

class Base;

class SemiConnector : public Connector {
 public:
  SemiConnector() {}
  SemiConnector(Base *left, Base *right) : Connector(left, right) {}

  bool execute();
};

#endif