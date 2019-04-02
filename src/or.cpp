#include "../header/or.hpp"
#include <iostream>
#include "../header/base.hpp"
#include "../header/connector.hpp"

using namespace std;

class Base;
class Connector;

bool OrConnector::execute() {
  return (left->execute()) || (right->execute());
}
