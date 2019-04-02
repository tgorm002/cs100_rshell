#include <iostream>
#include "../header/and.hpp"
#include "../header/base.hpp"
#include "../header/command.hpp"
#include "../header/connector.hpp"
#include "../header/input.hpp"
#include "../header/or.hpp"
#include "../header/output1.hpp"
#include "../header/output2.hpp"
#include "../header/pipe.hpp"
#include "../header/semi.hpp"
#include "../header/user.hpp"

using namespace std;

int main() {
  string input;
  while (true) {
    cout << "$ ";
    getline(cin, input);
    User* client = new User();
    client->parsing(input);
    client->opening();
    delete client;
  }

  return 0;
}