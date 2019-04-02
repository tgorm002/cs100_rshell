#include "../header/semi.hpp"
#include <iostream>
#include "../header/base.hpp"
#include "../header/connector.hpp"

using namespace std;

class Base;
class Connector;

// return value based on right child
bool SemiConnector::execute() {
  left->execute();
  return right->execute();
}