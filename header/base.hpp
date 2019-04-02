#ifndef __BASE__HPP__
#define __BASE__HPP__

#include <string>

using namespace std;

class Base {
 public:
  Base(){};

  virtual bool execute() = 0;
  // need to extract command from base pointer for pipe/redirection
  virtual string get_command() = 0;
};

#endif