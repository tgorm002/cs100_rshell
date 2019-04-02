#ifndef __USER__HPP__
#define __USER__HPP__

#include <string>
#include <vector>

using namespace std;

class Base;

class User {
 protected:
  Base *root;
  string opcommand;
  vector<string> argVec;

 public:
  User() : root(0) {}
  User(string &opcommand) : opcommand(opcommand) {}

  void opening();
  Base *parsing(string &);
};

#endif