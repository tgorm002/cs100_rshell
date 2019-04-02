#include "../header/and.hpp"
#include <iostream>
#include "../header/base.hpp"
#include "../header/connector.hpp"

using namespace std;

class Base;
class Connector;

bool AndConnector::execute() {
  return (left->execute()) && (right->execute());
}