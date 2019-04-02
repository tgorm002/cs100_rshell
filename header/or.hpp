#ifndef __OR__HPP__
#define __OR__HPP__

#include "base.hpp"
#include "connector.hpp"

using namespace std;

class Base;

class OrConnector : public Connector {
 public:
  OrConnector() {}
  OrConnector(Base *left, Base *right) : Connector(left, right) {}

  bool execute();
};

#endif