#ifndef __AND__HPP__
#define __AND__HPP__

#include "base.hpp"
#include "connector.hpp"

using namespace std;

class Base;

class AndConnector : public Connector {
 public:
  AndConnector() {}
  AndConnector(Base *left, Base *right) : Connector(left, right) {}

  bool execute();
};

#endif